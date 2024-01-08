#include "Settings.hpp"

#include <iostream>

int main() {
    Settings settings;
    std::cout << "Settings: ";
    for (std::string name : settings.List()) {
        std::cout << name << ", ";
        if (settings.IsNested(name)) {
            std::cout << ": {";
            for (std::string nestedName : settings.List(name)) {
                std::cout << nestedName << ", ";
            }
            std::cout << "}, ";
        }
    }
    std::cout << "\n";

    settings.Set("turnInterval", 0.2);

    std::map<std::string, double> PID = { {"p", 30}, {"i", 0.1}, {"d", 2666}};
    settings.Set("PID", PID);

    PID.clear();
    settings.Get("PID", PID);
    std::cout << "PID: ";
    for (std::pair<std::string, double> val : PID) {
        std::cout << val.first << ": " << val.second << ", ";
    }
    std::cout << "\n";

    double turnInterval = 0;
    settings.Get("turnInterval", turnInterval);
    std::cout << "turnInterval: " << turnInterval << "\n";
    return 0;
}