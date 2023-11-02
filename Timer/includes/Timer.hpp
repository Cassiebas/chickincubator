#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
  private:
  std::chrono::steady_clock::time_point start;
  std::chrono::steady_clock::time_point end;
  std::chrono::duration<double> duration;
  std::chrono::duration<double> elapsed_time;

  public:
    void Start();
    void End();
    void Stop();
    double Duration();
    double Elapsed();
};

#endif