#include "HeatingElement.hpp"
#include "Thermistor.hpp"
#include "Timer.hpp"
#include "HarryPlotter"
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
  Thermistor temp[2] = {Thermistor(ADC::A0), Thermistor(ADC::A1)};
  HeatingElement heater(HEATER_GPIO, "89", "1"); //89% over 1s
  Timer timer;
  Plotter plot[2];
  float interval = 0.1; //100ms

  timer.Start();
  heater.Start();
  
  while(timer.Elapsed()/60.0 < 45.0) {
    std::cout << "A0 temperature: " << temp[0].Temperature() << "°C\n";
    std::cout << "A1 temperature: " << temp[1].Temperature() << "°C\n";
    std::cout << "Elapsed time: " << timer.Elapsed() << "s" << std::endl;
    plot[0].AddPoint(timer.Elapsed()/60.0, temp[0].Temperature());
    plot[1].AddPoint(timer.Elapsed()/60.0, temp[1].Temperature());
  }
  timer.Stop();
  heater.Stop();
  std::cout << timer.Duration() << std::endl;
  plot[0].ExportAsPNG("", "A0", "Time (m)", "Temperature (°C)", "T(s)");
  plot[1].ExportAsPNG("", "A1", "Time (m)", "Temperature (°C)", "T(s)");
  // heater.startHeating();
  // sleep(3);
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