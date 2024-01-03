#include "UI.hpp"

UI::UI() {
    currentScreen = BOOT;
    threadRunning = true;
    uiThread = std::thread(&UI::ThreadCycle, this);
}

UI::~UI() {
    threadRunning = false;
    if (uiThread.joinable()) {
        uiThread.join();
    }
}

void UI::ThreadCycle() {
    while(threadRunning) {
        switch(currentScreen) {
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

void UI::SwitchScreen(Screen screen) {
    currentScreen = screen;
}