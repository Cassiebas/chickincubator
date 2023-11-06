#include "../../HeatingElement/includes/HeatingElement.hpp"
#include "../../Thermistor/includes/Thermistor.hpp"
#include "../../Timer/includes/Timer.hpp"
#include <iostream>
#include <thread>
#include <mutex>


#define HEATER_GPIO "12" 

std::mutex dutyCycleMutex;
unsigned int duty_cycle = 0;

void softPwm(float interval, HeatingElement &heater, Timer &timer) {
  while(timer.getElapsedTime() < interval) {
    dutyCycleMutex.lock(); // Acquire the lock
    if(duty_cycle > 0){
      duty_cycle =- duty_cycle;
      heater.startHeating();
    }
    else{
      heater.stopHeating();
    }
    dutyCycleMutex.unlock(); // Release the lock
  }
}

int main(){
  Thermistor temperature;
  HeatingElement heater(HEATER_GPIO);
  Timer timer;
  float interval = 0.1; //100ms

  std::thread threadedPwm(softPwm, interval, std::ref(heater), std::ref(timer));
  timer.startTimer();
  while(1) {
    temperature.ReadTemperature();
    //TODO update duty cycle in main code
    {
      // Modify the duty_cycle variable here
    }

    std::cout << timer.getElapsedTime() << std::endl;
  }

  timer.endTimer();
  std::cout << timer.getDuration() << std::endl;
  return 0;
}