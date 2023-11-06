#include "../includes/GPIO.hpp"
#include <iostream>
#include <fstream>

GPIO::GPIO() :
 path("/sys/class/gpio/")
{
  BCM2835_BASE = (volatile uint32_t*)0x20000000;
  GPFSEL1 = BCM2835_BASE + 0x04;
  GPFSEL2 = BCM2835_BASE + 0x08;
  GPFSEL3 = BCM2835_BASE + 0x0C;
  GPFSEL4 = BCM2835_BASE + 0x10;
  GPFSEL5 = BCM2835_BASE + 0x14;

  GPIOSET0 = BCM2835_BASE + 0x1C;
  GPIOSET1 = BCM2835_BASE + 0x20;
  GPCLR0 = BCM2835_BASE + 0x28;
  GPCLR1 = BCM2835_BASE + 0x2C;
}

void GPIO::set(std::string pin, uint8_t bitfield)
{
  int pinNumber = std::stoi(pin);
  // Determine the appropriate GPFSEL register based on the pin number
  volatile uint32_t* GPFSEL_REGISTER;
  switch (pinNumber / 10) {
    case 0:
      GPFSEL_REGISTER = GPFSEL1;
      break;
    case 1:
      GPFSEL_REGISTER = GPFSEL2;
      break;
    case 2:
      GPFSEL_REGISTER = GPFSEL3;
      break;
    case 3:
      GPFSEL_REGISTER = GPFSEL4;
      break;
    case 4:
      GPFSEL_REGISTER = GPFSEL5;
      break;
    default:
      break;
  }


}
