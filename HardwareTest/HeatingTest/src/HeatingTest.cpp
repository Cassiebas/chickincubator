#include "../../HeatingElement/includes/HeatingElement.hpp"
#include "../../Thermistor/includes/Thermistor.hpp"
#include <iostream>

#define HEATER_GPIO "12" 

int main(){
  Thermistor temperature;
  HeatingElement heater(HEATER_GPIO);
  heater.stopHeating();

  while(1) {
    temperature.ReadTemperature();
    sleep(1);
  }
  // heater.startHeating();
  // sleep(3);
  return 0;
}