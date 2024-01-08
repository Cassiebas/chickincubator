#include "Settings.hpp"

#include <sstream>

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
void Settings::Set(std::string settingName, std::vector<T> values) {
    pt::ptree node;
    for (T value : values) {
        pt::ptree leaf;
        leaf.put("", value);
        node.push_back(std::make_pair("", leaf));
    }
    data.put_child(settingName, node);
}

template <typename T>
void Settings::Get(std::string settingName, T& value) {
    value = data.get<T>(settingName);
}

template <typename T>
void Settings::Get(std::string settingName, std::vector<T>& values) {
    for (pt::ptree::value_type &pair : data.get_child(settingName)) {
        std::stringstream ss{pair.second.data()};
        T tmp;
        ss >> tmp;
        values.push_back(tmp);
    }
}

template void Settings::Set<std::string>(std::string settingName, std::string value);
template void Settings::Set<int>(std::string settingName, int value);
template void Settings::Set<double>(std::string settingName, double value);
template void Settings::Set<std::string>(std::string settingName, std::vector<std::string> values);
template void Settings::Set<int>(std::string settingName, std::vector<int> values);
template void Settings::Set<double>(std::string settingName, std::vector<double> values);

template void Settings::Get<std::string>(std::string settingName, std::string& value);
template void Settings::Get<int>(std::string settingName, int& value);
template void Settings::Get<double>(std::string settingName, double& value);
template void Settings::Get<std::string>(std::string settingName, std::vector<std::string>& values);
template void Settings::Get<int>(std::string settingName, std::vector<int>& values);
template void Settings::Get<double>(std::string settingName, std::vector<double>& values);

