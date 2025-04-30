/*

                                            *****************Bill of Materials (BOM)*****************

                                            ---> Arduino Nano
                                            ---> Display OLED SSD1306 (I2C, 128x64 pixels)
                                            ---> DHT22 (ou DHT11 como alternativa mais econômica)
                                            ---> Anemômetro (Sensor de Vento, como o modelo baseado em Reed Switch)
                                            ---> LDR (Light Dependent Resistor)
                                            ---> Resistor de Pull-up ou Pull-down (10kΩ, se necessário)
                                            ---> Resistor de carga para LDR (10kΩ, para divisor de tensão).
                                            ---> Conectores e Protoboard
                                            ---> Fonte de Alimentação
                                            ---> Opcional: Botões Push-Button (2 unidades)

                                            *****************Esquema de Conexão*****************

                                            ---> Display SSD1306:
                                            VCC_____5V
                                            GND_____GND
                                            SCL_____A5
                                            SDA_____A4 

                                            ---> DHT 22 / DHT 11
                                            VCC_____5V
                                            GND_____GND
                                            DATA_____D2

                                            ---> Anemômetro
                                            Sinal_____A0 

                                            ---> LDR
                                            Sinal_____A1

*/

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SSD1306_I2C_ADDRESS 0x27
#define DHTPIN 2
#define DHTTYPE DHT22
#define WIND_PIN A0
#define LIGHT_PIN A1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

int menuIndex = 0;
const int menuItems = 4;
String menuOptions[] = { "Umidade", "Temperatura", "Vento", "Luminosidade" };

void setup() {
  pinMode(WIND_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);

  dht.begin();
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    while (true)
      ;
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  handleMenu();
  displayMenu();
}

void handleMenu() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'u') menuIndex = (menuIndex - 1 + menuItems) % menuItems;  // Up
    if (command == 'd') menuIndex = (menuIndex + 1) % menuItems;              // Down
  }
}

void displayMenu() {
  display.clearDisplay();

  for (int i = 0; i < menuItems; i++) {
    if (i == menuIndex) {
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    } else {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    display.setCursor(0, i * 10);
    display.print(menuOptions[i]);
  }

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 50);
  display.println(getSensorData());

  display.display();
}

String getSensorData() {
  switch (menuIndex) {
    case 0:
      return String(dht.readHumidity(), 1) + "% Umidade";
    case 1:
      return String(dht.readTemperature(), 1) + " C";
    case 2:
      return String(analogRead(WIND_PIN));  // Exemplo de leitura de vento
    case 3:
      return String(analogRead(LIGHT_PIN));  // Exemplo de leitura de luminosidade
    default:
      return "";
  }
}
