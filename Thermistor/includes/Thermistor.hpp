#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <math.h>

namespace ADC {
  enum channel {
    A0,
    A1,
    A2,
    A3
  };
}

class Thermistor
{
  private:
    const char channelConfig[4] = {0b01000000, 0b01010000, 0b01100000, 0b01110000};
    // Steinhart coefficients
    double a;
    double b;
    double c;

    // Use the appropriate I2C bus number
    const char *filename;

    // File descriptor to open and read I2C Bus
    int fd;

    // ADC address
    int address;
    ADC::channel channel;

    char config[3]; // 16-bit configuration

    void WriteConfig();

  public:
    Thermistor(ADC::channel chosenChannel);
    ~Thermistor();
    
    // Open the I2C ADC bus and address
    int OpenADC();
    // Read from the I2C ADC address file
    double Temperature();
};

#endif