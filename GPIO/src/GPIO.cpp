#include "../includes/GPIO.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

GPIO::GPIO()
{
  // fd = open("/sys/class/gpio/", O_RDWR); //TODO: should be done in c++ style to get support for namespaces
  // if (fd < 0)
  // {
  //   printf("Error opening the device driver\n");
  // }
}

GPIO::~GPIO() 
{
  // close(fd);
}

bool GPIO::writeGPIO(const std::string filename, const std::string value)
{
  std::string path = "/sys/class/gpio/";
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

bool GPIO::SetMode(const std::string gpioPin, char ioValue)
{
  // Export the pin
  writeGPIO("export", gpioPin);
  sleep(1);
  
  // Set the pin as an output
  if (ioValue == INPUT) {
    return writeGPIO("gpio" + gpioPin + "/direction", "in");
  } else {
    return writeGPIO("gpio" + gpioPin + "/direction", "out");
  }
}

bool GPIO::SetMode(char gpioPin, char ioValue)
{
  return SetMode(std::string(1, gpioPin), ioValue);
}

bool GPIO::SetMode(int gpioPin, char ioValue)
{
  return SetMode(std::to_string(gpioPin), ioValue);
}

bool GPIO::Set(const std::string gpioPin, bool setValue)
{
  if (setValue) {
    return writeGPIO("gpio" + gpioPin + "/value", "1");
  } else {
    return writeGPIO("gpio" + gpioPin + "/value", "0");
  }
}

bool GPIO::Set(char gpioPin, bool setValue)
{
  return Set(std::string(1, gpioPin), setValue);
}

bool GPIO::Set(int gpioPin, bool setValue)
{
  return Set(std::to_string(gpioPin), setValue);
}

bool GPIO::Get(const std::string gpioPin)
{
  // Read the GPIO pin state
  std::ifstream valueFile("/sys/class/gpio/gpio" + gpioPin + "/value");
  if (!valueFile.is_open()) {
      throw std::runtime_error("Failed to open GPIO value file.");
  }
  int value;
  valueFile >> value;

  return (bool)value;
}

int GPIO::Get(char gpioPin)
{
  return Get(std::to_string(gpioPin));
}

int GPIO::Get(int gpioPin)
{
  return Get(std::to_string(gpioPin));
}