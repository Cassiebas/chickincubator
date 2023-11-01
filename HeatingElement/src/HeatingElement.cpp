#include "../includes/HeatingElement.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> 

<<<<<<< Updated upstream
HeatingElement::HeatingElement(const std::string pinNumber) :
  pin(pinNumber),
  path("/sys/class/gpio/")
=======
#define GPIO_PATH "/sys/class/gpio/"

HeatingElement::HeatingElement(std::string pinNumber) :
  pin(pinNumber),
  path(std::string(GPIO_PATH) + "gpio" + pin + "/")
>>>>>>> Stashed changes
{
  // Export the pin
  writeGPIO("export", pin);
  sleep(1);
  // Set the pin as an output
  writeGPIO("gpio" + pin + "/direction", "out");
}

void HeatingElement::writeGPIO(const std::string filename, const std::string value)
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

void HeatingElement::startHeating()
{
  // Set the pin to LOW to start the heating element
  writeGPIO("gpio" + pin + "/value", "0");
}

void HeatingElement::stopHeating()
{
  // Set the pin to HIGH to stop the heating element
  writeGPIO("gpio" + pin + "/value", "1");
}