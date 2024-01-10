#ifndef SETTINGSSCREEN_HPP
#define SETTINGSSCREEN_HPP

#include "Display.hpp"
#include "Settings.hpp"
#include <functional>

const Bitmap backArrow = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
const Bitmap backArrowSelected = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

const std::vector<Bitmap> eggAnimation = {
  {
    {0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0},
    {0,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0}
  },
  {
    {0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,0,0},
    {0,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0},
    {0,0,0,1,1,0,0,0}
  },
  {
    {0,0,0,0,0,0,0,0},
    {0,0,1,1,0,0,0,0},
    {0,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,0,0},
    {0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0}
  },
  {
    {0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0},
    {0,0,1,1,1,1,0,0},
    {0,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,0,0,1,1,1,0,0}
  },
  {
    {0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0},
    {0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0}
  },
  {
    {0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0},
    {0,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,0},
    {0,0,1,1,1,0,0,0}
  },
  {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0},
    {0,0,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,0},
    {0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,0,0}
  },
  {
    {0,0,0,0,0,0,0,0},
    {0,0,1,1,1,0,0,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,0},
    {0,0,1,1,1,1,0,0},
    {0,0,0,1,1,0,0,0}
  }
};

#define INCREMENT_FACTOR 0.1

class SettingsScreen
{  
  public:
    enum State {
      SETTINGS,
      SETTING
    };
    SettingsScreen();
    ~SettingsScreen();
    void SetOnSwitchScreen(std::function<void()> function);
    void OnButtonPress();
    void OnLeft();
    void OnRight();
    void Update();
    std::string RequestedScreen();
  private:
    Display display;
    Settings settings;
    Settings increments;
    State state = SETTINGS;
    std::function<void()> OnSwitchScreen = nullptr;
    std::vector<std::string> settingNames;
    std::string parentSetting = "";
    std::string settingPath = "";
    std::string requestedScreen = "settings";
    unsigned int currentSettingIndex = 0;
    unsigned int cursor = 1; //start with option selected
    unsigned int eggCounter = 0;
    std::vector<unsigned int> eggCoordinates = {17, 0}; //x, y 
    double settingValue = 0;
    double settingIncrement = 0;

    void updateEggAnimation();
};

#endif