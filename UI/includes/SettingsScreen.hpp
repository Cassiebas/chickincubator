#ifndef SETTINGSSCREEN_HPP
#define SETTINGSSCREEN_HPP

#include "Display.hpp"

class SettingsScreen {
    private:
        Display display;
    public:
        SettingsScreen();
        ~SettingsScreen();
        void Update();
    
};

#endif