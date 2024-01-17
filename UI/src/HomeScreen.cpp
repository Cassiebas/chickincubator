#include "HomeScreen.hpp"

HomeScreen::HomeScreen()
{
  UpdateIP();
  machineSettings.SetPath("../settings/machinesettings.json");
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::Update()
{
  if (ip == NO_INET_STR) {
    UpdateIP();
  }
  machineSettings.Read();
  machineSettings.Get("runtime", runtime);
  
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

  display.Print(secondsToTime(runtime), 2, 21);
  display.DrawLine(0, 20, 0, 32);
  display.DrawLine(127, 20, 127, 32);
  display.DrawLine(0, 32, 127, 32);

  display.Update();
}

void HomeScreen::OnButtonPress() {
  std::cout << "Button pressed on home screen\n";
  requestedScreen = "settings";
  if (OnSwitchScreen != nullptr)
    OnSwitchScreen();
}

void HomeScreen::OnButtonHold() {
  std::cout << "Button held on home screen\n";
  requestedScreen = "quit";
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

void HomeScreen::UpdateIP() {
  system("ip -4 addr show wlan0 | grep -oP '(?<=inet\\s)\\d+(\\.\\d+){3}' >ip.txt"); //put only the needed ip in a tmp txt file
  std::fstream inFile;
  inFile.open("ip.txt", std::ios::in);
  if (inFile.is_open()) { 
    getline(inFile, ip);
    inFile.close();
  }
  system("rm ip.txt");
  if (ip == "")
    ip = NO_INET_STR;
}

std::string HomeScreen::secondsToTime(double seconds) {
    // std::cout << "Calculating seconds to time: " << seconds << "\n";
    int days = (int)(seconds / 86400);
    int hours = (int)(seconds / 3600);
    int minutes = ((int)seconds % 3600) / 60;
    int remainingSeconds = (int)seconds % 60;

    std::ostringstream result;
    result << std::setfill('0') 
        << std::setw(2) << days << "d " 
        << std::setw(2) << hours << ":"
        << std::setw(2) << minutes << ":"
        << std::setw(2) << remainingSeconds; //hh:mm:ss

    return result.str();
}