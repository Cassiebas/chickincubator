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
      private:
        double kp;

      public:
        P(double kp);
        double operator()(double error);
    };

    class I
    {
      private:
        double ki;
        double sum = 0;
        double lastTime = 0;

      public:
        I(double ki);
        double operator()(double error, double time);
    };

    class D
    {
      private:
        double kd;
        double lastTime = 0;
        double lastError = 0;

      public:
        D(double kd);
        double operator()(double error, double time);
    };

    P p;
    I i;
    D d;
    double error, min, max;
    double ambientTemp;

  public:
    PIDController(double temperature, double kp, double ki, double kd, double min = 0, double max = 100);
    double operator()();
    double ToPercentPower(double pidValue);
    void Do() override;
    void Start();
    void Stop();
};

#endif