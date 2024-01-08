#include "Settings.hpp"

#include <iostream>

int main() {
    Settings settings;
    settings.Set("turnInterval", 0.2);
    std::vector<double> PID = {30, 0.1, 2666};
    settings.Set("PID", PID);
    PID.clear();
    settings.Get("PID", PID);
    std::cout << "PID: ";
    for (double val : PID) {
        std::cout << val << ", ";
    }
    std::cout << "\n";
    double turnInterval = 0;
    settings.Get("turnInterval", turnInterval);
    std::cout << "turnInterval: " << turnInterval << "\n";
    return 0;
}