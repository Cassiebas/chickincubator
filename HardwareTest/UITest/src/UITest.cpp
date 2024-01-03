#include <iostream>

#include "UI.hpp"
#include "RotaryEncoder.hpp"

Screen screen = BOOT;
UI ui;

void OnButtonPress();

int main() {    
    RotaryEncoder rotary;
    rotary(nullptr, nullptr, &OnButtonPress);
    return 0;
}

void OnButtonPress() {
    screen = (Screen)(screen + 1);
    screen = (Screen)(screen % 3);
    ui.SwitchScreen(screen);
    std::cout << "Screen: " << screen << "\n";
}