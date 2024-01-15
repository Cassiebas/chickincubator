#include "SettingsScreen.hpp"

SettingsScreen::SettingsScreen() : settingNames(settings.List()) 
{
  settings.SetPath("../settings/settings.json");
}

SettingsScreen::~SettingsScreen()
{

}

void SettingsScreen::Update()
{
  std::string unit;
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
      updateEggAnimation();
      break;
    case SETTING:
      display.Draw(backArrowSelected);
      display.Print(settingNames.at(currentSettingIndex), 3, 11);
      settings.Get(settingPath + ".value", settingValue);
      settings.Get(settingPath + ".unit", unit);
      settings.Get(settingPath + ".increment", settingIncrement);
      display.Print(std::to_string(settingValue), 3, 24);
      display.Print(unit, 111, 24);

      updateEggAnimation();
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
          if (OnSwitchScreen != nullptr)
            OnSwitchScreen();
        } else {
          settingNames = settings.List();
          parentSetting = "";
          if (settingPath != "") {
            if (settingPath.rfind(".") != std::string::npos) //if string contains .
              settingPath.erase(settingPath.rfind("."));
          }
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
          // std::cout << settingPath << " is nested\n";
          std::vector<std::string> tempNames;
          tempNames = settings.List(settingPath);
          for(std::string name : tempNames){
            if(name == "value"){
              state = SETTING;
              return;
            }
          }
          parentSetting = settingNames.at(currentSettingIndex);
          settingNames = settings.List(settingPath);
          currentSettingIndex = 0;
        }
      }
      break;
    case SETTING:
      settings.Write();
      state = SETTINGS;
      // settingNames = settings.List();
      // parentSetting = "";
      if (settingPath != "") {
        if (settingPath.rfind(".") != std::string::npos) //if string contains .
          settingPath.erase(settingPath.rfind("."));
      }
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
      settingValue = settingValue - settingIncrement;
      settings.Set(settingPath + ".value", settingValue);
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
      settingValue = settingValue + settingIncrement;
      settings.Set(settingPath + ".value", settingValue); //TODO: log settings that have changed
      break;
    default:
      break;
  }
}

std::string SettingsScreen::RequestedScreen() {
  return requestedScreen;
}

void SettingsScreen::updateEggAnimation() {
  display.Draw(eggAnimation.at(eggCounter), eggCoordinates.at(0), eggCoordinates.at(1));
  eggCounter++;
  eggCoordinates.at(0) += 4;
  if (eggCounter == eggAnimation.size())
    eggCounter = 0;
  if (eggCoordinates.at(0) >= 120) //screenWidth - eggAnimation.at(0).size()
    eggCoordinates.at(0) = 17;
}

void SettingsScreen::SetOnSwitchScreen(std::function<void()> function) {
  OnSwitchScreen = function;
}