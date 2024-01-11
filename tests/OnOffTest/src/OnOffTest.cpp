#include "OnOffController.hpp"

int main() {
    OnOffController controller(37.5); //37.5 °C
    controller.Start();
    while (controller.GetTime()/60.0 < 45.0);
    controller.Stop();
    return 0;
}