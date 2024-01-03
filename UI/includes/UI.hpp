#ifndef UI_HPP
#define UI_HPP

#include <thread>

#include "BootScreen.hpp"
#include "SettingsScreen.hpp"
#include "HomeScreen.hpp"

enum Screen
{
  BOOT,
  SETTINGS,
  HOME
};

class UI
{
  private:
    bool threadRunning;
    std::thread uiThread;
    BootScreen bootScreen;
    SettingsScreen settingsScreen;
    HomeScreen homeScreen;
    Screen currentScreen;

  public:
    UI();
    ~UI();
    void ThreadCycle();
    void Show();
    void SwitchScreen(Screen screen);
  };

#endif