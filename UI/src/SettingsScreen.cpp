#include "SettingsScreen.hpp"

SettingsScreen::SettingsScreen() : settingNames(settings.List())
{

}

SettingsScreen::~SettingsScreen()
{

}

void SettingsScreen::Update()
{
  display.Clear();
  switch(state) {
    case SETTINGS:
      if (cursor == 0)
        display.Draw(backArrowSelected);
      else
      {
        display.Draw(backArrow);
        display.Draw(textBox, 0, 9);
      }
      if (currentSettingIndex < settingNames.size())
        display.Print(settingNames.at(currentSettingIndex), 3, 11);
      if (currentSettingIndex + 1 < settingNames.size())
        display.Print(settingNames.at(currentSettingIndex + 1), 3, 24);
      break;
    case SETTING:

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
          requestedScreen = "home";
        } else {
          settingNames = settings.List(parentSetting);
          parentSetting = "";
          cursor = 1;
        }
      } else {   
        if (settings.IsNested(settingNames.at(currentSettingIndex))) {
          parentSetting = settingNames.at(currentSettingIndex);
        } else {
          state = SETTING;
        }
      }
      break;
    case SETTING:

      break;
    default:
      break;
  }
}

void SettingsScreen::OnLeft() {
  switch(state) {
    case SETTINGS:
      if (cursor > 0)
        cursor--;
      break;
    case SETTING:

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
      break;
    case SETTING:

      break;
    default:
      break;
  }
}

std::string SettingsScreen::RequestedScreen() {
  return requestedScreen;
}
