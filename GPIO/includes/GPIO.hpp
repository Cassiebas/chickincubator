#ifndef GPIO_H
#define GPIO_H

#include <sys/types.h>
#include <stdint.h>

#define OUTPUT 'O'
#define INPUT 'I'
#define GPIO_1 '1'
#define GPIO_2 '2'
#define GPIO_3 '3'
#define GPIO_4 '4'
#define GPIO_5 '5'
#define GPIO_6 '6'
#define GPIO_7 '7'
#define GPIO_8 '8'
#define GPIO_9 '9'
#define GPIO_10 "10"
#define GPIO_11 "11"
#define GPIO_12 "12"
#define GPIO_13 "13"
#define GPIO_14 "14"
#define GPIO_15 "15"
#define GPIO_16 "16"
#define GPIO_17 "17"
#define GPIO_18 "18"
#define GPIO_19 "19"
#define GPIO_20 "20"
#define GPIO_21 "21"
#define GPIO_22 "22"
#define GPIO_23 "23"
#define GPIO_24 "24"
#define GPIO_25 "25"

class GPIO
{
  private:
    int fd;
    ssize_t ret_val;

  public:
    GPIO();
    ~GPIO();

    bool setMode(const char *gpio_pin, char IO_value);
    bool setMode(char gpio_pin, char IO_value);

    bool set(const char *gpio_pin, char set_value); //TODO: look into how to name this write :/
    bool set(char gpio_pin, char set_value);

    char get(const char *gpio_pin);
    char get(char gpio_pin);
};

#endif