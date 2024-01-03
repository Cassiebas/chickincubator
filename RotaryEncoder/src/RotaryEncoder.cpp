#include "RotaryEncoder.hpp"
#include <unistd.h>

RotaryEncoder::RotaryEncoder() : threadRunning(true), onLeft(nullptr), onRight(nullptr), onButtonPress(nullptr), log(Log("../logs/", "eggcubator.log", "RotaryEncoder", true))
{
  rotaryThread = std::thread(&RotaryEncoder::rotaryThreadFunction, this);
}

RotaryEncoder::~RotaryEncoder()
{
  if (rotaryThread.joinable()) {
    rotaryThread.join();
  }
}

void RotaryEncoder::RotaryThreadFunction()
{
  GPIO gpio;
  gpio.SetMode(GPIO_11, INPUT);
  gpio.SetMode(GPIO_9, INPUT);
  uint8_t sequence = 0x00;
  while (threadRunning) {
    A = gpio.Get(GPIO_11);
    B = gpio.Get(GPIO_9);
    // if (A != prevA || B != prevB) {
    sequence <<= 1;
    sequence |= A;
    sequence <<= 1;
    sequence |= B;
    // }
    Button = gpio.Get(GPIO_10);
    left = false;
    right = false;
    buttonPressed = false;

    // Check for left sequence: 01 -> 11 -> 10 -> 00
    if ((sequence & 0b00001111) == 0b00000111/*0b01111000*/) {
      prevA = 0;
      prevB = 0;
      left = true;
      onLeft();
      log(Severity::info, "Rotary encoder is turned left. prev A, B: " + std::to_string(prevA) + ", " + std::to_string(prevB) +  " A, B: " + std::to_string(A) + ", " + std::to_string(B) + " Sequence: " + std::to_string(sequence) );
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Check for right sequence: 10 -> 11 -> 01 -> 00
    if ((sequence & 0b00001111) == 0b00001011/*0b10110100*/) {
      prevA = 0;
      prevB = 0;
      right = true;
      onRight();
      log(Severity::info, "Rotary encoder is turned right. prev A, B: " + std::to_string(prevA) + ", " + std::to_string(prevB) +  " A, B: " + std::to_string(A) + ", " + std::to_string(B) + " Sequence: " + std::to_string(sequence) );
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    if (Button) {
      buttonPressed = true;
      onButtonPress();
      log(Severity::info, "Rotary encoder is pressed.");
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    prevA = A;
    prevB = B;
    std::cout << "prevA,prevB,A,B : " << std::to_string(prevA) << std::to_string(prevB) << std::to_string(A) << std::to_string(B) << "\n";
    std::cout << "sequence : "  << std::to_string(sequence) << "\n";
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

  void RotaryEncoder::operator()(std::function<void()> onLeft, std::function<void()> onRight, std::function<void()> onButtonPress) {
    this->onLeft = onLeft;
    this->onRight = onRight;
    this->onButtonPress = onButtonPress;
  }

  void RotaryEncoder::SetOnLeft(std::function<void()> onLeft) {
    this->onLeft = onLeft;
  }

  void RotaryEncoder::SetOnRight(std::function<void()> onRight) {
    this->onRight = onRight;
  }

  void RotaryEncoder::setOnButtonPress(std::function<void()> onButtonPress) {
    this->onButtonPress = onButtonPress;
  }
