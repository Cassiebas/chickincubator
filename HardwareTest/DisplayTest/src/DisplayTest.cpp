#include "Display.hpp"

#include <iostream>
#include <unistd.h>  

int main(){
  Display display;

  display.oled_draw_pixel(1, 0, 1);
  display.oled_draw_pixel(2, 0, 1);
  display.oled_draw_pixel(3, 0, 1);
  display.oled_draw_pixel(4, 0, 1);

  display.update();
  sleep(10);
  display.oled_draw_pixel(4, 10, 1);
  display.oled_draw_pixel(4, 10, 1);
  display.oled_draw_pixel(4, 10, 1);
  display.oled_draw_pixel(4, 10, 1);
  display.update();
  sleep(10);
  return 0;
}