#include "BootScreen.hpp"

BootScreen::BootScreen()
{
}

BootScreen::~BootScreen()
{
}

void BootScreen::Update()
{
  display.Clear();
  display.Draw(BOOTSCREEN);
  display.Update();
  sleep(1);
  requestedScreen = "home";
  if (OnSwitchScreen != nullptr)
    OnSwitchScreen();
}

void BootScreen::SetOnSwitchScreen(std::function<void()> function) {
  OnSwitchScreen = function;
}

std::string BootScreen::RequestedScreen() {
  return requestedScreen;
}