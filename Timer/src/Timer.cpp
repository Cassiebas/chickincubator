#include "../includes/Timer.hpp"
#include <iostream>

void Timer::Start()
{
  start = std::chrono::steady_clock::now();
}

void Timer::End()
{
  end = std::chrono::steady_clock::now();
  duration = end - start;
}

void Timer::Stop()
{
  End();
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