#include "RotaryEncoder.hpp"

void onLeft();
void onRight();
void onButtonPress();

int main() {
    RotaryEncoder rotary;
    rotary(&onLeft, &onRight, &onButtonPress);
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
