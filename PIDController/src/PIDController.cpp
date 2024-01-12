#include "PIDController.hpp"
#include <stdlib.h>
#include <fstream>
#include <cmath>

PIDController::P::P(double kp, Log &log) : kp(kp), log(log) {

}

double PIDController::P::operator()(double error) {
    return kp * error;
}

PIDController::I::I(double ki, Log &log) : ki(ki), log(log) {

}

double PIDController::I::operator()(double error, double time) {
    sum += abs(time - lastTime) * error;
    double result = sum;
    result /= abs(time - lastTime);
    lastTime = time;
    return  ki * result;
}

PIDController::D::D(double kd, Log &log) : kd(kd), log(log) {

}

double PIDController::D::operator()(double error, double time) {
    if (lastTime == 0) {
        lastTime = time;
        lastError = error;
        return 0; //skip first call because there is no delta
    }
    double differential = (error - lastError) / (time - lastTime);
    log(Severity::debug, "Differential = (" + std::to_string(lastError) + " - " + std::to_string(error) + ") / (" + std::to_string(lastTime) + " - " +  std::to_string(time) + ")   = " + std::to_string(differential));
    // std::cout << differential <<  " = (" << lastError << " - " << error << ") / (" << lastTime << " - " <<  time << ")";
    // differential *= abs(time - lastTime);
    lastTime = time;
    lastError = error;
    // std::cout << "\t\t\t d::kd : " << kd << " d::diff : " << differential << "\n";
    return kd * differential;
}

PIDController::PIDController(double temperature, double kp, double ki, double kd, double min, double max) 
    : p(kp, log), i(ki, log), d(kd, log), min(min), max(max), log(Log("../logs/", "eggcubator.log", "PIDController", true))
{
    SetTemp(temperature);
    std::vector<double> temps = GetTemp();
    ambientTemp = (temps.at(0) + temps.at(1)) / 2.0;
}

double PIDController::operator()() {
    // Sum up the P, I, and D components
    pRes = p(error);
    iRes = i(error, GetTime());
    dRes = d(error, GetTime());
    log(Severity::info, "P: " + std::to_string(pRes) + " I: " + std::to_string(iRes) + " D: " + std::to_string(dRes));
    return pRes + iRes + dRes;
    // return p(error) + i(error, GetTime()) + d(error, GetTime());
}

void PIDController::operator()(double Kp, double Ki, double Kd) {
    p.kp = Kp;
    i.ki = Ki;
    d.kd = Kd;
    // i.sum = 0;
    // i.lastTime = 0;
    // d.lastTime = 0;
    // d.lastError = 0;
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
    // std::cout << "PID threadcycle\n";
    std::vector<double> temps = GetTemp();
    avgTemp = ((temps.at(0) + temps.at(1)) / 2.0);
    // error = (setTemp - ((temps.at(0) + temps.at(1)) / 2.0))/(setTemp - ambientTemp); //average temperature over both sensors, then normalize it over setPoint and ambient
    error = setTemp - avgTemp;
    double result = this->operator()();
    // std::cout << "Kp: " << p.kp << " Ki: " << i.ki << " Kd: " << d.kd << "\n";
    // std::cout << "PID value: " << result << "\n";
    // std::cout << "Controlling heater with: " << ToPercentPower(result) << "% power \n";
    // pidPlot.AddPoint(GetTime()/60.0, ToPercentPower(result), "Heater (%)");
    pidPlot.AddPoint(GetTime()/60.0, setTemp, "Tset (°C)");
    pidPlot.AddPoint(GetTime()/60.0, (temps.at(0) + temps.at(1)) / 2.0, "Tavg (°C)");
    pidPlot.ExportToPNG("plots/", "Temperature", "Time (min)", "Temperature (°C)", "T(t)"); //Line label gets ignored here since there are multiple lines
    system("sudo rm -f /var/www/eggcubator/Temperature.png");
    system("sudo mv plots/Temperature.png /var/www/eggcubator/Temperature.png");
    powerPlot.AddPoint(GetTime()/60.0, ToPercentPower(result), "Heater power (%)");
    powerPlot.ExportToPNG("plots/", "Power", "Time (min)", "Power (%)", "P(t)"); //Line label gets ignored here since there are multiple lines
    system("sudo rm -f /var/www/eggcubator/Power.png");
    system("sudo mv plots/Power.png /var/www/eggcubator/Power.png");
    componentPlot.AddPoint(GetTime()/60.0, pRes, "P");
    componentPlot.AddPoint(GetTime()/60.0, iRes, "I");
    componentPlot.AddPoint(GetTime()/60.0, dRes, "D");
    componentPlot.ExportToPNG("plots/", "Components", "Time (min)", "Value", "T(t)"); //Line label gets ignored here since there are multiple lines
    system("sudo rm -f /var/www/eggcubator/Components.png");
    system("sudo mv plots/Components.png /var/www/eggcubator/Components.png");
    heater((unsigned int)(ToPercentPower(result))); 
}

void PIDController::Start() {
    ControllerStart();
}

void PIDController::Stop() {
    ControllerStop();
    pidPlot.ExportToPNG("plots/", "Temperature", "Time (min)", "Temperature (°C)", "T(t)"); //Line label gets ignored here since there are multiple lines
}

void PIDController::SetTemp(double temp) {
    setTemp = temp;
}

double PIDController::GetAvgTemp() {
    return avgTemp;
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
