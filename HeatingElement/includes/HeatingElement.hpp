#ifndef HEATING_ELEMENT_H
#define HEATING_ELEMENT_H

#include "Timer.hpp"
#include "PWM.hpp"
#include "GPIO.hpp"

#include <string>
#include <thread>

class HeatingElement {
  private:
    std::string pin;
    std::string path;
    Timer timer;
    GPIO gpio;
    PWM *pwm;
    
    bool writeGPIO(const std::string filename, const std::string value);

  public:
    HeatingElement(const std::string pin);
    void operator()(unsigned int percentage);
    void Start();
    void Stop();
    void On();
    void Off();
};

#endif