#include <iostream>

#include "UI.hpp"

int main() {
    UI ui;
    sleep(5);
    ui.SwitchScreen(UI::SETTINGS);
    while(1);
    return 0;
}
