/*
Controle de temperatura em uma estufa com LM35

SETPOINT = 35 GRAUS CELSIUS

Controle da temperatura -> ventoinha acionada por um transistor

Acendimento interno de uma lâmpada, que deve ocorrer de modo intermitente e a partir de um tempo predefinido. 

Resolução do LM35 = 10mV/ºC

Acionamento da lâmpada -> relé 5V

Display LCD plota os valores do processo. 
*/

#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>

#define sensor_pino A0
#define ventoinha_pino 10
#define lampada_pino 13

// Inicializa o display LCD com o endereço I2C e o tamanho do display (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // O endereço I2C pode variar, verifique se é 0x27 ou 0x3F

int referencia = 27;
int kp = 300;
int tempo = 15000000;

float temperatura;
float erro;
int saida;

void setup() {
  pinMode(sensor_pino, INPUT);
  pinMode(ventoinha_pino, OUTPUT);
  pinMode(lampada_pino, OUTPUT);

  lcd.begin(16, 2);  // Inicializa o LCD
  lcd.backlight();   // Liga a luz de fundo do LCD

  Timer1.initialize(tempo);
  Timer1.attachInterrupt(callback);
}

void loop() {
  leitura();
  saturador();
  controle();
  plotar();
}

/*
CONFIGURA FUNCAO CALLBACK
luminosidade baixa -> acender luz externa
*/
void callback() {
  digitalWrite(lampada_pino, !digitalRead(lampada_pino));
}

void leitura() {
  //CONVERSAO ADC -> (5V / (2^10 - 1) * 10mV)
  temperatura = (analogRead(sensor_pino) * 0.0488) - 5;
  erro = temperatura - referencia;
  saida = kp * erro;
}

void saturador() {
  if (saida > 255) {
    saida = 255;
  }
  if (saida < 0) {
    saida = 0;
  }
}

void controle() {
  analogWrite(ventoinha_pino, saida);
}

void plotar() {
  lcd.setCursor(0, 0);
  lcd.print("CONTROLE TEMP");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatura);
}