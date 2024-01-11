#include <iostream>
#include "UI.hpp"
#include "PIDController.hpp"
#include "Motor.hpp"
#include "Humidity.hpp"
#include "Settings.hpp"
#include "Thermistor.hpp"
#include "Timer.hpp"

#define EGGFULLROT 7.58473625144 // seconds to rotate egg for 360 degrees, theoretical value with 1:1 relationship of how much the big gear spins and the egg spins

bool motorTurning = false;
bool startBrakeTimer = false;
double turnAngle = 360;

void RotateEgg();
void stopMotor();

int main() {
    UI ui;
    Motor motor;
    Humidity humidity;
    Thermistor thermistor[2] = {Thermistor(ADC::A0), Thermistor(ADC::A1)};
    Settings settings("../settings/settings.json");
    double setTemp, p, i, d, turnInterval; //all settings
    double avgTemp;
    settings.Get("heating.temperature", setTemp);
    settings.Get("heating.PID.P", p);
    settings.Get("heating.PID.I", i);
    settings.Get("heating.PID.D", d);
    settings.Get("rotation.angle", turnAngle);
    settings.Get("rotation.interval", turnInterval);
    Timer rotateEggTimer(&RotateEgg, turnInterval * 3600);
    Timer brakeTimer; //EGGFULLROT * (turnAngle / 360.0
    rotateEggTimer.Start();
    PIDController pid(setTemp, p, i, d);
    pid.Start();
    while (1) {
        settings.Read();
        settings.Get("heating.temperature", setTemp);
        settings.Get("heating.PID.P", p);
        settings.Get("heating.PID.I", i);
        settings.Get("heating.PID.D", d);
        settings.Get("rotation.angle", turnAngle);
        settings.Get("rotation.interval", turnInterval);
        std::cout << "Settings: " << setTemp << " " << p << " " << i << " " << d << " " << turnAngle << " " << turnInterval << "\n";
        pid(p, i, d);
        avgTemp = (thermistor[0].Temperature() + thermistor[1].Temperature())/2;
        ui.SetTemperature(avgTemp);
        ui.SetHumidity(humidity.Read());
        if (startBrakeTimer) {
          brakeTimer.Start();
          startBrakeTimer = false;
        }
        if (brakeTimer.Elapsed() >= EGGFULLROT * (turnAngle / 360.0)) {
          stopMotor();
          brakeTimer.Stop();
        }
        if (motorTurning) 
            motor.Forward();
        else
            motor.Brake();
    }
    pid.Stop();
    rotateEggTimer.Stop();
    return 0;
}

void RotateEgg() {
  startBrakeTimer = true;
  motorTurning = true;
}

void stopMotor()
{
  motorTurning = false;
}