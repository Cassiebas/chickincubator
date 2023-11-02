#include "../includes/HeatingElement.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> 

HeatingElement::HeatingElement(const std::string pinNumber, const std::string dutyCycle, const std::string period) :
  pin(pinNumber),
  path("/sys/class/gpio/")

{
  // Export the pin
  writeGPIO("export", pin);
  sleep(1);
  // Set the pin as an output
  writeGPIO("gpio" + pin + "/direction", "out");
  // writeGPIO("gpio" + pin + "/duty_cycle", dutyCycle);
  // writeGPIO("gpio" + pin + "/period", period);
  // writeGPIO("gpio" + pin + "/inversion", "1");
  Stop(); //make sure heater is off
}

void HeatingElement::writeGPIO(const std::string filename, const std::string value)
{
  std::ofstream file((path + filename).c_str());

  if (!file.is_open())
  {
    std::cerr << "Unable to open file: " + (path + filename) << std::endl;
    return;
  }
  file << value;
  file.close();
}

void HeatingElement::Start()
{
  // Set the pin to LOW to start the heating element
  writeGPIO("gpio" + pin + "/value", "1");
}

void HeatingElement::Stop()
{
  // Set the pin to HIGH to stop the heating element
  writeGPIO("gpio" + pin + "/value", "0");
}