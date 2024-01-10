#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Display.hpp"
#include <functional>

class HomeScreen
{
  private:
    Display display;
    std::string requestedScreen = "home";
    std::function<void()> OnSwitchScreen = nullptr;
  public:
    HomeScreen();
    ~HomeScreen();
    void SetOnSwitchScreen(std::function<void()> function);
    void OnButtonPress();
    void OnLeft();
    void OnRight();
    void Update();
    std::string RequestedScreen();
};

#endif