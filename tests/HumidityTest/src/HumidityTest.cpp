#include <iostream>
#include "Humidity.hpp"

int main()
{
  Humidity humidity;

  std::cout << "RH: "<< humidity.Read() << std::endl;

  return 0;
}