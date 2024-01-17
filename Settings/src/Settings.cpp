#include "Settings.hpp"

#include <sstream>

Settings::Settings() {
    Read();
}

Settings::~Settings() {
    Write();
}

void Settings::SetPath(std::string path) {
    filePath = path;
    Read();
}

void Settings::Read() {
    data.clear();
    try {
        pt::read_json(filePath, data);
    } 
    catch (...) {
        
    }
}

void Settings::Write() {
    pt::write_json(filePath, data);
}

std::vector<std::string> Settings::List(std::string settingName) { //lists all setting names
  std::vector<std::string> result;
  for (pt::ptree::value_type &pair : data.get_child(settingName)) {
      result.push_back(pair.first);
  }
  return result;
}

bool Settings::IsNested(std::string settingName) {
  if (List(settingName).size() == 0)
    return false;
  return true;
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
void Settings::Set(std::string settingName, std::map<std::string, T> values) {
    pt::ptree node;
    for (std::pair<std::string, T> value : values) {
        pt::ptree leaf;
        leaf.put("", value.second);
        node.push_back(std::make_pair(value.first, leaf));
    }
    data.put_child(settingName, node);
}

template <typename T>
void Settings::Get(std::string settingName, T& value) {
    // std::cout << "Type of T is: " << typeid(T).name() << std::endl;
    try {
        value = data.get<T>(settingName);
    }
    catch (...) { //for now just ignore any exceptions

    }
}

template <typename T>
void Settings::Get(std::string settingName, std::vector<T>& values) { //list
    try {
        for (pt::ptree::value_type &pair : data.get_child(settingName)) {
            std::stringstream ss{pair.second.data()};
            T tmp;
            ss >> tmp;
            values.push_back(tmp);
        }
    }
    catch (...) { //for now just ignore any exceptions

    }
}

template <typename T>
void Settings::Get(std::string settingName, std::map<std::string, T>& map) { //map
    try {
        for (pt::ptree::value_type &pair : data.get_child(settingName)) {
            std::stringstream ss{pair.second.data()};
            T tmp;
            ss >> tmp;
            // std::cout << "Key: " << pair.first << ", Value: " << tmp << "\n";
            map[pair.first] = tmp;
        }
    }
    catch (...) { //for now just ignore any exceptions

    }
}

template void Settings::Set<std::string>(std::string settingName, std::string value);
template void Settings::Set<int>(std::string settingName, int value);
template void Settings::Set<double>(std::string settingName, double value);
template void Settings::Set<std::string>(std::string settingName, std::vector<std::string> values);
template void Settings::Set<int>(std::string settingName, std::vector<int> values);
template void Settings::Set<double>(std::string settingName, std::vector<double> values);
template void Settings::Set<std::string>(std::string settingName, std::map<std::string, std::string> values);
template void Settings::Set<int>(std::string settingName, std::map<std::string, int> values);
template void Settings::Set<double>(std::string settingName, std::map<std::string, double> values);

template void Settings::Get<std::string>(std::string settingName, std::string& value);
template void Settings::Get<int>(std::string settingName, int& value);
template void Settings::Get<double>(std::string settingName, double& value);
template void Settings::Get<std::string>(std::string settingName, std::vector<std::string>& values);
template void Settings::Get<int>(std::string settingName, std::vector<int>& values);
template void Settings::Get<double>(std::string settingName, std::vector<double>& values);
template void Settings::Get<std::string>(std::string settingName, std::map<std::string, std::string>& values);
template void Settings::Get<int>(std::string settingName, std::map<std::string, int>& values);
template void Settings::Get<double>(std::string settingName, std::map<std::string, double>& values);

