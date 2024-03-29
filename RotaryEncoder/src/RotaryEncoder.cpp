#include "RotaryEncoder.hpp"
#include <unistd.h>
#include <fstream>

RotaryEncoder::RotaryEncoder() :
  threadRunning(false),
  onLeft(nullptr),
  onRight(nullptr),
  onButtonPress(nullptr),
  log(Log("../logs/", "eggcubator.log", "RotaryEncoder", true))
{
  buttonPressed = false;
  gpio.SetMode(11, INPUT);
  gpio.SetMode(10, INPUT);
  gpio.SetMode(9, INPUT);
}

RotaryEncoder::~RotaryEncoder()
{
  if (rotaryThread.joinable()) {
    rotaryThread.join();
  }
}

void RotaryEncoder::RotaryThreadFunction()
{
  uint8_t sequence = 0x00;
  while (threadRunning) {
    // std::cout << "Rotary threadcycle\n";
    // A = (uint8_t)gpio.Get(GPIO_11);
    // B = (uint8_t)gpio.Get(GPIO_9);
    A = gpio.Get(11);
    B = gpio.Get(9);
    // if (A != prevA || B != prevB) {
    sequence <<= 1;
    sequence |= (uint8_t)A;
    sequence <<= 1;
    sequence |= (uint8_t)B;
    // }
    // Button = (uint8_t)gpio.Get(GPIO_10);
    Button = gpio.Get(10);
    left = false;
    right = false;

    // Check for left sequence: 01 -> 11 -> 10 -> 00
    if ((sequence & 0b00001111) == 0b00000111/*0b01111000*/) {
      prevA = 0;
      prevB = 0;
      left = true;
      if(onLeft != nullptr)
        onLeft();
      log(Severity::info, "Rotary encoder is turned left. prev A, B: " + std::to_string(prevA) + ", " + std::to_string(prevB) +  " A, B: " + std::to_string(A) + ", " + std::to_string(B) + " Sequence: " + std::to_string(sequence) );
      // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Check for right sequence: 10 -> 11 -> 01 -> 00
    if ((sequence & 0b00001111) == 0b00001011/*0b10110100*/) {
      prevA = 0;
      prevB = 0;
      right = true;
      if(onRight != nullptr)
        onRight();
      log(Severity::info, "Rotary encoder is turned right. prev A, B: " + std::to_string(prevA) + ", " + std::to_string(prevB) +  " A, B: " + std::to_string(A) + ", " + std::to_string(B) + " Sequence: " + std::to_string(sequence) );
      // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    if (Button && timerButton.Elapsed() == 0) {
      timerButton.Start();
      // std::cout << "Timer start\n";
    }
    if (Button && timerButton.Elapsed() > 0.01 && timerButton.Elapsed() <= 0.5) {
      buttonPressed = true;
      // std::cout << "Looking like the button is pressed\n";
      // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if(Button && timerButton.Elapsed() > 0.5){
      buttonPressed = false;
      buttonHeld = true;
      // std::cout << "Looking like the button is held\n";
    } 
    
    if(!Button)
    {
        if(buttonPressed){
          log(Severity::info, "Rotary encoder is pressed.");
          if(onButtonPress != nullptr)
            onButtonPress();
          // std::this_thread::sleep_for(std::chrono::milliseconds(200));
          // std::cout << "The button is pressed\n";
        }
        if(buttonHeld){
          log(Severity::info, "Rotary encoder was held.");
          if(onButtonHold != nullptr)
            onButtonHold();
          // std::cout << "The button is held\n";
          // std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        buttonHeld = false;
        buttonPressed = false;
        timerButton.Stop();
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (prevA != A && prevB != B) {
    //   std::cout << "prevA,prevB,A,B : " << std::to_string(prevA) << std::to_string(prevB) << std::to_string(A) << std::to_string(B) << "\n";
    //   std::cout << "sequence : "  << std::to_string(sequence) << "\n";
      prevA = A;
      prevB = B;
    }
  }
} 

bool RotaryEncoder::IsButtonPressed() const {
  return buttonPressed; 
}

bool RotaryEncoder::IsRight() const {
  return right; 
}

bool RotaryEncoder::IsLeft() const {
  return left; 
}

void RotaryEncoder::operator()(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onButtonPress, std::function<void()> onButtonHold) {
  if (rotaryThread.joinable()) {
    rotaryThread.join();
  }
  this->onLeft = onLeft;
  this->onRight = onRight;
  this->onButtonPress = onButtonPress;
  this->onButtonHold = onButtonHold;
  threadRunning = true;
  rotaryThread = std::thread(&RotaryEncoder::RotaryThreadFunction, this);
}

void RotaryEncoder::SetOnLeft(std::function<void()> onLeft) {
  this->onLeft = onLeft;
}

void RotaryEncoder::SetOnRight(std::function<void()> onRight) {
  this->onRight = onRight;
}

void RotaryEncoder::SetOnButtonPress(std::function<void()> onButtonPress) {
  this->onButtonPress = onButtonPress;
}

void RotaryEncoder::SetOnButtonHold(std::function<void()> onButtonHold) {
  this->onButtonHold = onButtonHold;
}