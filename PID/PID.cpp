#include "PID.h"

PID::PID(double _kP, double _kI, double _kD) {
  kP = _kP;
  kI = _kI;
  kD = _kD;
  P = 0;
  I = 0;
  D = 0;
  lastProcess = -1;
}

void PID::addNewSample(double _sample) {
  sample = _sample;
}

void PID::setSetPoint(double _setPoint) {
  setPoint = _setPoint;
}

double PID::process() {
  if (lastProcess == -1) {
    lastSample = sample;
    lastProcess = millis();
  }
  // Implementação PID
  error = setPoint - sample;
  float deltaTime = (millis() - lastProcess) / 1000.0;
  lastProcess = millis();

  //P
  P = error * kP;

  //I
  I = I + (error * kI) * deltaTime;

  //D
  D = (lastSample - sample) * kD / deltaTime;
  lastSample = sample;

  // Soma tudo
  pid = P + I + D;

  return pid;
}