#ifndef HEATING_ELEMENT_H
#define HEATING_ELEMENT_H

#include <string>

class HeatingElement {
  private:
    std::string pin;
    std::string path;

    void writeGPIO(const std::string filename, const std::string value);

  public:
<<<<<<< Updated upstream
    HeatingElement(const std::string pin);
=======
    HeatingElement(std::string pinNumber);
>>>>>>> Stashed changes

    void startHeating();

    void stopHeating();
};

#endif