#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define DEFAULT_SETTINGS_PATH "../settings/settings.json"

namespace pt = boost::property_tree;

class Settings {
    private:
        pt::ptree data;
        std::string filePath = DEFAULT_SETTINGS_PATH;
    public:
        Settings();
        ~Settings();
        void Read();
        void Write();
        template <typename T>
        void Set(std::string settingName, T value);
        template <typename T>
        T Get(std::string settingName);
};

#endif