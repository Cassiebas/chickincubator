#include "HeatingElement.hpp"
#include "Thermistor.hpp"
#include "GPIO.hpp"
#include "Timer.hpp"
#include "HarryPlotter"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
  GPIO gpio("/dev/my_gpio_driver");

  gpio.setPinState(GPIO_5, '1');

  std::cout << "Pin state of " << GPIO_5 << " is: "<< gpio.readPinState(GPIO_5) << std::endl;

  return 0;
}