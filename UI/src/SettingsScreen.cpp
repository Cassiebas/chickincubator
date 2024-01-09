#include "SettingsScreen.hpp"

SettingsScreen::SettingsScreen() : settingNames(settings.List())
{

}

SettingsScreen::~SettingsScreen()
{

}

void SettingsScreen::Update()
{
  std::string value;
  display.Clear();
  switch(state) {
    case SETTINGS:
      if (currentSettingIndex < settingNames.size())
        display.Print(settingNames.at(currentSettingIndex), 3, 11);
      if (currentSettingIndex + 1 < settingNames.size())
        display.Print(settingNames.at(currentSettingIndex + 1), 3, 24);
      if (cursor == 0)
        display.Draw(backArrowSelected);
      else
      {
        display.Draw(backArrow);
        display.DrawLine(0, 9, 127, 9);
        display.DrawLine(0, 22, 127, 22);
        display.DrawLine(0, 9, 0, 22);
        display.DrawLine(127, 9, 127, 22);
      }
      break;
    case SETTING:
      display.Draw(backArrowSelected);
      display.Print(settingNames.at(currentSettingIndex), 3, 11);
      settings.Get(settingPath, settingValue);
      display.Print(std::to_string(settingValue), 3, 24);
      break;
    default:
      break;
  }
  display.Update();
}

void SettingsScreen::OnButtonPress() {
  switch(state) {
    case SETTINGS:
      if (cursor == 0) {
        if (parentSetting == "") {
          std::cout << "Going back to home screen...\n";
          requestedScreen = "home";
        } else {
          settingNames = settings.List();
          parentSetting = "";
          cursor = 1;
        }
      } else {   
        if (parentSetting == "")
          settingPath = settingNames.at(currentSettingIndex); //"PID"
        else {
          if (settingPath != settingNames.at(currentSettingIndex)) {
            settingPath = settingPath + "." + settingNames.at(currentSettingIndex); //"PID.D.X" etc
          } else {
            settingPath = parentSetting + "." + settingNames.at(currentSettingIndex); //"PID.D"
          }
        }
        if (settings.IsNested(settingPath)) {
          std::cout << settingPath << " is nested\n";
          parentSetting = settingNames.at(currentSettingIndex);
          settingNames = settings.List(settingPath);
          currentSettingIndex = 0;
        } else {
          state = SETTING;
        }
      }
      break;
    case SETTING:
      settings.Write();
      state = SETTINGS;
      break;
    default:
      break;
  }
}

void SettingsScreen::OnLeft() {
  switch(state) {
    case SETTINGS:
      if (currentSettingIndex > 0)
        currentSettingIndex--;
      else {
        if (cursor > 0)
          cursor--;
      }
      break;
    case SETTING:
      settingValue = settingValue - settingValue * INCREMENT_FACTOR;
      settings.Set(settingPath, settingValue);
      break;
    default:
      break;
  }
}

void SettingsScreen::OnRight() {
  switch(state) {
    case SETTINGS:
      if (cursor < 1)
        cursor++;
      else if (currentSettingIndex + 1 < settingNames.size())
        currentSettingIndex++;
      break;
    case SETTING:
      settingValue = settingValue + settingValue * INCREMENT_FACTOR;
      settings.Set(settingPath, settingValue); //TODO: log settings that have changed
      break;
    default:
      break;
  }
}

std::string SettingsScreen::RequestedScreen() {
  return requestedScreen;
}
