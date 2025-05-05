#ifndef PID_H
#define PID_H
#include <Arduino.h>

class PID {

public:
  double error;
  double sample;
  double lastSample;
  double kP, kI, kD;
  double P, I, D;
  double pid;
  double setPoint;
  long lastProcess;
  PID(double _kP, double _kI, double _kD);
  void addNewSample(double _sample);
  void setSetPoint(double _setPoint);
  double process();
};

#endif