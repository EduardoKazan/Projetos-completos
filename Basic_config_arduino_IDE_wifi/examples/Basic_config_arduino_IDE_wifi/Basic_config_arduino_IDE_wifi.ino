// Exemplo de uso da Basic_config_arduino_IDE_wifi com configuração fácil dos pinos de sensores
#include "Basic_config_arduino_IDE_wifi.h"

#define LED_BUILTIN 2

// Inclua outras bibliotecas, se necessario
// #include <DHT.h>

// Criando a instância da biblioteca passando os pinos dos sensores como parâmetros
Basic_config_arduino_IDE_wifi minhaLib(2, 3);  // Sensores nos pinos 2 e 3

void setup() {
  Serial.begin(115200);

  // Inicializa os sensores para INPUT
  minhaLib.init();

  // Se quiser alterar os pinos após criar:
  // minhaLib.setPinSensor1(4);
  // minhaLib.setPinSensor2(5);
}

void loop() {
  // Piscar LED builtin
  minhaLib.piscarLED(LED_BUILTIN, 500);

  // Ler os sensores
  int valor1 = minhaLib.lerSensor1();
  int valor2 = minhaLib.lerSensor2();

  // Exibir no monitor serial (se sensor não estiver configurado, retorna -1)
  Serial.print("Sensor 1: ");
  Serial.println(valor1);
  Serial.print("Sensor 2: ");
  Serial.println(valor2);

  delay(1000);
}
