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
    std::map<std::string, char> configBits = {
                                                {"CONTROL", 0x00},
                                                {"5v", 0b11110100/*0b11111100*/}, //we only need 5v, but copying this over from the datasheet should be easy
                                                {"3.3v", 0b10100100},
                                                {"1v", 0b00110100},
                                                {"forward", 0b00000001},
                                                {"backward", 0b00000010},
                                                {"brake", 0b00000011},
                                                {"coast", 0b00000000},
                                                {"FAULT", 0x01},
                                                {"clear", 0b10000000}
    };
    // Use the appropriate I2C bus number
    const char *filename;

    // File descriptor to open and read I2C Bus
    int fd;

    int address;

    char data[2]; // 16-bit configuration

    void WriteConfig();
    // Open the I2C ADC bus and address
    int Open_I2C();

  public:
    Motor();
    ~Motor();  
    bool Forward();
    bool Backward();
    bool Brake();
    bool Coast();
};
#endif