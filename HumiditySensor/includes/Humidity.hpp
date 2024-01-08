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

    unsigned int humidity;

  public:
    Humidity();
    ~Humidity();  
    unsigned int Read();
};

#endif