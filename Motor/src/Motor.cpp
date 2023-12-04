#include "Motor.hpp"

Motor::Motor() :
  filename("/dev/i2c-1"),
  address(0x60)
{
  fd = Open_I2C();
  WriteConfig();
}

Motor::~Motor()
{
  close(fd);
}

void Motor::WriteConfig()
{
  char faultdata = configBits["FAULT"]; //FAULT registry
  std::cout << "Write Config Motor: " << (int)faultdata << "\n";
  if (read(fd, &faultdata, 1) != 1) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return;
  }
  else {
    std::cout << (int)faultdata << "\n";
  }

  data[0] = configBits["FAULT"]; //FAULT registry
  data[1] = configBits["clear"]; //clear
  if (write(fd, data, 2) != 2) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return;
  }

  data[0] = configBits["CONTROL"]; //CONTROL registry
  data[1] = configBits["5v"] | configBits["brake"]; //5v and brakes
  if (write(fd, data, 2) != 2) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return;
  }
  usleep(0.5*1000000);
}

int Motor::Open_I2C() {
  int file = open(filename, O_RDWR);
  if (file < 0) {
    std::cerr << "Failed to open the bus." << std::endl;
    return -1;
  }

  if (ioctl(file, I2C_SLAVE, address) < 0) {
    std::cerr << "Failed to acquire bus access and/or talk to slave." << std::endl;
    return -1;
  }
  return file;
}

bool Motor::Forward() {
  data[0] = configBits["CONTROL"]; //CONTROL registry
  data[1] = configBits["5v"] | configBits["forward"]; //5v and brakes
  if (write(fd, data, 2) != 2) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}

bool Motor::Backward() {
  data[0] = configBits["CONTROL"]; //CONTROL registry
  data[1] = configBits["5v"] | configBits["backward"]; //5v and brakes
  if (write(fd, data, 2) != 2) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}

bool Motor::Brake() {
  data[0] = configBits["CONTROL"]; //CONTROL registry
  data[1] = configBits["5v"] | configBits["brake"]; //5v and brakes
  if (write(fd, data, 2) != 2) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}

bool Motor::Coast() {
  data[0] = configBits["CONTROL"]; //CONTROL registry
  data[1] = configBits["5v"] | configBits["coast"]; //5v and brakes
  if (write(fd, data, 2) != 2) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return false;
  }
  return true;
}