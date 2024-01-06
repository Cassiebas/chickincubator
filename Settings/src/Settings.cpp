#include "Settings.hpp"

Settings::Settings() {
    Read();
}

Settings::~Settings() {
    Write();
}

void Settings::Read() {
    pt::read_json(filePath, data);
}

void Settings::Write() {
    pt::write_json(filePath, data);
}

template <typename T>
void Settings::Set(std::string settingName, T value) {
    data.put(settingName, value);
}

template <typename T>
T Settings::Get(std::string settingName) {
    return data.get<T>(settingName);
}

template void Settings::Set<std::string>(std::string settingName, std::string value);
template void Settings::Set<int>(std::string settingName, int value);
template void Settings::Set<double>(std::string settingName, double value);
// ... add other types you might use with Set

template std::string Settings::Get<std::string>(std::string settingName);
template int Settings::Get<int>(std::string settingName);
template double Settings::Get<double>(std::string settingName);
// ... add other types you might use with Get

