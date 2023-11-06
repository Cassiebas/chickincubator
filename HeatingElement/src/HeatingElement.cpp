#include "../includes/HeatingElement.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> 
#include <math.h>

HeatingElement::HeatingElement(const std::string pin_number, Timer *timer) :
  pin(pin_number),
  path("/sys/class/gpio/")
{
  this->timer = *timer;
  // Export the pin
  writeGPIO("export", pin);
  sleep(1);
  // Set the pin as an output
  writeGPIO("gpio" + pin + "/direction", "out");
  //make sure heater is off
  Stop();
}

void HeatingElement::startThread(unsigned int percentage_duty_cycle){
  heatingThread = std::thread([this, percentage_duty_cycle] (){
    int duty_cycle = percentage_duty_cycle;
    while(true) {
      if (std::fmod(timer.Elapsed(), INTERVAL) < 0.0001) {
        if(duty_cycle > 0){
          duty_cycle -= 1;
          if(!On())
          {
            //error
          }
        }
        else{
          duty_cycle -= 1;
          if(!Off()){
            //error
          }
          if (abs(duty_cycle) + percentage_duty_cycle == 100) {
            duty_cycle = percentage_duty_cycle;
          }
        }
      }
    }
  });
}

void HeatingElement::stopThread() {
  if (heatingThread.joinable()) {
    heatingThread.join();
  }
}

bool HeatingElement::writeGPIO(const std::string filename, const std::string value)
{
  std::ofstream file((path + filename).c_str());

  if (file.is_open())
  {
    file << value;
    file.close();
    return 1;
  }
  else{
    std::cerr << "Unable to open file: " + (path + filename) << std::endl;
    return -1;
  }
}

bool HeatingElement::On()
{
  // Set the pin to LOW to start the heating element
  return writeGPIO("gpio" + pin + "/value", "1");
}

bool HeatingElement::Off()
{
  // Set the pin to HIGH to stop the heating element
  return writeGPIO("gpio" + pin + "/value", "0");
}

bool HeatingElement::Start()
{
  return On();
}

bool HeatingElement::Stop()
{
  return Off();
}