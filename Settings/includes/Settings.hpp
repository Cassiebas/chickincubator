#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <map>

#define DEFAULT_SETTINGS_PATH "../settings/settings.json"

namespace pt = boost::property_tree;

class Settings {
    private:
        pt::ptree data;
        std::string filePath = DEFAULT_SETTINGS_PATH;
    public:
        Settings();
        Settings(std::string path);
        ~Settings();
        void SetPath(std::string path);
        void Read();
        void Write();
        bool IsNested(std::string settingName);
        std::vector<std::string> List(std::string settingName = ""); 
        template <typename T> void Set(std::string settingName, T value);
        template <typename T> void Set(std::string settingName, std::vector<T> values);
        template <typename T> void Set(std::string settingName, std::map<std::string, T> values);
        template <typename T> void Get(std::string settingName, T& value);
        template <typename T> void Get(std::string settingName, std::vector<T>& values);
        template <typename T> void Get(std::string settingName, std::map<std::string, T>& values);
};

#endif