#include "../includes/Thermistor.hpp"

Thermistor::Thermistor() :
  a(0.0011252566721075908),
  b(0.0002347204472978223),
  c(8.563052731505118e-8),
  filename("/dev/i2c-1"),
  address(0x48){
    Open_I2C_ADC();
    InitializeConfig();
  }


void Thermistor::InitializeConfig()
{
    config[0] = 1; //config register
    config[1] = 0b10000100; // 15-8
    /*  
    Bits 14-12 input selection:
      100 ANC0; 101 ANC1; 110 ANC2; 111 ANC3
    Bit 8 Operational mode of the ADS1115.
      0 : Continuous conversion mode
      1 : Power-down single-shot mode
    */
    config[2] = 0b10000101; // 7-0
    /* 
      Bits 7-5 data rate:
        default to 100 for 128SPS
      Bits 4-0  comparator functions see data sheet.
     */
}

int Thermistor::Open_I2C_ADC() {
  int file;
  if ((file = open(filename, O_RDWR)) < 0) {
    std::cerr << "Failed to open the bus." << std::endl;
    return -1;
  }

  if (ioctl(file, I2C_SLAVE, address) < 0) {
    std::cerr << "Failed to acquire bus access and/or talk to slave." << std::endl;
    return -1;
  }

  if (write(file, config, 3) != 3) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return -1;
  }

  return file;
}

void Thermistor::ReadTemperature(int file) {
  // Read the data from the ADC
  char data[2] = {0};
  if (read(file, data, 2) != 2) {
    std::cerr << "Error reading from the i2c bus." << std::endl;
    return;
  }

  // Convert the 2byte data to 16-bits
  int16_t adc_value = (data[0] << 8) | data[1];

  float kelvin = 1 / (a + b * log(adc_value) + c * pow(log(adc_value), 3));

  float celsius = kelvin - 273.15;

  // Print the resistance value
  std::cout << "Celcius: " << celsius << std::endl;
}