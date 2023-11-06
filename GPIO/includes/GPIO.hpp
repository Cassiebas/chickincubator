#ifndef GPIO_HPP
#define GPIO_HPP

#include <string>

class GPIO
{
  private:
    int duty_cycle = 0;
    int period = 0;
    volatile uint32_t* BCM2835_BASE;
    volatile uint32_t* GPFSEL0;
    volatile uint32_t* GPFSEL1;
    volatile uint32_t* GPFSEL2; 
    volatile uint32_t* GPFSEL3; 
    volatile uint32_t* GPFSEL4;
    volatile uint32_t* GPFSEL5;  

    volatile uint32_t* GPIOSET0;
    volatile uint32_t* GPIOSET1;
    
    volatile uint32_t* GPCLR0;
    volatile uint32_t* GPCLR1;

    std::string pin;
    std::string path;

  public:
    const struct pin_sel_register
    {
      uint8_t OUTPUT = 0b001;
      uint8_t INPUT = 0b000;
      uint8_t ALT0 = 0b100;
      uint8_t ALT1 = 0b101;
      uint8_t ALT2 = 0b110;
      uint8_t ALT3 = 0b111;
      uint8_t ALT4 = 0b011;
      uint8_t ALT5 = 0b010;
    };

    GPIO();

    void set(std::string pin, uint8_t bitfield);
};

#endif