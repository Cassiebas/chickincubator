#include "UI.hpp"

UI::UI()
{
  currentScreen = BOOT;
  threadRunning = true;
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
      break;
    case HOME:
      homeScreen.Update();
      break;
    default:
      break;
    }
  }
}

void UI::OnButtonPressed()
{
  switch (currentScreen)
  {
    case SETTINGS:
      homeScreen.OnButtonPressed();
      settingsScreen.Update();
      break;
    case HOME:
      homeScreen.OnButtonPressed();
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