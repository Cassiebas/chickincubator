#include "Timer.hpp"
#include <iostream>
#include <math.h>

Timer::Timer() :
  timerType(Type::NORMAL)
{ 

};

Timer::~Timer() { 

};

Timer::Timer(Type type) : 
  timerType(type)
{ 

};

Timer::Timer(std::function<void()> OnInterrupt, double intervalS) : //interval in seconds
  timerType(Type::INTERRUPT), OnInterrupt(OnInterrupt), interval(intervalS)
{ 

};

void Timer::Start()
{
  start = std::chrono::steady_clock::now();
  switch (timerType) {
    case Type::INTERRUPT:
      threadRunning = true;
      timerThread = std::thread(&Timer::ThreadCycle, this);
      break;
    default:
      break;
  }
}

void Timer::Reset()
{
  start = std::chrono::steady_clock::now();
}

void Timer::Stop()
{  
  end = std::chrono::steady_clock::now();
  duration = end - start;
  switch (timerType) {
    case Type::INTERRUPT:  
      threadRunning = false;
      if (timerThread.joinable()) {
        timerThread.join();
      }
      break;
    default:
      break;
  }
}

double Timer::Duration()
{
  return duration.count();
}

double Timer::Elapsed()
{
  elapsed_time = std::chrono::steady_clock::now() - start;
  return elapsed_time.count();
}

void Timer::ThreadCycle() { 
  while (threadRunning) {
    // std::cout << "Timer threadcycle\n";
    if (Elapsed() >= interval) {
      OnInterrupt();
      Reset(); 
    }
  }
}