#include <iostream>

#include "UI.hpp"

int main() {
    UI ui;
    sleep(3);
    ui.SwitchScreen(UI::HOME);
    sleep(10);
    ui.Warning("Never");
    sleep(1);
    ui.Warning("gonna");
    sleep(1);
    ui.Warning("give");
    sleep(1);
    ui.Warning("you");
    sleep(1);
    ui.Warning("up");
    while(1);
    return 0;
}
