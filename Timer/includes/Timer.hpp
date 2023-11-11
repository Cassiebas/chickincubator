#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <functional>
#include <thread>

class Timer {
  public:
    typedef enum Type {
      NORMAL,
      INTERRUPT
    } Type_t;
    Timer();
    ~Timer();
    Timer(Type type);
    Timer(std::function<void()> OnInterrupt, double interval);
    void Start();
    void Stop();
    void Reset();
    double Duration();
    double Elapsed();
  private:
    void ThreadCycle();
    bool threadRunning;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    std::chrono::duration<double> duration;
    std::chrono::duration<double> elapsed_time;
    Type timerType;
    std::function<void()> OnInterrupt;
    double interval;
    std::thread timerThread;
};

#endif