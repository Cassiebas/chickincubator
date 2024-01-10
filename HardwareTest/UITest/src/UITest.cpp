#include <iostream>

#include "UI.hpp"

int main() {
    UI ui;
    sleep(3);
    ui.Warning("Never");
    ui.Warning("gonna");
    ui.Warning("give");
    ui.Warning("you");
    ui.Warning("up");
    while(1);
    return 0;
}