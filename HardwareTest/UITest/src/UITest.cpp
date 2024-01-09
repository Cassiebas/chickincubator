#include <iostream>

#include "UI.hpp"

int main() {
    UI ui;
    sleep(3);
    ui.SwitchScreen(UI::SETTINGS);
    while(1);
    return 0;
}
