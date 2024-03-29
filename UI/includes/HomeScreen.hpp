#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Display.hpp"
#include "Settings.hpp"

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
    double runtime = 0;
    Settings machineSettings;
    void UpdateIP();
    std::string secondsToTime(double seconds);
  public:
    HomeScreen();
    ~HomeScreen();
    void SetOnSwitchScreen(std::function<void()> function);
    void OnButtonPress();
    void OnButtonHold();
    void Update();
    void SetTemperature(double temperature);
    void SetHumidity(float humidity);
    void SetRunTime(unsigned int days, unsigned int hours, unsigned int minutes);
    std::string RequestedScreen();
};

#endif