#ifndef SETTINGSSCREEN_HPP
#define SETTINGSSCREEN_HPP

#include "Display.hpp"

class SettingsScreen
{
  private:
    Display display;

  public:
    SettingsScreen();
    ~SettingsScreen();
    void OnButtonPressed();
    void OnLeft();
    void OnRight();
    void Update();
};

#endif