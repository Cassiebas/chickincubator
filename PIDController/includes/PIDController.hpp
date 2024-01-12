#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include <iostream>
#include <vector>
#include "HeaterController.hpp"

class PIDController : public HeaterController
{ 
  private:
    class P
    {
      public:
        double kp;
        Log &log;
        P(double kp, Log &log);
        double operator()(double error);
    };

    class I
    {
      public:   
        double sum = 0;
        double lastTime = 0;
        double ki;
        Log &log;
        I(double ki, Log &log);
        double operator()(double error, double time);
    };

    class D
    {
      public:
        double lastTime = 0;
        double lastError = 0;
        double kd;
        Log &log;
        D(double kd, Log &log);
        double operator()(double error, double time);
    };

    P p;
    I i;
    D d;
    Plotter pidPlot;
    Plotter powerPlot;
    Plotter componentPlot;
    double error, min, max;
    double ambientTemp, avgTemp;
    double pRes, iRes, dRes;
    Log log;

  public:
    PIDController(double temperature, double kp, double ki, double kd, double min = 0, double max = 100);
    double operator()();
    void operator()(double Kp, double Ki, double Kd);
    double ToPercentPower(double pidValue);
    void Do() override;
    void Start();
    void Stop();
    void SetTemp(double temp);
    double GetAvgTemp();
    void ExportConstants();
};

#endif