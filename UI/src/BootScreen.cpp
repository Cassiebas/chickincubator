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
}