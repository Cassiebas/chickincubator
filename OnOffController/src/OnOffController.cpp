#include "OnOffController.hpp"

OnOffController::OnOffController(double setTemp) {
    SetTemp(setTemp);
}

OnOffController::~OnOffController() {

}

void OnOffController::Start() {
    SetHeaterPercent(100);
    ControllerStart();
}

void OnOffController::Stop() {
    ControllerStop();
}

void OnOffController::Do() {
    std::vector<double> temps = GetTemp();
    if (heaterOn) {
        if (temps.at(0) > setTemp || temps.at(1) > setTemp) {
            heater.Stop();
            heaterOn = false;
        }
    } else {
        if (temps.at(0) < setTemp && temps.at(1) < setTemp) {
            heater.Start();
            heaterOn = true;
        }
    }
}