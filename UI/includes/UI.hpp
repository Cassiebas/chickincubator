#ifndef UI_HPP
#define UI_HPP

#include <thread>

#include "BootScreen.hpp"
#include "SettingsScreen.hpp"
#include "HomeScreen.hpp"
#include "RotaryEncoder.hpp"

class UI
{
  public:
    enum Screen
    {
      BOOT,
      SETTINGS,
      HOME
    };
    UI();
    ~UI();
    void ThreadCycle();
    void Show();
    void SwitchScreen(UI::Screen screen);
    void SwitchScreen(std::string screen);
    void OnButtonPress();
    void OnLeft();
    void OnRight();
  private:
    Screen currentScreen;
    bool threadRunning;
    std::thread uiThread;
    BootScreen bootScreen;
    SettingsScreen settingsScreen;
    HomeScreen homeScreen;
    RotaryEncoder rotary;
  };

#endif