#include "PIDController.hpp"

int main() {
    PIDController controller(37.5, 0.75, 0, 0);
    controller.Start();
    while (controller.GetTime()/60.0 < 5.0);
    controller.Stop();
    return 0;
}