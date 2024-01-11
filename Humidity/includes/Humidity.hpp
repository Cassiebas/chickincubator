#ifndef HUMIDITY_HPP
#define HUMIDITY_HPP

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

class Humidity
{
  private:
    // Use the appropriate I2C bus number
    const char *filename;
    int fd;
    uint8_t rxBuffer[5];  // receive buffer
    uint8_t txBuffer[5];  // transmit buffer
    ssize_t result;

    float humidity;

  public:
    Humidity();
    ~Humidity();  
    float Read();
};

#endif