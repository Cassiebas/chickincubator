#include "PIDController.hpp"

int main() {
    PIDController controller(37.5, 1.5, 0, 0);
    // PIDController controller(37.5, 0.3375, 0.15428571428, 0);
    controller.Start();
    while (controller.GetTime()/60.0 < 20.0);
    controller.Stop();
    return 0;
}