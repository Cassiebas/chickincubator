#include "HeatingElement.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> 
#include <math.h>

HeatingElement::HeatingElement(const std::string pin_number) :
  pin(pin_number)
{
  gpio.SetMode(pin, OUTPUT);
  pwm = new PWM(100, 10, [this]() { this->On(); }, [this]() { this->Off(); }); //pass those methods baby

  //make sure heater is off
  Off();
}

void HeatingElement::Start() {
  pwm->Start();
}

void HeatingElement::Stop() {
  pwm->Stop();
}

void HeatingElement::operator()(unsigned int percentage) {
  pwm->SetDutyCycle(percentage);
}

void HeatingElement::On()
{
  // Set the pin to HIGH to start the heating element
  gpio.Set(pin, 1);
  // std::cout << "Heater::On()\n";
}

void HeatingElement::Off()
{
  // Set the pin to LOW to stop the heating element
  gpio.Set(pin, 0);
  // std::cout << "Heater::Off()\n";
}