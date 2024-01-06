#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include <map>

class Motor
{
  private:
    // Use the appropriate I2C bus number
    const char *filename;
    int fd;
    int address;

  public:
    Motor();
    ~Motor();  
    bool Forward();
    bool Backward();
    bool Brake();
    // bool Coast();
};
#endif