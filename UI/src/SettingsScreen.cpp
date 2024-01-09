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
      if (currentSettingIndex < settingNames.size())
        display.Print(settingNames.at(currentSettingIndex), 3, 11);
      if (currentSettingIndex + 1 < settingNames.size())
        display.Print(settingNames.at(currentSettingIndex + 1), 3, 24);
      if (cursor == 0)
        display.Draw(backArrowSelected);
      else
      {
        display.Draw(backArrow);
        display.Draw(textBoxVerticalLine, 0, 9);
        display.Draw(textBoxVerticalLine, 127, 9);
        display.Draw(textBoxHorizontalLine, 0, 9);
        display.Draw(textBoxHorizontalLine, 0, 22);
      }
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
          std::cout << "Going back to home screen...\n";
          requestedScreen = "home";
        } else {
          settingNames = settings.List();
          parentSetting = "";
          cursor = 1;
        }
      } else {   
        if (settings.IsNested(settingNames.at(currentSettingIndex))) {
          parentSetting = settingNames.at(currentSettingIndex);
          settingNames = settings.List(settingNames.at(currentSettingIndex));
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
  std::cout << "Button pressed in settings\n";
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
      break;
    default:
      break;
  }
  std::cout << "Turned left in settings\n";
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

      break;
    default:
      break;
  }
  std::cout << "Turned right in settings\n";
}

std::string SettingsScreen::RequestedScreen() {
  return requestedScreen;
}
