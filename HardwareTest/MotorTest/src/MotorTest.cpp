#include <iostream>
#include "Motor.hpp"
#include "Timer.hpp"

int main() {
    Motor motor;
    Timer timer;
    timer.Start();
    motor.Forward();
    std::cout << "Forward\n";
    while(timer.Elapsed() < 3);
    motor.Coast();
    std::cout << "Coast\n";
    while(timer.Elapsed() < 6);
    motor.Backward();
    std::cout << "Backward\n";
    while(timer.Elapsed() < 9);
    motor.Brake();
    std::cout << "Brake\n";
    timer.Stop();
    return 0;
}