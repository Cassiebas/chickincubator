#include "Humidity.hpp"
#include <string>
#include <algorithm>

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
  std::fill(rxBuffer, rxBuffer + 5, 0);
  std::fill(txBuffer, txBuffer + 5, 0);
}

Humidity::~Humidity()
{
  close(fd);
}

float Humidity::Read()
{
  txBuffer[0] = 0x00;
  if(write(fd, txBuffer , 1) != 1)
  {
    std::cerr << "no ACK bit!" << std::endl;
  }

  int ready;
  do
  {
    // Read the humidity data (4 bytes) from the sensor
    result = read(fd, rxBuffer, 4);

    // Check the status bits in the first byte to see if the data is ready
    ready = ((rxBuffer[0] & 0xC0 == 0) ? 1 : 0);
  } while (!ready);

  float HumidH = (rxBuffer[0] & 0b00111111);
  float HumidL = rxBuffer[1];
  humidity = ((HumidH * 256 + HumidL) / 16384) * 100;
  //int unfiltHumidity = ((rxBuffer[0] & 0x3f) << 8) + (rxBuffer[1] & 0xff);
  //int unfiltTemp = (((rxBuffer[2] & 0xff) << 8) + (rxBuffer[3] & 0xfc)) >> 2;
 //temp_d = ((unfiltTemp/16384.0) * 165.0) - 40.0; 

  return humidity;
}