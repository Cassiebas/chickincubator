#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <math.h>

class Thermistor
{
  private:
    // Steinhart coefficients
    float a;
    float b;
    float c;

    // Use the appropriate I2C bus number
    const char *filename;

    // File descriptor to open and read I2C Bus
    int fd;

    // ADC address
    int address;

    char config[3]; // 16-bit configuration

    void InitializeConfig();

  public:
    Thermistor();

    // Open the I2C ADC bus and address
    int Open_I2C_ADC();
    // Read from the I2C ADC address file
    void ReadTemperature();
};

#endif