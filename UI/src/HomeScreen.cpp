#include "HomeScreen.hpp"

HomeScreen::HomeScreen()
{
  system("ip -4 addr show wlan0 | grep -oP '(?<=inet\\s)\\d+(\\.\\d+){3}' >ip.txt"); //put only the needed ip in a tmp txt file
  std::fstream inFile;
  inFile.open("ip.txt", std::ios::in);
  if (inFile.is_open()){ 
    getline(inFile, ip);
    inFile.close();
  }
  system("rm ip.txt");
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::Update()
{
  display.Clear();

  display.Print(ip, 1, 1);
  display.DrawLine(0, 0, 127, 0);
  display.DrawLine(0, 10, 127, 10);
  display.DrawLine(0, 0, 0, 10);
  display.DrawLine(127, 0, 127, 10);

  display.Print(temperature, 1, 11);
  display.Print(humidity, 64, 11);
  display.DrawLine(63, 10, 63, 20);
  display.DrawLine(0, 10, 0, 20);
  display.DrawLine(127, 10, 127, 20);
  display.DrawLine(0, 20, 127, 20);

  display.Update();
}

void HomeScreen::OnButtonPress() {
  requestedScreen = "settings";
  if (OnSwitchScreen != nullptr)
    OnSwitchScreen();
}

std::string HomeScreen::RequestedScreen() {
  return requestedScreen;
}

void HomeScreen::SetOnSwitchScreen(std::function<void()> function) {
  OnSwitchScreen = function;
}

void HomeScreen::SetTemperate(double temperature) {
  this->temperature = std::to_string(temperature) + " C°";
}

void HomeScreen::SetHumidity(float humidity) {
  this->humidity = std::to_string(humidity) + " %";
}