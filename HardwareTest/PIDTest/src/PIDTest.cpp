#include "PIDController.hpp"

int main() {
    // PIDController controller(37.5, 6000, 0, 0);
    std::cout << "Enter Kp Ki Kd: \n"; //best till now: 200 0.5 0
    double Kp = 0, Ki = 0, Kd = 0;
    std::cin >> Kp;
    std::cin >> Ki;
    std::cin >> Kd;
    PIDController controller(37.5, Kp, Ki, Kd);
    // PIDController controller(37.5, 0.3375, 0.15428571428, 0);
    controller.Start();
    while (controller.GetTime()/60.0 < 20.0) {
        std::cin >> Kp;
        std::cin >> Ki;
        std::cin >> Kd;
        controller(Kp, Ki, Kd);
    }
    controller.Stop();
    return 0;
}