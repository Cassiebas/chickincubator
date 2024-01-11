#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Display.hpp"

#include <iostream>
#include <fstream>
#include <functional>

class HomeScreen
{
  private:
    Display display;
    std::string requestedScreen = "home";
    std::function<void()> OnSwitchScreen = nullptr;
    std::string ip = "";
    std::string temperature = "37.5 C°";
    std::string humidity = "50 %";
  public:
    HomeScreen();
    ~HomeScreen();
    void SetOnSwitchScreen(std::function<void()> function);
    void OnButtonPress();
    void Update();
    void SetTemperate(double temperature);
    void SetHumidity(float humidity);
    void SetRunTime(unsigned int days, unsigned int hours, unsigned int minutes);
    std::string RequestedScreen();
};

#endif