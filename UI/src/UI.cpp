#include "UI.hpp"

UI::UI() 
{
  currentScreen = BOOT;
  threadRunning = true;
  rotary([this]() { this->OnLeft(); }, [this]() { this->OnRight(); }, [this]() { this->OnButtonPress(); });
  uiThread = std::thread(&UI::ThreadCycle, this);
}

UI::~UI()
{
  threadRunning = false;
  if (uiThread.joinable())
  {
    uiThread.join();
  }
}

void UI::ThreadCycle()
{
  while (threadRunning)
  {
    switch (currentScreen)
    {
    case BOOT:
      bootScreen.Update();
      break;
    case SETTINGS:
      settingsScreen.Update();
      SwitchScreen(settingsScreen.RequestedScreen());
      break;
    case HOME:
      homeScreen.Update();
      SwitchScreen(homeScreen.RequestedScreen());
      break;
    case WARNING:
      warningScreen.Update();
      SwitchScreen(warningScreen.RequestedScreen());
      break;
    default:
      break;
    }
  }
}

void UI::OnButtonPress()
{
  switch (currentScreen)
  {
    case SETTINGS:
      settingsScreen.OnButtonPress();
      settingsScreen.Update();
      break;
    case HOME:
      homeScreen.OnButtonPress();
      homeScreen.Update();
      break;
    case WARNING:
      warningScreen.OnButtonPress();
      warningScreen.Update();
      break;
    default:
      break;
  }
}

void UI::OnRight() {
  switch (currentScreen)
  {
    case SETTINGS:
      settingsScreen.OnRight();
      settingsScreen.Update();
      break;
    case HOME:
      homeScreen.OnRight();
      homeScreen.Update();
      break;
    default:
      break;
  }
}

void UI::OnLeft() {
  switch (currentScreen)
  {
    case SETTINGS:
      settingsScreen.OnLeft();
      settingsScreen.Update();
      break;
    case HOME:
      homeScreen.OnLeft();
      homeScreen.Update();
      break;
    default:
      break;
  }
}

void UI::SwitchScreen(UI::Screen screen) {
  if (screen != currentScreen) { 
    std::cout << "Switching screen to: " << ScreenToString(screen) << "\n";
    currentScreen = screen;
  }
}

void UI::SwitchScreen(std::string screen) {
  SwitchScreen(StringToScreen(screen));
}

void UI::Warning(std::string message) {
  if (currentScreen == WARNING)
    warningScreen.Add(message);
  else {
    warningScreen.SetPreviousScreen(ScreenToString(currentScreen));
    warningScreen.Add(message);
    SwitchScreen(WARNING);
    // std::cout << "Current screen set to warning\n";
  }
}

std::string UI::ScreenToString(UI::Screen screen) {
  switch (screen) {
    case BOOT:
      return "boot";
      break;
    case SETTINGS:
      return "settings";
      break;
    case HOME:
      return "home";
      break;
    case WARNING:
      return "warning";
      break;
    default:
      break;
  }
  return "";
}

UI::Screen UI::StringToScreen(std::string screen) {
  if (screen == "boot") {
    return BOOT;
  }
  if (screen == "home") {
    return HOME;
  }
  if (screen == "settings") {
    return SETTINGS;
  }
  if (screen == "warning") {
    return WARNING;
  }
  return BOOT;
}