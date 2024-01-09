#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

// #include "GPIO.hpp"
#include "Log.hpp"

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
    std::thread rotaryThread;
    bool left, right, buttonPressed;
    Log log;
    std::string path;

    void RotaryThreadFunction();

  public:
    RotaryEncoder();
    ~RotaryEncoder();
    // Accessor functions for variables
    bool IsLeft() const; 
    bool IsRight() const; 
    bool IsButtonPressed() const;
    void writeGPIO(const std::string filename, const std::string value);
    int readGPIO(std::string pin);

    void operator()(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onButtonPress);
    void SetOnLeft(std::function<void()> onLeft);
    void SetOnRight(std::function<void()> onRight);
    void SetOnButtonPress(std::function<void()> onButtonPress);
};

#endif