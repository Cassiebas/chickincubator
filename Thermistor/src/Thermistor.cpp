#include "../includes/Thermistor.hpp"

Thermistor::Thermistor(ADC::channel chosenChannel) :
  a(0.0011252566721075908),
  b(0.0002347204472978223),
  c(8.563052731505118*pow(10, -8)),
  filename("/dev/i2c-1"),
  address(0x48),
  channel(chosenChannel)
{
  fd = Open_I2C_ADC();
  WriteConfig();
}

Thermistor::~Thermistor()
{
  close(fd);
}

void Thermistor::WriteConfig()
{
  config[0] = 0x01;
  config[1] = 0b10000100; // 15-8
  config[1] |= channelConfig[channel]; 
  /*
  Bit 15 OS:
    On/ off bit  
  Bits 14-12 input selection:
    100 ANC0; 101 ANC1; 110 ANC2; 111 ANC3
  Bit 8 Operational mode of the ADS1115.
    0 : Continuous conversion mode
    1 : Power-down single-shot mode
  */
  config[2] = 0b10000010; // 7-0
  /* 
  Bits 7-5 data rate:
    default to 100 for 128SPS
  Bits 4-0  comparator functions see data sheet.
  */
  if (write(fd, config, 3) != 3) {
    std::cerr << "Error writing to the i2c bus." << std::endl;
    return;
  }
  usleep(0.5*1000000);
}

int Thermistor::Open_I2C_ADC() {
  int file = open(filename, O_RDWR);
  if (file < 0) {
    std::cerr << "Failed to open the bus." << std::endl;
    return -1;
  }

  if (ioctl(file, I2C_SLAVE, address) < 0) {
    std::cerr << "Failed to acquire bus access and/or talk to slave." << std::endl;
    return -1;
  }
  return file;
}

double Thermistor::Temperature() {
  WriteConfig();
  char reg[1] = {0x00};
  write(fd, reg, 1);
  char data[2]={0x00};
  if (read(fd, data, 2) != 2) {
    std::cerr << "Error reading from the i2c bus." << std::endl;
    return -273.16;
  }

  // Convert the 2byte data to 16-bits
  int adc_value = (data[0] * 256 + data[1]);
  // if (adc_value > 32767)
  // {
  //   adc_value -= 65535;
  // }
  double celsius = 1 / (a + b * log(adc_value) + c * pow(log(adc_value), 3)) - 273.15;

  // Print the resistance value
  // std::cout << "ADC A" << channel << ": " << adc_value << std::endl;
  // std::cout << "Celcius: " << celsius << std::endl;
  return celsius + 20; //offset :(
}