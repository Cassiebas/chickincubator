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

  try {
    humidity = std::stoi(buffer);
  } catch (const std::invalid_argument& e) {
    std::cerr << "Error converting string to integer: " << e.what() << std::endl;
    std::cerr << "Buffer content: " << buffer << std::endl;
    humidity = 0;
  }

  return humidity;
}