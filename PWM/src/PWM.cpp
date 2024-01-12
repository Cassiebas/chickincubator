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
  // std::cout << "dutyCycle: " << dutyCycle << "\n";
}

PWM::~PWM() {
  Stop();  
}

void PWM::SetDutyCycle(const unsigned int dutyCycle) {
  this->dutyCycle = dutyCycle;
  dutyCycleCounter = dutyCycle; //disrupt ongoing cycle
  // std::cout << "dutyCycle: " << dutyCycle << "\n";
}

void PWM::SetPeriod(const double period) {
  this->period = period;
}

void PWM::Start() {
  // std::cout << "Starting PWM...\n";
  running = true;
  dutyCycleCounter = dutyCycle;
  timer->Start();
}

void PWM::Stop() {
  // std::cout << "Stopping PWM...\n";
  running = false;
  timer->Stop();
  Off();
}

void PWM::OnTick() {
  // std::cout << "PWM::OnTick() \n" << running << " " << dutyCycle << " " << dutyCycleCounter << "\n";
  if (running) {
    if (dutyCycleCounter == (int)dutyCycle && dutyCycle > 0) {
      On();
    }
    else if (dutyCycleCounter == 0) {
      Off();
    }
    dutyCycleCounter -= 1;
    if (dutyCycleCounter - (int)dutyCycle <= -100) {
      dutyCycleCounter = dutyCycle;
    }
  }
}