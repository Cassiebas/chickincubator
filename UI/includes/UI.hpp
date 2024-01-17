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

struct MessageOnTrigger {
  std::string message;
  std::string trigger;
  std::string operation; 
  double value;
  double timeout = -1; //in minutes, how long to wait for to reset the message
  bool triggered = false;
};


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
    bool eggHatched = false;
    double temp, hum;
    std::vector<MessageOnTrigger> messagesOnTrigger = { //keep this order, otherwise the .at calls have the wrong message
      {"Temperature is too high for the eggs!", "temperature", ">", 40.5, 10}, //TODO: look into why the timeout is not accurate
      {"Temperature is too low for the eggs!", "temperature", "<", 35, 10},
      {"Humidity is too high for the eggs!", "humidity", ">", 55, 30},
      {"Humidity is too low for the eggs!", "humidity", "<", 45, 30},
      {"Eggs should have hatched now!", "day", "=", 21},
      {"Humidity should now be held at 65-75%", "day", "=", 18},
      {"Change flooring to a non-slip surface", "day", "=", 18}
    };
    Timer msgTimer[7]; //7 messages
  };

#endif