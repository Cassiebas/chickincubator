#include <iostream>
#include "Motor.hpp"
#include "Timer.hpp"

#define EGGFULLROT 7.58473625144 // seconds to rotate egg for 360 degrees, theoretical value with 1:1 relationship of how much the big gear spins and the egg spins

bool braking = false;

void stopMotor()
{
  braking = true;
}

int main()
{
  std::cout << "How many degrees should the eggs turn?\n";
  double deg;
  std::cin >> deg;
  Motor motor;
  Timer timer(&stopMotor, EGGFULLROT * (deg / 360.0));
  timer.Start();
  motor.Forward();
  while (!braking);
  motor.Brake();
  // std::cout << "Forward\n";
  // while(timer.Elapsed() < 30);
  // motor.Coast();
  // std::cout << "Coast\n";
  // while(timer.Elapsed() < 36);
  // motor.Backward();
  // std::cout << "Backward\n";
  // while(timer.Elapsed() < 69);
  // motor.Brake();
  // std::cout << "Brake\n";
  // timer.Stop();
  timer.Stop();
  return 0;
}