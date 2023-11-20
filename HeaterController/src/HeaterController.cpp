#include "HeaterController.hpp"

HeaterController::HeaterController() {

}

HeaterController::HeaterController(double celsius) : setTemp(celsius){

}

HeaterController::~HeaterController() {
    ControllerStop();
}

void HeaterController::SetTemp(double celsius) {
    setTemp = celsius;
}

void HeaterController::SetHeaterPercent(unsigned int percentage) {
    heaterPercent = percentage;
}

void HeaterController::ControllerStart() {      
    threadRunning = true;
    timerThread = std::thread(&HeaterController::ThreadCycle, this);
    timer.Start();
    heater(heaterPercent);
    heater.Start();
}

void HeaterController::ControllerStop() {
    threadRunning = false;
    if (timerThread.joinable()) {
        timerThread.join();
    }
    timer.Stop();
    heater.Stop();
    plot[0].ExportAsPNG("", "A0", "Time (m)", "Temperature (°C)", "T(s)");
    plot[1].ExportAsPNG("", "A1", "Time (m)", "Temperature (°C)", "T(s)");
}

std::vector<double> HeaterController::GetTemp() {
    return std::vector<double>{tempSensor[0].Temperature(), tempSensor[1].Temperature()};
}

double HeaterController::GetTime() {
    return timer.Elapsed();
}

void HeaterController::ThreadCycle() {    
    while (threadRunning) {    
        std::cout << "A0 temperature: " << tempSensor[0].Temperature() << "°C\n";
        std::cout << "A1 temperature: " << tempSensor[1].Temperature() << "°C\n";
        std::cout << "Elapsed time: " << timer.Elapsed() << "s\n";
        plot[0].AddPoint(timer.Elapsed()/60.0, tempSensor[0].Temperature());
        plot[1].AddPoint(timer.Elapsed()/60.0, tempSensor[1].Temperature());
        Do(); //must be overwritten by derived class
    }
}