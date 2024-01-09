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
    // std::cout << "currentScreen: " << currentScreen << "\n";
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
  std::cout << "Switching screen to: " << screen << "\n";
  currentScreen = screen;
}

void UI::SwitchScreen(std::string screen) {
  if (screen == "boot") {
    currentScreen = BOOT;
  }
  if (screen == "home") {
    currentScreen = HOME;
  }
  if (screen == "settings") {
    currentScreen = SETTINGS;
  }
}