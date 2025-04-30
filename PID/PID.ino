/*




*/

#include "PID.h"

#define pSENSOR A1
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