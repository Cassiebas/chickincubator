#include "UI.hpp"

UI::UI() 
{
  currentScreen = BOOT;
  threadRunning = true;
  rotary([this]() { this->OnLeft(); }, [this]() { this->OnRight(); }, [this]() { this->OnButtonPress(); }, [this]() { this->OnButtonHold(); });
  warningScreen.SetOnSwitchScreen([this]() { this->OnSwitchScreen(); });
  bootScreen.SetOnSwitchScreen([this]() { this->OnSwitchScreen(); });
  homeScreen.SetOnSwitchScreen([this]() { this->OnSwitchScreen(); });
  settingsScreen.SetOnSwitchScreen([this]() { this->OnSwitchScreen(); });
  quitScreen.SetOnSwitchScreen([this]() { this->OnSwitchScreen(); });
  machineSettings.SetPath("../settings/machinesettings.json");
  runtime.Start();
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
  double time;
  while (threadRunning) {
    // std::cout << "UI threadcycle\n";
    switch (currentScreen) {
    case BOOT:
      bootScreen.Update();
      break;
    case SETTINGS:
      settingsScreen.Update();
      break;
    case HOME:
      homeScreen.Update();
      break;
    case WARNING:
      warningScreen.Update();
      break;
    case QUIT:
      quitScreen.Update();
      break;
    default:
      break;
    }
    if (runtime.Elapsed() > 1 && !QuitCalled()) {
      machineSettings.Read();
      machineSettings.Get("runtime", time);
      machineSettings.Set("runtime", time + runtime.Elapsed());
      runtime.Reset();
      machineSettings.Write();
    }
  }
}

void UI::OnButtonPress()
{
  switch (currentScreen)
  {
    case SETTINGS:
      settingsScreen.OnButtonPress();
      settingsScreen.Update();
      break;
    case HOME:
      homeScreen.OnButtonPress();
      homeScreen.Update();
      break;
    case WARNING:
      warningScreen.OnButtonPress();
      warningScreen.Update();
      break;
    case QUIT:
      quitScreen.OnButtonPress();
      quitScreen.Update();
      break;
    default:
      break;
  }
}

void UI::OnButtonHold()
{
  switch (currentScreen)
  {
    case HOME:
      homeScreen.OnButtonHold();
      homeScreen.Update();
      break;
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
    case QUIT:
      quitScreen.OnRight();
      quitScreen.Update();
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
    case QUIT:
      quitScreen.OnLeft();
      quitScreen.Update();
      break;
    default:
      break;
  }
}

void UI::SwitchScreen(UI::Screen screen) {
  if (screen != currentScreen) { 
    std::cout << "Switching screen to: " << ScreenToString(screen) << "\n";
    currentScreen = screen;
  }
}

void UI::SwitchScreen(std::string screen) {
  SwitchScreen(StringToScreen(screen));
}

void UI::Warning(std::string message) {
  if (currentScreen == WARNING)
    warningScreen.Add(message);
  else {
    warningScreen.SetPreviousScreen(ScreenToString(currentScreen));
    warningScreen.Add(message);
    SwitchScreen(WARNING);
    // std::cout << "Current screen set to warning\n";
  }
}

std::string UI::ScreenToString(UI::Screen screen) {
  switch (screen) {
    case BOOT:
      return "boot";
      break;
    case SETTINGS:
      return "settings";
      break;
    case HOME:
      return "home";
      break;
    case WARNING:
      return "warning";
      break;
    case QUIT:
      return "quit";
      break;
    default:
      break;
  }
  return "";
}

UI::Screen UI::StringToScreen(std::string screen) {
  if (screen == "boot") {
    return BOOT;
  }
  if (screen == "home") {
    return HOME;
  }
  if (screen == "settings") {
    return SETTINGS;
  }
  if (screen == "warning") {
    return WARNING;
  }
  if (screen == "quit") {
    return QUIT;
  }
  return BOOT;
}

void UI::OnSwitchScreen() {
  switch (currentScreen)
  {
  case BOOT:
    SwitchScreen(bootScreen.RequestedScreen());
    break;
  case SETTINGS:
    SwitchScreen(settingsScreen.RequestedScreen());
    break;
  case HOME:
    SwitchScreen(homeScreen.RequestedScreen());
    break;
  case WARNING:
    SwitchScreen(warningScreen.RequestedScreen());
    break;
  case QUIT:
    SwitchScreen(quitScreen.RequestedScreen());
    break;
  default:
    break;
  }
}

void UI::SetTemperature(double temperature)
{
  homeScreen.SetTemperature(temperature);
}

void UI::SetHumidity(float humidity)
{
  homeScreen.SetHumidity(humidity);
}

bool UI::QuitCalled() {
  return quitScreen.SelectedOption();
}