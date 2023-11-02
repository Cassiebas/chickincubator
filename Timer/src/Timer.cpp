#include "../includes/Timer.hpp"
#include <iostream>

void Timer::startTimer()
{
  start = std::chrono::steady_clock::now();
}

void Timer::endTimer()
{
  end = std::chrono::steady_clock::now();
  duration = end - start;
}

double Timer::getDuration()
{
  return duration.count();
}

double Timer::getElapsedTime()
{
  elapsed_time = std::chrono::steady_clock::now() - start;
  return elapsed_time.count();
}