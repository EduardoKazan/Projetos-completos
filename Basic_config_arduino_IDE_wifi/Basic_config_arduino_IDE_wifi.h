/* Basic_config_arduino_IDE_wifi.h

- A biblioteca Basic_config_arduino_IDE_wifi permite configurar pinos de sensores e controle de LEDs
- O usuário pode especificar os pinos ao instanciar a classe ou usar os métodos setPinSensorX

*/
 
#ifndef BASIC_CONFIG_ARDUINO_IDE_WIFI_H
#define BASIC_CONFIG_ARDUINO_IDE_WIFI_H

// Inclui outras bibliotecas no sketch
#include <Arduino.h>
#include <Wire.h>
#include "Wifi_Config.h"

class Basic_config_arduino_IDE_wifi {
public:
  // Construtor padrão sem configurações
  Basic_config_arduino_IDE_wifi();

  // Construtor com configuração de pinos - você pode definir até 3 pinos de sensores como exemplo
  Basic_config_arduino_IDE_wifi(uint8_t pinSensor1, uint8_t pinSensor2 = 255, uint8_t pinSensor3 = 255);

  // Configurações dos pinos sensoriais (com o valor 255 indicando "não configurado")
  void setPinSensor1(uint8_t pin);
  void setPinSensor2(uint8_t pin);
  void setPinSensor3(uint8_t pin);

  // Inicializa os pinos configurados (seta modos INPUT ou OUTPUT)
  void init();

  // Método para piscar LED em um pino qualquer
  void piscarLED(int pin, int time);

  // Métodos para ler os sensores configurados - retorna valor digital ou -1 se não configurado
  int lerSensor1();
  int lerSensor2();
  int lerSensor3();

private:
  uint8_t _pinSensor1;
  uint8_t _pinSensor2;
  uint8_t _pinSensor3;

  bool pinValido(uint8_t pin);
};

#endif
