// #include "GPIO.hpp"
// #include <thread>
// #include <unistd.h>
#include <iostream>
#include "RotaryEncoder.hpp"

void onLeft();
void onRight();
void onButtonPress();
void onButtonHold();

int main() {
  RotaryEncoder rot;
  rot(&onLeft, &onRight, &onButtonPress, &onButtonHold);
  while(1);
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
