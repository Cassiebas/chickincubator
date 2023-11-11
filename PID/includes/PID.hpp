#ifndef PID_HPP
#define PID_HPP

#include <iostream>

class PID
{ 
  private:
    class P
    {
      private:
        double kp;

      public:
        P(double kp) : kp(kp) {}

        double operator()() const
        {
          // Perform proportional calculation here
          return kp; //* some_input_value
        }
    };

    class I
    {
      private:
        double ki;

      public:
        I(double ki) : ki(ki) {}

        double operator()() const
        {
          // Perform integral calculation here
          return ki; //* some_input_value_accumulated
        }
    };

    class D
    {
      private:
        double kd;

      public:
        D(double kd) : kd(kd) {}

        double operator()() const
        {
          // Perform derivative calculation here
          return kd;// * (some_input_value - previous_input_value);
        }
    };

    P p;
    I i;
    D d;

  public:
    PID(double kp, double ki, double kd) : p(kp), i(ki), d(kd) {}

    double operator()() const
    {
      // Sum up the P, I, and D components
      return p() + i() + d();
    }
};

#endif