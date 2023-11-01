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

    // ADC address
    int address;

    // Set the configuration bytes for continuous conversion mode
    char config[3] = {1, 0b10000100, 0b10000101};
    config[0] = {1}; //config register
    config[1] = {0b10000100}; // 15-8
    /*  
    Bits 14-12 input selection:
      100 ANC0; 101 ANC1; 110 ANC2; 111 ANC3
    Bit 8 Operational mode of the ADS1115.
      0 : Continuous conversion mode
      1 : Power-down single-shot mode
    */
    config[2] = {0b10000101}; // 7-0
    /* 
      Bits 7-5 data rate:
        default to 100 for 128SPS
      Bits 4-0  comparator functions see data sheet.
     */

  public:
    Thermistor();

    // Open the I2C ADC bus and address
    int Open_I2C_ADC();
    // Read from the I2C ADC address file
    void ReadTemperature(int file);
};

#endif