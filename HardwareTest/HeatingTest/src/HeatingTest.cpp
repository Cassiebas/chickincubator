#include "../../HeatingElement/includes/HeatingElement.hpp"
#include "../../Thermistor/includes/Thermistor.hpp"
#include "../../Timer/includes/Timer.hpp"
#include <iostream>

#define HEATER_GPIO "12" 

int main(){
  Thermistor temperature;
  HeatingElement heater(HEATER_GPIO);
  Timer timer;
  heater.stopHeating();

  timer.startTimer();
  while(1) {
    temperature.ReadTemperature();
    sleep(1);
    std::cout << timer.getElapsedTime() << std::endl;
  }
  timer.endTimer();
  std::cout << timer.getDuration() << std::endl;
  // heater.startHeating();
  // sleep(3);
  return 0;
}