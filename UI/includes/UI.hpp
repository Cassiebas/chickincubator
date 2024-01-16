#ifndef UI_HPP
#define UI_HPP

#include <thread>

#include "BootScreen.hpp"
#include "SettingsScreen.hpp"
#include "HomeScreen.hpp"
#include "WarningScreen.hpp"
#include "QuitScreen.hpp"

#include "Timer.hpp"
#include "RotaryEncoder.hpp"
#include "Settings.hpp"

class UI
{
  public:
    enum Screen
    {
      BOOT,
      SETTINGS,
      HOME,
      WARNING,
      QUIT
    };
    UI();
    ~UI();
    void ThreadCycle();
    void Show();
    void SwitchScreen(UI::Screen screen);
    void SwitchScreen(std::string screen);
    void OnSwitchScreen();
    void OnButtonPress();
    void OnButtonHold();
    void OnLeft();
    void OnRight();
    void Warning(std::string message);
    void SetTemperature(double temperature);
    void SetHumidity(float humidity);
    std::string ScreenToString(UI::Screen screen);
    UI::Screen StringToScreen(std::string screen);
    bool QuitCalled();
  private:
    Screen currentScreen;
    bool threadRunning;
    std::thread uiThread;
    BootScreen bootScreen;
    SettingsScreen settingsScreen;
    HomeScreen homeScreen;
    WarningScreen warningScreen;
    QuitScreen quitScreen;
    RotaryEncoder rotary;
    Timer runtime;
    Settings machineSettings;
  };

#endif