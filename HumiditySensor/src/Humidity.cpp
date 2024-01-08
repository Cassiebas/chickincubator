#include "Humidity.hpp"
#include <string>

Humidity::Humidity() :
  filename("/dev/i2c-1")
{
  fd = open(filename, O_RDWR);
  if (fd < 0) {
    std::cerr << "Error opening I2C device." << std::endl;
    return;
  }

  if (ioctl(fd, I2C_SLAVE, 0x28) < 0) {
    std::cerr << "Error setting I2C address." << std::endl;
    close(fd);
    fd = -1;
  }
  humidity = 0;
}

Humidity::~Humidity()
{
  close(fd);
}

unsigned int Humidity::Read()
{
  const int bufferSize = 3;
  char buffer[bufferSize] = {0};

  if (read(fd, buffer, sizeof(buffer)) != sizeof(buffer)) {
    std::cerr << "Error reading from I2C." << std::endl;
    return humidity;
  }

  // Assuming buffer contains the humidity data in the desired format
  humidity = std::stoi(buffer);
  return humidity;
}