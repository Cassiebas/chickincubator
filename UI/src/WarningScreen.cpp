#include "WarningScreen.hpp"

WarningScreen::WarningScreen() {

}

WarningScreen::WarningScreen(std::string prevScreen) : requestedScreen(prevScreen) {

}

WarningScreen::~WarningScreen() {

}

void WarningScreen::SetPreviousScreen(std::string prevScreen) {
  requestedScreen = prevScreen;
  quit = false;
}

void WarningScreen::Update() {
  display.Clear();
  display.Draw(okButton, 127 - (unsigned int)okButton.at(0).size(), 31 - (unsigned int)okButton.size());
  if (warningQueue.size() > 0)
    display.Print(warningQueue.at(0));
  display.Update();
}

void WarningScreen::OnButtonPress() {
  if (warningQueue.size() > 1)
    warningQueue.erase(warningQueue.begin());
  else {
    quit = true;
    if (OnSwitchScreen != nullptr) {
      OnSwitchScreen();
    }
  }
}

void WarningScreen::Add(std::string warning) {
  warningQueue.push_back(warning);
}

std::string WarningScreen::RequestedScreen() {
  if (quit) {
    quit = false;
    return requestedScreen;
  }
  return "warning";
}

void WarningScreen::SetOnSwitchScreen(std::function<void()> function) {
  OnSwitchScreen = function;
}
