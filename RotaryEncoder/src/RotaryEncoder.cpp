#include "RotaryEncoder.hpp"
#include <unistd.h>
#include <fstream>

void RotaryEncoder::writeGPIO(const std::string filename, const std::string value)
{
  std::ofstream file((path + filename).c_str());

  if (!file)
  {
    std::cerr << "Unable to open file: " + (path + filename) << std::endl;
    return;
  }
  file << value;
  file.close();
}

int RotaryEncoder::readGPIO(std::string pin) {
    // Read the GPIO pin state
    std::ifstream valueFile("/sys/class/gpio/gpio" + pin + "/value");
    if (!valueFile.is_open()) {
        throw std::runtime_error("Failed to open GPIO value file.");
    }
    int value;
    valueFile >> value;

    return value;
}

RotaryEncoder::RotaryEncoder() : threadRunning(false), onLeft(nullptr), onRight(nullptr), onButtonPress(nullptr), log(Log("../logs/", "eggcubator.log", "RotaryEncoder", true)), path("/sys/class/gpio/")
{
  buttonPressed = false;
  // Export the pin
  writeGPIO("export", "11");
  // sleep(1);
  // Set the pin as an output
  writeGPIO("gpio11/direction", "in");
  // Export the pin
  writeGPIO("export", "10");
  // sleep(1);
  // Set the pin as an output
  writeGPIO("gpio10/direction", "in");
  // Export the pin
  writeGPIO("export", "9");
  // sleep(1);
  // Set the pin as an output
  writeGPIO("gpio9/direction", "in");

}

RotaryEncoder::~RotaryEncoder()
{
  if (rotaryThread.joinable()) {
    rotaryThread.join();
  }
}

void RotaryEncoder::RotaryThreadFunction()
{
  // GPIO gpio;
  // gpio.SetMode(GPIO_11, INPUT);
  // gpio.SetMode(GPIO_9, INPUT);
  uint8_t sequence = 0x00;
  bool buttonAlreadyPressed = false;
  while (threadRunning) {
    // std::cout << "Rotary threadcycle\n";
    // A = (uint8_t)gpio.Get(GPIO_11);
    // B = (uint8_t)gpio.Get(GPIO_9);
    A = readGPIO("11");
    B = readGPIO("9");
    // if (A != prevA || B != prevB) {
    sequence <<= 1;
    sequence |= (uint8_t)A;
    sequence <<= 1;
    sequence |= (uint8_t)B;
    // }
    // Button = (uint8_t)gpio.Get(GPIO_10);
    Button = readGPIO("10");
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
      // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Check for right sequence: 10 -> 11 -> 01 -> 00
    if ((sequence & 0b00001111) == 0b00001011/*0b10110100*/) {
      prevA = 0;
      prevB = 0;
      right = true;
      onRight();
      log(Severity::info, "Rotary encoder is turned right. prev A, B: " + std::to_string(prevA) + ", " + std::to_string(prevB) +  " A, B: " + std::to_string(A) + ", " + std::to_string(B) + " Sequence: " + std::to_string(sequence) );
      // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    if (Button) {
      auto buttonPressTime = std::chrono::steady_clock::now();
      auto currentTime = std::chrono::steady_clock::now();
      auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - buttonPressTime).count();

      if (elapsedTime >= 500) {
        // Button held for more than 500ms
        if (!buttonHeld) {
          buttonHeld = true;
          onButtonHold();
        }
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      if (readGPIO("10") && !buttonAlreadyPressed) {
        buttonHeld = false;
        buttonPressed = true;
        onButtonPress();
        log(Severity::info, "Rotary encoder is pressed.");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        buttonPressTime = std::chrono::steady_clock::now();

        buttonAlreadyPressed = true;
      }
      else {
        // Reset the flag when the button is not pressed
        buttonAlreadyPressed = false;
      }
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
  this->onButtonPress = onButtonHold;
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