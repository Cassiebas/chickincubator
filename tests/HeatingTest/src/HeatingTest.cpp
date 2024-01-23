#include "HeatingElement.hpp"
#include "Thermistor.hpp"
#include "Timer.hpp"
#include "HarryPlotter"
#include "GPIO.hpp"

#include <iostream>

#define HEATER_GPIO "12"

int main(){
 // Thermistor temp[2] = {Thermistor(ADC::A0), Thermistor(ADC::A1)};
  HeatingElement heater(HEATER_GPIO);
  Timer timer;
  GPIO gpio;
  //Plotter plot[2];

  timer.Start();
  heater(100);
  heater.Start();

  while(timer.Elapsed()/60.0 < 1.0) {
    std::cout << "Heating state: " << gpio.Get(HEATER_GPIO) << std::endl;
    // std::cout << "A0 temperature: " << temp[0].Temperature() << "°C\n";
    // std::cout << "A1 temperature: " << temp[1].Temperature() << "°C\n";
    // std::cout << "Elapsed time: " << timer.Elapsed() << "s" << std::endl;
    // plot[0].AddPoint(timer.Elapsed()/60.0, temp[0].Temperature());
    // plot[1].AddPoint(timer.Elapsed()/60.0, temp[1].Temperature());
  }
  timer.Stop();
  heater.Stop();
  std::cout << timer.Duration() << std::endl;
  std::cout << "Heating state: " << gpio.Get(HEATER_GPIO) << std::endl;
  // plot[0].ExportAsPNG("", "A0", "Time (m)", "Temperature (°C)", "T(s)");
  // plot[1].ExportAsPNG("", "A1", "Time (m)", "Temperature (°C)", "T(s)");
  // heater.startHeating();
  // sleep(3);
}