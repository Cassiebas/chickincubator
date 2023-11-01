#ifndef HEATING_ELEMENT_H
#define HEATING_ELEMENT_H

#include <string>

class HeatingElement {
  private:
    std::string path;
    std::string pin;

    void writeGPIO(const std::string &filename, const std::string &value);

  public:
    HeatingElement(const std::string &pin);

    void startHeating();

    void stopHeating();
};

#endif