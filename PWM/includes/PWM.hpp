#ifndef PWM_HPP
#define PWM_HPP

#include "Timer.hpp"

#include <string>
#include <thread>
#include <map>
#include <functional>

class PWM {
  private:
    unsigned int dutyCycle;
    double period;
    std::function<void()> On;
    std::function<void()> Off;

    bool running;
    int dutyCycleCounter;
    Timer *timer;
    std::thread PWMThread;

    void OnTick();
  public:
    PWM() : On(nullptr), Off(nullptr) {};
    PWM(unsigned int dutyCycle, double period, std::function<void()> OnFunction, std::function<void()> OffFunction);
    ~PWM();

    void Start();
    void Stop();
    void SetDutyCycle(const unsigned int dutyCycle);
    void SetPeriod(const double period);
};

#endif