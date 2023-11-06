#ifndef HEATING_ELEMENT_H
#define HEATING_ELEMENT_H

#include "Timer.hpp"

#include <string>
#include <thread>

class HeatingElement {
  private:
    const double INTERVAL = 0.01;
    
    std::string pin;
    std::string path;
    Timer timer;
    std::thread heatingThread;
    
    bool writeGPIO(const std::string filename, const std::string value);
    bool On();
    bool Off();

  public:
    HeatingElement(const std::string pin, Timer *timer);
    void startThread(unsigned int duty_cycle);
    void stopThread();
    bool Start();
    bool Stop();
};

#endif