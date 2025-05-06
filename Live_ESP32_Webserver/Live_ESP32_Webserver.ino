#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <Wifi_Config.h>

#define LEDPIN 22
#define strip1_Pin 16  //  Pino de sinal

WebServer server(80);

const int strip1_NumLeds = 8, MAX_NUM_LEDS = 8;

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(strip1_NumLeds, strip1_Pin, NEO_GRB + NEO_KHZ800);

// Variáveis de Cores
uint32_t white = strip1.Color(255, 255, 255);
uint32_t blue = strip1.Color(0, 0, 255);
uint32_t red = strip1.Color(255, 0, 0);
uint32_t green = strip1.Color(0, 255, 0);
uint32_t orange = strip1.Color(255, 153, 0);
uint32_t purple = strip1.Color(255, 0, 255);
uint32_t pink = strip1.Color(255, 153, 255);
uint32_t yellow = strip1.Color(255, 255, 0);
uint32_t gold = strip1.Color(153, 153, 0);
uint32_t cyan = strip1.Color(0, 255, 255);
uint32_t black = strip1.Color(0, 0, 0);
uint32_t selColor, currentColor;
uint8_t r, g, b;
uint32_t AliceBlue = 0xF0F8FF;
uint32_t Chocolate = 0xD2691E;

float temperature = 0, humidity = 0, pressure = 0;

String ledState = "OFF", colorValue, colorNumCode, redHex, greenHex, blueHex;

int redInt = 0, greenInt = 0, blueInt = 0;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);
  initSensor();
  connectToWifi();
  beginServer();

  // Inicia Fita
  strip1.begin();
  strip1.show();

  // Inicia Brilho
  strip1.setBrightness(200);
}

void loop() {
  server.handleClient();

  getTemperature();
  getHumidity();
  getPressure();
  delay(1000);
}

void connectToWifi() {
  WiFi.enableSTA(true);

  delay(2000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void beginServer() {
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  //if ( server.hasArg("LED") || server.hasArg("COLOR")) {
  if (server.hasArg("COLOR")) {
    handleSubmit();
  } else {
    server.send(200, "text/html", getPage());
  }
}

void handleSubmit() {

  colorValue = server.arg("COLOR");

  colorNumCode = colorValue.substring(1, 7);
  redHex = colorValue.substring(1, 3);
  greenHex = colorValue.substring(3, 5);
  blueHex = colorValue.substring(5, 7);

  int number = (int)strtol(&colorValue[1], NULL, 16);

  // Split them up into r, g, b values
  redInt = number >> 16;
  greenInt = number >> 8 & 0xFF;
  blueInt = number & 0xFF;

  String LEDValue;
  LEDValue = server.arg("LED");
  Serial.println("Set GPIO ");
  Serial.print(LEDValue);

  // Acende leds conforme cor do picker
  for (int i = 0; i < MAX_NUM_LEDS; i++) {
    strip1.setPixelColor(i, strip1.Color(redInt, greenInt, blueInt));
    delay(100);
  }
  strip1.show();
  server.send(200, "text/html", getPage());


  if (LEDValue == "1") {
    //digitalWrite(LEDPIN, HIGH);

    for (int i = 0; i < MAX_NUM_LEDS; i++) {
      strip1.setPixelColor(i, blue);
      //delay (100);
    }
    strip1.show();

    ledState = "On";
    server.send(200, "text/html", getPage());
  } else if (LEDValue == "0") {
    //digitalWrite(LEDPIN, LOW);
    for (int i = 0; i < MAX_NUM_LEDS; i++) {
      strip1.setPixelColor(i, black);
      //delay (100);
    }
    strip1.show();
    ledState = "Off";
    server.send(200, "text/html", getPage());
  } else {
    Serial.println("Error Led Value");
  }
}

String getPage() {
  String page = "<html lang=en-EN><head><meta http-equiv='refresh' content='60'/>";
  page += "<title>ESP32 WebServer Led Strip FunBots</title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }</style>";
  page += "</head><body><h1>ESP32 WebServer Led Strip FunBots</h1>";
  page += "<h3>Selected Color</h3>";
  page += "<ul><li>Color Code R: ";
  page += redInt;
  page += " G: ";
  page += greenInt;
  page += " B: ";
  page += blueInt;
  page += "</li></ul>";
  page += "&deg;C</li>";
  page += "<li>Humidity: ";
  page += humidity;
  page += "%</li>";
  page += "<li>Barometric Pressure: ";
  page += pressure;
  page += " hPa</li></ul>";
  page += "<h3>LED STRIP</h3>";
  page += "<form action='/' method='POST'>";
  page += "<ul><li>LED";
  page += "";
  page += "<INPUT type='radio' name='LED' value='1'>ON";
  page += "<INPUT type='radio' name='LED' value='0'>OFF</li></ul>";

  page += "<ul><li>COLOR";
  page += "";
  page += "<label for='colorpicker'>Color Picker:</label>";
  page += "<INPUT type='color' name='COLOR' id='colorpicker' value='#0000ff'></li></ul>";

  page += "<INPUT type='submit' value='Submit'>";

  page += "</form>";
  page += "</body></html>";
  return page;
}
