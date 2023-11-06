#ifndef PWM_HPP
#define PWM_HPP

#include "Timer.hpp"

#include <string>
#include <thread>

class PWM {
  private:
    int duty_cycle = 0;
    int period = 0;
    
    std::string pin;
    std::string path;

  public:
    PWM(const std::string pin);

};

#endif