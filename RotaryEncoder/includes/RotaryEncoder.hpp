#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

// #include "GPIO.hpp"
#include "Log.hpp"
#include "Timer.hpp"
#include "GPIO.hpp"

#include <iostream>
#include <functional>
#include <thread>

class RotaryEncoder {
  private:
    int A, B, Button;
    int prevA, prevB;
    bool threadRunning;
    std::function<void()> onLeft;
    std::function<void()> onRight;
    std::function<void()> onButtonPress;
    std::function<void()> onButtonHold;
    std::thread rotaryThread;
    bool left, right, buttonPressed, buttonHeld;
    Log log;
    Timer timerButton;
    GPIO gpio;

    void RotaryThreadFunction();

  public:
    RotaryEncoder();
    ~RotaryEncoder();
    // Accessor functions for variables
    bool IsLeft() const; 
    bool IsRight() const; 
    bool IsButtonPressed() const;

    void operator()(std::function<void()> onLeft = nullptr, std::function<void()> onRight = nullptr, std::function<void()> onButtonPress = nullptr, std::function<void()> onButtonHold = nullptr);
    void SetOnLeft(std::function<void()> onLeft);
    void SetOnRight(std::function<void()> onRight);
    void SetOnButtonPress(std::function<void()> onButtonPress);
    void SetOnButtonHold(std::function<void()> onButtonHold);
};

#endif