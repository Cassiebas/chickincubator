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
}

void HomeScreen::OnLeft() {

}

void HomeScreen::OnRight() {

}

std::string HomeScreen::RequestedScreen() {
  return requestedScreen;
}
