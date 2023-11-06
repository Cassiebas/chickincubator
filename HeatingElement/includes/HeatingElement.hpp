#ifndef HEATING_ELEMENT_H
#define HEATING_ELEMENT_H

#include <string>

class HeatingElement {
  private:
    std::string pin;
    std::string path;

    void writeGPIO(const std::string filename, const std::string value);

  public:
    HeatingElement(const std::string pin, const std::string dutyCycle = "100", const std::string period = "1");

    void Start();

    void Stop();
};

#endif