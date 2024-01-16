#include "RotaryEncoder.hpp"

void onLeft();
void onRight();
void onButtonPress();
void onButtonHold();

int main() {
    RotaryEncoder rotary;
    rotary(&onLeft, &onRight, &onButtonPress, &onButtonHold);
    return 0;
}

void onLeft() {
    std::cout << "Rotary turned left\n";
}

void onRight() {
    std::cout << "Rotary turned right\n";
}

void onButtonPress() {
    std::cout << "Rotary button pressed\n";
}

void onButtonHold() {
    std::cout << "Rotary button was held\n";
}
