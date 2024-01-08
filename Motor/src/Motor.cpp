#include "Motor.hpp"
#include <string.h>

Motor::Motor() :
  filename("/proc/motor"),
  address(0x60)
{
  fd = open(filename, O_RDWR);
  if (fd < 0) {
    std::cerr << "ERROR: Failed to open %s in read/write mode\n" << fd << std::endl;
  }
}

Motor::~Motor()
{
  close(fd);
}

bool Motor::Forward() {
  char command = '0';
  // send PWM value if needed
  if (write(fd, &command , 1) < 1) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}

bool Motor::Backward() {
  char command = '1';
  // send PWM value if needed
  if (write(fd, &command , 1) < 1) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}

bool Motor::Brake() {
  char command = '2';
  if (write(fd, &command , 1) < 1) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}