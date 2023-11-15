#include "HeatingElement.hpp"
#include "Thermistor.hpp"
#include "GPIO.hpp"
#include "Timer.hpp"
//#include "HarryPlotter"
#include "PID.hpp"
#include "RotaryEncoder.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
  RotaryEncoder encoder;
  while (1) {
    if (encoder.isLeft()) {
      printf("left\n");
    } else if (encoder.isRight()) {
      printf("right\n");
    } else if (encoder.isButtonPressed()) {
      printf("button is pressed\n");
    }
  }
  return 0;
}