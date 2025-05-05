#include "PID.h"

#define pSENSOR 35
#define pCONTROLE 3

PID meuPid(1.0, 0, 0);

void setup() {
	Serial.begin(9600);
	pinMode(pSENSOR, INPUT);
	pinMode(pCONTROLE, OUTPUT);
}

int controlePwm = 50;

void loop() {
	// Lê temperatura
	double temperature = map(analogRead(pSENSOR), 0, 1023, 0, 100);

	// Manda pro objeto PID!
	meuPid.addNewSample(temperature);

	// Converte para controle
	controlePwm = (meuPid.process() + 50);

	// Saída do controle
	analogWrite(pCONTROLE, controlePwm);
}

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