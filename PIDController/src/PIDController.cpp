#include "PIDController.hpp"

PIDController::P::P(double kp) : kp(kp) {

}

double PIDController::P::operator()(double error) {
    return kp * error;
}

PIDController::I::I(double ki) : ki(ki) {

}

double PIDController::I::operator()(double error, double time) {
    sum += (abs(time - lastTime)) * error;
    lastTime = time;
    return ki * sum;
}

PIDController::D::D(double kd) : kd(kd) {

}

double PIDController::D::operator()(double error, double time) {
    double differential = abs(lastTime - time) / abs(lastError - error);
    lastTime = time;
    lastError = error;
    return kd * differential;
}

PIDController::PIDController(double temperature, double kp, double ki, double kd) : p(kp), i(ki), d(kd) {
    SetTemp(temperature);
    std::vector<double> temps = GetTemp();
    ambientTemperature = (temps.at(0) + temps.at(1)) / 2.0;
}

double PIDController::operator()() {
    // Sum up the P, I, and D components
    return p(error) + i(error, GetTime()) + d(error, GetTime());
}

double PIDController::ToPercentPower(double pidValue) {
    return (pidValue / abs(setTemp - ambientTemperature)) * 100.0;
}

void PIDController::Do() {
    std::vector<double> temps = GetTemp();
    error = setTemp - ((temps.at(0) + temps.at(1)) / 2.0);
    double result = this->operator()();
    std::cout << "PID value: " << result << "\n";
    if (result > 0) {
        std::cout << "Controlling heater with: " << ToPercentPower(result) << "\% power \n";
        heater(ToPercentPower(static_cast<unsigned int>(result))); 
    }
}

void PIDController::Start() {
    ControllerStart();
}

void PIDController::Stop() {
    ControllerStop();
}