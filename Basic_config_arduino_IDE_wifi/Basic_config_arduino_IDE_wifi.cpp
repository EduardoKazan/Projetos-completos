// Basic_config_arduino_IDE_wifi.cpp
#include "Basic_config_arduino_IDE_wifi.h"

// Construtor padrão
Basic_config_arduino_IDE_wifi::Basic_config_arduino_IDE_wifi()
  : _pinSensor1(255), _pinSensor2(255), _pinSensor3(255) {}

// Construtor com pinos configurados
Basic_config_arduino_IDE_wifi::Basic_config_arduino_IDE_wifi(uint8_t pinSensor1, uint8_t pinSensor2, uint8_t pinSensor3)
  : _pinSensor1(pinSensor1), _pinSensor2(pinSensor2), _pinSensor3(pinSensor3) {}

// Seta os pinos dos sensores
void Basic_config_arduino_IDE_wifi::setPinSensor1(uint8_t pin) {
  _pinSensor1 = pin;
}
void Basic_config_arduino_IDE_wifi::setPinSensor2(uint8_t pin) {
  _pinSensor2 = pin;
}
void Basic_config_arduino_IDE_wifi::setPinSensor3(uint8_t pin) {
  _pinSensor3 = pin;
}

// Verifica se o pino é válido
bool Basic_config_arduino_IDE_wifi::pinValido(uint8_t pin) {
  return (pin <= 54);  // A maioria dos Arduinos tem até 54 pinos digitais, ajuste conforme seu modelo
}

// Inicializa os pinos configurados como INPUT
void Basic_config_arduino_IDE_wifi::init() {
  if (pinValido(_pinSensor1) && _pinSensor1 != 255) {
    pinMode(_pinSensor1, INPUT);
  }
  if (pinValido(_pinSensor2) && _pinSensor2 != 255) {
    pinMode(_pinSensor2, INPUT);
  }
  if (pinValido(_pinSensor3) && _pinSensor3 != 255) {
    pinMode(_pinSensor3, INPUT);
  }
}

// Piscar LED no pino selecionado
void Basic_config_arduino_IDE_wifi::piscarLED(int pin, int time) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(time);
  digitalWrite(pin, LOW);
  delay(time);
}

// Ler sensores digitais (alto ou baixo), retorna -1 se o sensor não estiver configurado
int Basic_config_arduino_IDE_wifi::lerSensor1() {
  if (pinValido(_pinSensor1) && _pinSensor1 != 255) {
    return digitalRead(_pinSensor1);
  }
  return -1;
}
int Basic_config_arduino_IDE_wifi::lerSensor2() {
  if (pinValido(_pinSensor2) && _pinSensor2 != 255) {
    return digitalRead(_pinSensor2);
  }
  return -1;
}
int Basic_config_arduino_IDE_wifi::lerSensor3() {
  if (pinValido(_pinSensor3) && _pinSensor3 != 255) {
    return digitalRead(_pinSensor3);
  }
  return -1;
}
