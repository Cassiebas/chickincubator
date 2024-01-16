#include "QuitScreen.hpp"


QuitScreen::QuitScreen() {

}

QuitScreen::~QuitScreen() {

}

void QuitScreen::SetOnSwitchScreen(std::function<void()> function) {
    OnSwitchScreen = function;
}

void QuitScreen::Update() {
    display.Clear();
    display.Print("Stop incubating egg?");
    if (cursor == 0) {
        display.Draw(noButtonSelected, 0, 21);
        display.Draw(yesButton, 127 - (unsigned int)yesButton.at(0).size(), 21);
    } else {
        display.Draw(noButton, 0, 21);
        display.Draw(yesButtonSelected, 127 - (unsigned int)yesButton.at(0).size(), 21);
    }
    display.Update();
}

void QuitScreen::OnButtonPress() {
    requestedScreen = "home";
    if (OnSwitchScreen != nullptr)
        OnSwitchScreen();
}

void QuitScreen::OnLeft() {
    if (cursor < 1)
        cursor++;
}

void QuitScreen::OnRight() {
    if (cursor > 0)
        cursor--;
}

std::string QuitScreen::RequestedScreen() {
    return requestedScreen;
}

bool QuitScreen::SelectedOption() {
    if (cursor == 0)
        return false;
    return true;
}