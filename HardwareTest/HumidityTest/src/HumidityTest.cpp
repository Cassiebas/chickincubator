#include <iostream>
#include "Humidity.hpp"

int main()
{
  Humidity humiditySensor;

  while (true)
  {
    std::cout << "Humidity Readings: " << humiditySensor.Read() << "\n";
    sleep(1);
  }

  return 0;
}