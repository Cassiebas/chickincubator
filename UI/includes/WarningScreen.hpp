#ifndef WARNING_SCREEN_HPP
#define WARNING_SCREEN_HPP

#include "Display.hpp"

const Bitmap okButton {
  {1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,1,1,0,1,1,0,1},
  {1,0,1,1,1,0,1,0,1,0,1,1},
  {1,0,1,1,1,0,1,0,0,1,1,1},
  {1,0,1,1,1,0,1,0,0,1,1,1},
  {1,0,1,1,1,0,1,0,1,0,1,1},
  {1,1,0,0,0,1,1,0,1,1,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1}
};

class WarningScreen {
  public:
    WarningScreen();
    WarningScreen(std::string prevScreen);
    ~WarningScreen();
    void Update();
    void OnButtonPress();
    void SetPreviousScreen(std::string prevScreen);
    void Add(std::string warning);
    std::string RequestedScreen();
  private:
    Display display;
    std::vector<std::string> warningQueue;
    std::string requestedScreen = "";
    bool quit = false;
};

#endif