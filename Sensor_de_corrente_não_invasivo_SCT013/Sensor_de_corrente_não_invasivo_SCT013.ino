//Programa : Medidor de corrente com Arduino e SCT-013 100A

//Carrega as bibliotecas
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "EmonLib.h"
#include <SPI.h>

EnergyMonitor emon1;

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

//Tensao da rede eletrica
int rede = 220;

//Pino do sensor SCT
int pino_sct = A1;

void setup() {
  Serial.begin(9600);
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pino_sct, 60);
  //Ajuste iniciais display
  display.begin();
  //Ajusta o contraste do display
  display.setContrast(48);
  //Apaga o buffer e o display
  display.clearDisplay();
  //Define tamanho do texto e cor
  display.setTextSize(1);
  display.setTextColor(BLACK);

  //Retangulo principal
  display.drawRect(0, 0, 84, 48, 2);
  //Retangulo corrente
  display.fillRect(0, 0, 84, 15, 2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(18, 4);
  display.println("Corrente");
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(2);
}

void loop() {
  //Calcula a corrente
  double Irms = emon1.calcIrms(1480);
  //Mostra o valor da corrente no serial monitor e display
  Serial.print("Corrente : ");
  Serial.print(Irms);  // Irms

  display.fillRect(4, 15, 55, 20, 0);
  display.setCursor(8, 22);
  display.println(Irms, 2);
  display.display();
  display.setCursor(67, 22);
  display.println("A");
  delay(1000);
}