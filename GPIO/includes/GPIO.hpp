#ifndef GPIO_H
#define GPIO_H

#include <sys/types.h>
#include <stdint.h>
#include <string>

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
    ssize_t retVal;

  public:
    GPIO();
    ~GPIO();
    // Set GPIO IO state
    bool SetMode(const std::string &gpioPin, char ioValue);
    bool SetMode(char gpioPin, char ioValue);
    bool SetMode(int gpioPin, char ioValue);
    
    // Set GPIO Input state
    bool Set(const std::string &gpioPin, bool setValue); 
    bool Set(char gpioPin, bool setValue);
    bool Set(int gpioPin, bool setValue);

    // Get GPIO state
    int Get(const std::string &gpioPin);
    int Get(char gpioPin);
    int Get(int gpioPin);
};

#endif