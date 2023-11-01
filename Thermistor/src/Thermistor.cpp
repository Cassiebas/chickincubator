#include "../includes/Thermistor.hpp"

Thermistor::Thermistor() :
  a(0.0011252566721075908),
  b(0.0002347204472978223),
  c(8.563052731505118e-8),
  filename("/dev/i2c-1"),
  address(0x48){
    Open_I2C_ADC();
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