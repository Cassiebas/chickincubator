#ifndef HEATER_CONTROLLER_HPP
#define HEATER_CONTROLLER_HPP

#include "HeatingElement.hpp"
#include "Thermistor.hpp"
#include "Timer.hpp"
#include "HarryPlotter"

#include <chrono>
#include <functional>
#include <thread>

class HeaterController {
    private:
        const std::string HEATER_GPIO = "12";
        Thermistor tempSensor[2] = {Thermistor(ADC::A0), Thermistor(ADC::A1)};
        Timer timer;
        Plotter plot[2];
        void ThreadCycle();
        bool threadRunning;
        std::thread timerThread;
        unsigned int heaterPercent;
    protected:
        HeatingElement heater = HeatingElement(HEATER_GPIO);
        double setTemp;
    public:
        HeaterController();
        HeaterController(double celsius);
        ~HeaterController();
        void SetTemp(double celsius);
        void SetHeaterPercent(unsigned int percentage);
        void ControllerStart();
        void ControllerStop();
        virtual void Do() = 0;
        std::vector<double> GetTemp();
        double GetTime(); //in seconds
};

#endif