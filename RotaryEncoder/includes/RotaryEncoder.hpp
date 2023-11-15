#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include "GPIO.hpp"

#include <iostream>
#include <functional>
#include <thread>


class RotaryEncoder {
  private:
    int A, B, Button;
    int prevA, prevB;
    bool threadRunning;
    std::thread rotaryThread;
    bool left, right, buttonPressed;

    void rotaryThreadFunction();

  public:
    RotaryEncoder();
    ~RotaryEncoder();

    // Accessor functions for variables
    bool isLeft() const { return left; }
    bool isRight() const { return right; }
    bool isButtonPressed() const { return buttonPressed; }
};

#endif