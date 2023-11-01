#include "../includes/HeatingElement.hpp"
#include <iostream>
#include <fstream>
#include <string>

#define GPIO_PATH "/sys/class/gpio/"

HeatingElement::HeatingElement(const std::string &pin) :
  pin(pin),
  path(std::string(GPIO_PATH) + "gpio" + pin + "/")
{
  // Export the pin
  writeGPIO("export", pin);

  // Set the pin as an output
  writeGPIO("direction", "out");
}

void HeatingElement::writeGPIO(const std::string &filename, const std::string &value)
{
  std::ofstream file((path + filename).c_str());
  if (!file)
  {
    std::cerr << "Unable to open file: " + filename << std::endl;
    return;
  }
  file << value;
  file.close();
}

void HeatingElement::startHeating()
{
  // Set the pin to LOW to start the heating element
  writeGPIO("value", "0");
}

void HeatingElement::stopHeating()
{
  // Set the pin to HIGH to stop the heating element
  writeGPIO("value", "1");
}