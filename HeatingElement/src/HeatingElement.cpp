#include "HeatingElement.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> 
#include <math.h>

HeatingElement::HeatingElement(const std::string pin_number) :
  pin(pin_number),
  path("/sys/class/gpio/")
{
  writeGPIO("export", pin);
  sleep(1);
  writeGPIO("gpio" + pin + "/direction", "out");
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

bool HeatingElement::writeGPIO(const std::string filename, const std::string value)
{
  std::ofstream file((path + filename).c_str());

  if (file.is_open())
  {
    file << value;
    file.close();
    return 1;
  }
  else{
    std::cerr << "Unable to open file: " + (path + filename) << std::endl;
    return -1;
  }
}

void HeatingElement::On()
{
  // Set the pin to LOW to start the heating element
  writeGPIO("gpio" + pin + "/value", "1");
  // std::cout << "Heater::On()\n";
}

void HeatingElement::Off()
{
  // Set the pin to HIGH to stop the heating element
  writeGPIO("gpio" + pin + "/value", "0");
  // std::cout << "Heater::Off()\n";
}