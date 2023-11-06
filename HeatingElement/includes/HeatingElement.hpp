#ifndef HEATING_ELEMENT_H
#define HEATING_ELEMENT_H

#include "Timer.hpp"

#include <string>
#include <thread>

class HeatingElement {
  private:
    const double INTERVAL = 0.01;
    int duty_cycle = 0;
    std::string pin;
    std::string path;
    Timer timer;
    std::thread heatingThread;
    
    void ThreadPwm();
    bool writeGPIO(const std::string filename, const std::string value);
    bool On();
    bool Off();

  public:
    HeatingElement(const std::string pin);
    void operator()(unsigned int percentage_duty_cycle);
    void Start();
    void Stop();
};

#endif