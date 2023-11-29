#include "Display.hpp"

#include <iostream>


int main(){
  Display display;

  unsigned char message[] = "Ik wil kaas.";

  display.PrintString(message);

  return 0;
}