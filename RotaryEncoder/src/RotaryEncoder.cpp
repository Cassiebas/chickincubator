#include "RotaryEncoder.hpp"
#include <unistd.h>

RotaryEncoder::RotaryEncoder() : threadRunning(true)
{
  rotaryThread = std::thread(&RotaryEncoder::rotaryThreadFunction, this);
}

RotaryEncoder::~RotaryEncoder()
{
  if (rotaryThread.joinable()) {
    rotaryThread.join();
  }
}

void RotaryEncoder::rotaryThreadFunction()
{
  GPIO gpio;

  while (threadRunning) {
    A = gpio.readPinState(GPIO_9) - '0';
    B = gpio.readPinState(GPIO_11) - '0';
    Button = gpio.readPinState(GPIO_10) - '0';
    left = false;
    right = false;
    buttonPressed = false;

    // Check for left sequence: 01 -> 11 -> 10 -> 00
    if (prevA == 0 && prevB == 1 && A == 1 && B == 1) {
      left = true;
    }

    // Check for right sequence: 10 -> 11 -> 01 -> 00
    if (prevA == 1 && prevB == 0 && A == 1 && B == 1) {
      right = true;
    }
    if (Button) {
      buttonPressed = true;
    }
    
    prevA = A;
    prevB = B;
  }
}