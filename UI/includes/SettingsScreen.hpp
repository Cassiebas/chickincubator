#ifndef SETTINGSSCREEN_HPP
#define SETTINGSSCREEN_HPP

#include "Display.hpp"
#include "Settings.hpp"

using Bitmap = std::vector<std::vector<bool>>;
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
    void OnButtonPress();
    void OnLeft();
    void OnRight();
    void Update();
    std::string RequestedScreen();
  private:
    Display display;
    Settings settings;
    State state = SETTINGS;
    std::vector<std::string> settingNames;
    unsigned int currentSettingIndex = 0;
    std::string parentSetting = "";
    std::string settingPath = "";
    unsigned int cursor = 1; //start with option selected
    std::string requestedScreen = "settings";
    double settingValue;
};

#endif