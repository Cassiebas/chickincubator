#include "../../HeatingElement/includes/HeatingElement.hpp"
#include "../../Thermistor/includes/Thermistor.hpp"
#include <iostream>

#define HEATER_GPIO "26" 

int main(){
  Thermistor temperature;
  HeatingElement heater(HEATER_GPIO);

  heater.startHeating();
  sleep(3);
  heater.stopHeating();
  return 0;
}