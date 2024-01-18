#include "GPIO.hpp"
#include <thread>
#include <unistd.h>
#include <iostream>

// void onLeft();
// void onRight();
// void onButtonPress();
// void onButtonHold();

int main() {
  GPIO gpio;
  gpio.SetMode(GPIO_11, INPUT);
  gpio.SetMode(GPIO_10, INPUT);
  gpio.SetMode(GPIO_9, INPUT);
  
  while(1){
    int result = gpio.Get("11");
    if (result < 0) {
      std::cerr << "Error reading GPIO pin: " << result << std::endl;
    } else {
      std::cout << "GPIO pin value: " << result << std::endl;
    }
    result = gpio.Get("10");
    if (result < 0) {
      std::cerr << "Error reading GPIO pin: " << result << std::endl;
    } else {
      std::cout << "GPIO pin value: " << result << std::endl;
    }
    result = gpio.Get('9');
    if (result < 0) {
      std::cerr << "Error reading GPIO pin: " << result << std::endl;
    } else {
      std::cout << "GPIO pin value: " << result << std::endl;
    }

    // printf("pin 11: %d\n", gpio.Get(GPIO_11));
    // printf("pin 10: %d\n", gpio.Get(GPIO_10));
    // printf("pin 9: %d\n", gpio.Get(GPIO_9));
    sleep(4);
  }

  return 0;
}

// void onLeft() {
//     std::cout << "Rotary turned left\n";
// }

// void onRight() {
//     std::cout << "Rotary turned right\n";
// }

// void onButtonPress() {
//     std::cout << "Rotary button pressed\n";
// }

// void onButtonHold() {
//     std::cout << "Rotary button was held\n";
// }
