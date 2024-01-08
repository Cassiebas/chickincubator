#include "PWM.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> 
#include <math.h>

PWM::PWM(unsigned int dutyCycle, double period, std::function<void()> OnFunction, std::function<void()> OffFunction) :
  dutyCycle(dutyCycle),
  period(period),
  On(OnFunction),
  Off(OffFunction),
  timer(new Timer([this]() { this->OnTick(); }, this->period/100.0)) 
{
  
}

PWM::~PWM() {
  Stop();  
  if (PWMThread.joinable()) {
    PWMThread.join();
  }
}

void PWM::SetDutyCycle(const unsigned int dutyCycle) {
  this->dutyCycle = dutyCycle;
}

void PWM::SetPeriod(const double period) {
  this->period = period;
}

void PWM::Start() {
  std::cout << "Starting PWM...\n";
  running = true;
  dutyCycleCounter = dutyCycle;
  timer->Start();
}

void PWM::Stop() {
  std::cout << "Stopping PWM...\n";
  running = false;
  timer->Stop();
  Off();
}

void PWM::OnTick() {
  if(running) {
    if(dutyCycleCounter >= 0) {
      dutyCycleCounter -= 1;
      On();
    }
    else {
      dutyCycleCounter -= 1;
      Off();
      if (abs(dutyCycleCounter) + dutyCycle >= 100) {
        dutyCycleCounter = dutyCycle;
      }
    }
  }
}