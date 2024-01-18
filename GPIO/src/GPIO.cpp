#include "../includes/GPIO.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

GPIO::GPIO()
{
  fd = open("/proc/gpio_driver", O_RDWR); //TODO: should be done in c++ style to get support for namespaces
  if (fd < 0)
  {
    printf("Error opening the device driver\n");
  }
}

GPIO::~GPIO() 
{
  close(fd);
}

bool GPIO::SetMode(const std::string &gpioPin, char ioValue)
{
  std::string buffer = gpioPin + ioValue;
  // Writing to GPIO driver
  retVal = write(fd, buffer.data(), buffer.size());
  if (retVal < 0)
  {
    printf("Error writing to the device file\n");
    close(fd);
    return -1;
  }
  return true; // Placeholder return value
}

bool GPIO::SetMode(char gpioPin, char ioValue)
{
  return SetMode(std::string(1, gpioPin), ioValue);
}

bool GPIO::SetMode(int gpioPin, char ioValue)
{
  return SetMode(std::to_string(gpioPin), ioValue);
}

bool GPIO::Set(const std::string &gpioPin, bool setValue)
{
  std::string buffer = gpioPin + (setValue ? "1" : "0");

  // Writing to GPIO driver
  retVal = write(fd, buffer.c_str(), buffer.size());
  if (retVal < 0)
  {
    std::cerr << "Error writing to the device file" << std::endl;
    close(fd);
    return false;
  }
  return true;
}

bool GPIO::Set(char gpioPin, bool setValue)
{
  return Set(std::string(1, gpioPin), setValue);
}

int GPIO::Get(const char *gpioPin)
{
  // Reading from the device file
  char read_buffer[3] = {0};
  sprintf(read_buffer, "%s", gpioPin);
  printf("Read character: %s\n", read_buffer);
  retVal = read(fd, read_buffer, sizeof(read_buffer));
  if (retVal < 0)
  {
    printf("Error reading from the device file\n");
    close(fd);
    return -1;
  }
  return read_buffer[0] - '0';
}

int GPIO::Get(char gpioPin)
{
  // Reading from the device file
  char read_buffer[2] = {0};
  read_buffer[0] = gpioPin;
  printf("Read character: %c\n", read_buffer[0]);
  
  retVal = read(fd, read_buffer, sizeof(read_buffer));
  if (gpioPin < 0)
  {
    printf("Error reading from the device file\n");
    close(fd);
    return -1;
  }
  return read_buffer[0] - '0';
}