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

  display.Print(ip, 2, 1);
  display.DrawLine(0, 0, 127, 0);
  display.DrawLine(0, 10, 127, 10);
  display.DrawLine(0, 0, 0, 10);
  display.DrawLine(127, 0, 127, 10);

  display.Print(temperature, 2, 11);
  display.Print(humidity, 65, 11);
  display.DrawLine(63, 10, 63, 20);
  display.DrawLine(0, 10, 0, 20);
  display.DrawLine(127, 10, 127, 20);
  display.DrawLine(0, 20, 127, 20);

  display.Update();
}

void HomeScreen::OnButtonPress() {
  std::cout << "Button pressed on home screen\n";
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

void HomeScreen::SetTemperature(double temperature) {
  std::stringstream temp;
  temp << std::fixed << std::setprecision(1) << temperature;
  this->temperature = temp.str() + " C°";
}

void HomeScreen::SetHumidity(float humidity) {
  std::stringstream hum;
  hum << std::fixed << std::setprecision(1) << humidity;
  this->humidity = hum.str() + " %";
}