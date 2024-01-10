#include "HomeScreen.hpp"

HomeScreen::HomeScreen()
{
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::Update()
{
  display.Clear();
  display.Update();
}

void HomeScreen::OnButtonPress() {
  requestedScreen = "settings";
  if (OnSwitchScreen != nullptr)
    OnSwitchScreen();
}

void HomeScreen::OnLeft() {

}

void HomeScreen::OnRight() {

}

std::string HomeScreen::RequestedScreen() {
  return requestedScreen;
}

void HomeScreen::SetOnSwitchScreen(std::function<void()> function) {
  OnSwitchScreen = function;
}