#include "HeatingElement.hpp"
#include "Thermistor.hpp"
#include "GPIO.hpp"
#include "Timer.hpp"
#include "HarryPlotter"
#include "PID.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
  PID pidController(0.1, 0.01, 0.001);
  double output = pidController();
  std::cout << output << std::endl;
  // Thermistor temp[2] = {Thermistor(ADC::A0), Thermistor(ADC::A1)};
  // Timer timer;
  // HeatingElement heater(HEATER_GPIO);
  
  // Plotter plot[2];
  // timer.Start();
  // heater(75);
  // heater.Start();
  // while(timer.Elapsed()/60.0 < 2.0) {
  //   std::cout << "A0 temperature: " << temp[0].Temperature() << "°C\n";
  //   std::cout << "A1 temperature: " << temp[1].Temperature() << "°C\n";
  //   std::cout << "Elapsed time: " << timer.Elapsed() << "s" << std::endl;
  //   plot[0].AddPoint(timer.Elapsed()/60.0, temp[0].Temperature());
  //   plot[1].AddPoint(timer.Elapsed()/60.0, temp[1].Temperature());
  // }
  // std::cout << "Stopping heater\n";
  // heater.Stop();
  // std::cout << "Stopping timer\n";
  // timer.Stop();

  // std::cout << timer.Duration() << std::endl;
  // plot[0].ExportAsPNG("", "A0", "Time (m)", "Temperature (°C)", "T(t)");
  // plot[1].ExportAsPNG("", "A1", "Time (m)", "Temperature (°C)", "T(t)");
  // std::cout << "Exported results\n";

  return 0;
}