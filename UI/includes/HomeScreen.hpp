#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Display.hpp"

#include <iostream>
#include <fstream>
#include <functional>
#include <iomanip>
#include <sstream>

#define NO_INET_STR "No internet!"

class HomeScreen
{
  private:
    Display display;
    std::string requestedScreen = "home";
    std::function<void()> OnSwitchScreen = nullptr;
    std::string ip = NO_INET_STR;
    std::string temperature = "37.5 C°";
    std::string humidity = "50 %";
    void UpdateIP();
  public:
    HomeScreen();
    ~HomeScreen();
    void SetOnSwitchScreen(std::function<void()> function);
    void OnButtonPress();
    void Update();
    void SetTemperature(double temperature);
    void SetHumidity(float humidity);
    void SetRunTime(unsigned int days, unsigned int hours, unsigned int minutes);
    std::string RequestedScreen();
};

#endif