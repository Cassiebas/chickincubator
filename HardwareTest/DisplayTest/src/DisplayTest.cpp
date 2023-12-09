#include "Display.hpp"

#include <iostream>
#include <unistd.h>  

int main(){
  Display display;

  char line[25] = "Hoi";
  //char msg[200] = "alpha\nbravo\ncharlie\ndelta";

  // print text
  // if (msg[0] != 0)
  // {
  //   display.oled_write_string(1, msg);
  // }

  // sleep(10);
  display.oled_horizontal_flip(1);
  display.oled_clear_screen();


  return 0;
}