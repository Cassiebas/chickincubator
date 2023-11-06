#include "../includes/PWM.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> 
#include <math.h>

PWM::PWM(const std::string pin_number) :
  pin(pin_number),
  path("/sys/class/gpio/")
{

}