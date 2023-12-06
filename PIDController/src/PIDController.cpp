#include "PIDController.hpp"
#include <stdlib.h>
#include <fstream>
#include <cmath>

PIDController::P::P(double kp) : kp(kp) {

}

double PIDController::P::operator()(double error) {
    return kp * error;
}

PIDController::I::I(double ki) : ki(ki) {

}

double PIDController::I::operator()(double error, double time) {
    sum += abs(time - lastTime) * error;
    double result = sum;
    result /= abs(time - lastTime);
    lastTime = time;
    return  ki * result;
}

PIDController::D::D(double kd) : kd(kd) {

}

double PIDController::D::operator()(double error, double time) {
    double differential = /*abs(lastTime - time) != 0 ? */(error - lastError) / (time - lastTime)/* : 0*/;
    // std::cout << differential <<  " = (" << lastError << " - " << error << ") / (" << lastTime << " - " <<  time << ")";
    differential *= time;
    lastTime = time;
    lastError = error;
    // std::cout << "\t\t\t d::kd : " << kd << " d::diff : " << differential << "\n";
    return kd * differential;
}

PIDController::PIDController(double temperature, double kp, double ki, double kd, double min, double max) : p(kp), i(ki), d(kd), min(min), max(max) {
    log = Log("", "PIDController.log", true);
    logtag = "[PIDController] ";
    logNamespace = "PIDController::";
    SetTemp(temperature);
    std::vector<double> temps = GetTemp();
    ambientTemp = (temps.at(0) + temps.at(1)) / 2.0;
}

double PIDController::operator()() {
    // Sum up the P, I, and D components
    pRes = p(error);
    iRes = i(error, GetTime());
    dRes = d(error, GetTime());
    log(Severity::trace, logtag + " " + logNamespace + "operator()() called");
    return pRes + iRes + dRes;
    // return p(error) + i(error, GetTime()) + d(error, GetTime());
}

void PIDController::operator()(double Kp, double Ki, double Kd) {
    p.kp = Kp;
    i.ki = Ki;
    d.kd = Kd;
    i.sum = 0;
    i.lastTime = 0;
    d.lastTime = 0;
    d.lastError = 0;
}

double PIDController::ToPercentPower(double pidValue) {  
    // double percent = (pidValue / abs(setTemp - ambientTemp)) * 100.0;  
    // double percent = pidValue * 100.0;
    double percent = pidValue;
    if (percent < min)
        percent = min;
    if (percent > max)
        percent = max;
    return percent;
}

void PIDController::Do() {
    std::vector<double> temps = GetTemp();
    // error = (setTemp - ((temps.at(0) + temps.at(1)) / 2.0))/(setTemp - ambientTemp); //average temperature over both sensors, then normalize it over setPoint and ambient
    error = setTemp - ((temps.at(0) + temps.at(1)) / 2.0);
    double result = this->operator()();
    std::cout << "Kp: " << p.kp << " Ki: " << i.ki << " Kd: " << d.kd << "\n";
    std::cout << "PID value: " << result << "\n";
    std::cout << "Controlling heater with: " << ToPercentPower(result) << "% power \n";
    // pidPlot.AddPoint(GetTime()/60.0, ToPercentPower(result), "Heater (%)");
    pidPlot.AddPoint(GetTime()/60.0, setTemp, "Tset (°C)");
    pidPlot.AddPoint(GetTime()/60.0, (temps.at(0) + temps.at(1)) / 2.0, "Tavg (°C)");
    pidPlot.ExportToPNG("", "PID", "Time (m)", "Temperature (°C)", "T(t)"); //Line label gets ignored here since there are multiple lines
    system("sudo cp PID.png /var/www/eggcubator/PID.png");
    powerPlot.AddPoint(GetTime()/60.0, ToPercentPower(result), "Heater power (%)");
    powerPlot.ExportToPNG("", "Power", "Time (m)", "Power (%)", "P(t)"); //Line label gets ignored here since there are multiple lines
    system("sudo cp Power.png /var/www/eggcubator/Power.png");
    componentPlot.AddPoint(GetTime()/60.0, pRes, "P");
    componentPlot.AddPoint(GetTime()/60.0, iRes, "I");
    componentPlot.AddPoint(GetTime()/60.0, dRes, "D");
    componentPlot.ExportToPNG("", "components", "Time (m)", "Value", "T(t)"); //Line label gets ignored here since there are multiple lines
    system("sudo cp components.png /var/www/eggcubator/components.png");
    heater(static_cast<unsigned int>(ToPercentPower(result))); 
}

void PIDController::Start() {
    ControllerStart();
}

void PIDController::Stop() {
    ControllerStop();
    pidPlot.ExportToPNG("", "PID", "Time (m)", "Temperature (°C)", "T(t)"); //Line label gets ignored here since there are multiple lines
}

void PIDController::SetTemp(double temp) {
    setTemp = temp;
}

void PIDController::ExportConstants() {
    std::ofstream file;
    file.open("pidconstants.txt");
    file << "Set temperature: " << setTemp << "\n"
         << "Kp: " << p.kp
         << "Ki: " << i.ki
         << "Kd: " << d.kd;
    file.close();
    system("sudo cp pidconstants.txt /var/www/eggcubator/pidconstants.txt");
}