#include <iostream>
#include "UI.hpp"
#include "PIDController.hpp"
#include "Motor.hpp"
#include "Humidity.hpp"
#include "Settings.hpp"
#include "Timer.hpp"

#define EGGFULLROT 7.58473625144 // seconds to rotate egg for 360 degrees, theoretical value with 1:1 relationship of how much the big gear spins and the egg spins and not accounting for backlash

bool motorTurning = false;
bool startBrakeTimer = false;
double turnAngle = 0;

void RotateEgg();
void stopMotor();

int main() {
  double setTemp = 0, p = 0, i = 0, d = 0, turnInterval = 0;
  double runtime = 0, hum = 0, temp = 0;
  UI ui;
  Motor motor;
  Humidity humidity;
  Settings settings;
  Settings machineSettings;
  machineSettings.SetPath(("../settings/machinesettings.json"));
  machineSettings.Get("runtime", runtime);
  settings.Get("heating.temperature.value", setTemp);
  settings.Get("heating.PID.P.value", p);
  settings.Get("heating.PID.I.value", i);
  settings.Get("heating.PID.D.value", d);
  settings.Get("rotation.angle.value", turnAngle);
  settings.Get("rotation.interval.value", turnInterval);
  PIDController pid(setTemp, p, i, d);  
  Timer rotateEggTimer(&RotateEgg, turnInterval * 3600);
  Timer brakeTimer; 
  rotateEggTimer.Start();
  pid.Start();
  while (1) {
    temp = pid.GetAvgTemp();
    hum = humidity.Read();
    if (ui.QuitCalled()) {
      pid(0,0,0);
      ui.SetTemperature(temp);
      ui.SetHumidity(hum);

    } else {
      //Get settings:
      machineSettings.Read();
      machineSettings.Get("runtime", runtime);
      settings.Read();
      settings.Get("heating.temperature.value", setTemp);
      settings.Get("heating.PID.P.value", p);
      settings.Get("heating.PID.I.value", i);
      settings.Get("heating.PID.D.value", d);
      settings.Get("rotation.angle.value", turnAngle);
      settings.Get("rotation.interval.value", turnInterval);
      //Update values:
      pid(p, i, d);
      pid.SetTemp(setTemp);
      ui.SetTemperature(temp);
      ui.SetHumidity(hum);
      //Control motor:
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
      // sleep(1);
    }
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
