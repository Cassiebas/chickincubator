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
    bool isLeft() const; 
    bool isRight() const; 
    bool isButtonPressed() const;

    void operator()(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onButtonPress);
    void setOnLeft(std::function<void()> onLeft);
    void setOnRight(std::function<void()> onRight);
    void setOnButtonPress(std::function<void()> onButtonPress);
};

#endif