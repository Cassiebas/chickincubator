#include "Motor.hpp"
#include <string.h>

Motor::Motor() :
  filename("/dev/motor"),
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
  std::string data = std::string("forward") + " " + std::to_string(40);

  if (write(fd, data.c_str(), data.length()) != data.length()) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}

bool Motor::Backward() {
  std::string data = std::string("backward") + " " +std::to_string(40);

  if (write(fd, data.c_str(), data.length()) != data.length()) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}

bool Motor::Brake() {
  std::string data = std::string("brake");

  if (write(fd, data.c_str(), data.length()) != data.length()) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}