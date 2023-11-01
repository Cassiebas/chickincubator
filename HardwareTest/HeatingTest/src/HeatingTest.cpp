#include "../../HeatingElement/includes/HeatingElement.hpp"
#include "../../Thermistor/includes/Thermistor.hpp"
#include <iostream>

#define HEATER_GPIO "26" 

int main(){
  Thermistor temperature;
  HeatingElement heater(HEATER_GPIO);
  
  int i2c_adc_file = temperature.Open_I2C_ADC();

  heater.startHeating();
  while(true){
    temperature.Read_I2C_ADC(i2c_adc_file);
  }
  heater.stopHeating();
  return 0;
}