#include "../includes/GPIO.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

GPIO::GPIO()
{
  fd = open("/dev/my_gpio_driver", O_RDWR); //TODO: should be done in c++ style to get support for namespaces
  if (fd < 0)
  {
    printf("Error opening the device driver\n");
  }
}

GPIO::~GPIO() 
{
  close(fd);
}

bool GPIO::setMode(const char *gpio_pin, char IO_value)
{
  char buffer[4];
  sprintf(buffer, "%s%c", gpio_pin, IO_value);
  // Writing to GPIO driver
  ret_val = write(fd, buffer, sizeof(buffer));
  if (ret_val < 0)
  {
    printf("Error writing to the device file\n");
    close(fd);
    return -1;
  }
  return true; // Placeholder return value
}

bool GPIO::setMode(char gpio_pin, char IO_value)
{
  char buffer[2];
  buffer[0] = gpio_pin;
  buffer[1] = IO_value;
  // Writing to GPIO driver
  ret_val = write(fd, buffer, sizeof(buffer));
  if (ret_val < 0)
  {
    printf("Error writing to the device file\n");
    close(fd);
    return false;
  }
  return true; // Placeholder return value
}

bool GPIO::set(const char *gpio_pin, char set_value) //TODO: change this to bool set_value, change pin to int.
{
  char buffer[4];
  sprintf(buffer, "%s%c", gpio_pin, set_value);
  // Writing to GPIO driver
  ret_val = write(fd, buffer, sizeof(buffer));
  if (ret_val < 0)
  {
    printf("Error writing to the device file\n");
    close(fd);
    return -1;
  }
  return true; // Placeholder return value
}

bool GPIO::set(char gpio_pin, char set_value) //for when gpio_pin is passed as '' (char not char *)
{
  char *tmp = &gpio_pin;
  return set(tmp, set_value);
}

char GPIO::get(const char *gpio_pin)
{
  // Reading from the device file
  char read_buffer[3];
  sprintf(read_buffer, "%s", gpio_pin);
  ret_val = read(fd, read_buffer, sizeof(read_buffer));
  if (ret_val < 0)
  {
    printf("Error reading from the device file\n");
    close(fd);
    return -1;
  }
  return read_buffer[0];
}

char GPIO::get(char gpio_pin)
{
  char *tmp = &gpio_pin;
  return get(tmp);
}