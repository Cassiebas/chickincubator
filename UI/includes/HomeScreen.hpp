#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Display.hpp"

class HomeScreen
{
  private:
    Display display;

  public:
    HomeScreen();
    ~HomeScreen();
    void Update();
};

#endif