#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include "GPIO.hpp"
#include "Log.hpp"

#include <iostream>
#include <functional>
#include <thread>

class RotaryEncoder {
  private:
    uint8_t A, B, Button;
    uint8_t prevA, prevB;
    bool threadRunning;
    std::function<void()> onLeft;
    std::function<void()> onRight;
    std::function<void()> onButtonPress;
    std::thread rotaryThread;
    bool left, right, buttonPressed;
    Log log;

    void rotaryThreadFunction();

  public:
    RotaryEncoder();
    ~RotaryEncoder();
    // Accessor functions for variables
    bool IsLeft() const; 
    bool IsRight() const; 
    bool IsButtonPressed() const;

    void operator()(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onButtonPress);
    void SetOnLeft(std::function<void()> onLeft);
    void SetOnRight(std::function<void()> onRight);
    void SetOnButtonPress(std::function<void()> onButtonPress);
};

#endif