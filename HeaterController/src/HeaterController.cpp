#include "HeaterController.hpp"

HeaterController::HeaterController() 
    : log(Log("../logs/", "eggcubator.log", "HeaterController", true)) 
{

}

HeaterController::HeaterController(double celsius) 
    : setTemp(celsius), log(Log("../logs/", "eggcubator.log", "HeaterController", true)) 
{

}

HeaterController::~HeaterController() {
    // ControllerStop(); //unexpected behavior
}

void HeaterController::SetTemp(double celsius) {
    // std::cout << "SetTemp(" + std::to_string(celsius) + ")\n";
    log(Severity::trace, "SetTemp(" + std::to_string(celsius) + ")");
    setTemp = celsius;
}

void HeaterController::SetHeaterPercent(unsigned int percentage) {
    // std::cout << "SetHeaterPercent(" + std::to_string(percentage) + ")\n";
    log(Severity::trace, "SetHeaterPercent(" + std::to_string(percentage) + ")");
    heaterPercent = percentage;
}

void HeaterController::ControllerStart() {      
    threadRunning = true;
    controllerThread = std::thread(&HeaterController::ThreadCycle, this);
    timer.Start();
    heater(heaterPercent);
    heater.Start();
    log(Severity::trace, "ControllerStart()");
}

void HeaterController::ControllerStop() {
    threadRunning = false;
    if (controllerThread.joinable()) {
        controllerThread.join();
    }
    timer.Stop();
    heater.Stop();
    plot[0].ExportToPNG("plots/", "A0", "Time (m)", "Temperature (°C)", "T(t)");
    plot[1].ExportToPNG("plots/", "A1", "Time (m)", "Temperature (°C)", "T(t)");
    log(Severity::trace, "ControllerStop()");
}

std::vector<double> HeaterController::GetTemp() {
    return std::vector<double>{tempSensor[0].Temperature(), tempSensor[1].Temperature()};
}

double HeaterController::GetTime() {
    return timer.Elapsed();
}

void HeaterController::ThreadCycle() {    
    while (threadRunning) {    
        // std::cout << "A0 temperature: " << tempSensor[0].Temperature() << "°C\n";
        // std::cout << "A1 temperature: " << tempSensor[1].Temperature() << "°C\n";
        // std::cout << "Elapsed time: " << timer.Elapsed() << "s\n";
        plot[0].AddPoint(timer.Elapsed()/60.0, tempSensor[0].Temperature());
        plot[1].AddPoint(timer.Elapsed()/60.0, tempSensor[1].Temperature());
        // log(Severity::info, "A0 : " + std::to_string(timer.Elapsed()/60.0) + " min , " + std::to_string(tempSensor[0].Temperature()) + " °C");
        // log(Severity::info, "A1 : " + std::to_string(timer.Elapsed()/60.0) + " min , " + std::to_string(tempSensor[1].Temperature()) + " °C");
        Do(); //must be overwritten by derived class
    }
}