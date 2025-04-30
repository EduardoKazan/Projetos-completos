#include <DHT.h>
#include <tago.h>

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

tago tag("CLARO_2G9F971E",
         "WrZHU48hzz",
         "8cd24288-f0ea-48f7-a8be-f8d50f4048dc");  // ssid, password and tago apikey

void setup() {

  Serial.begin(115200);

  if (!tag.connectWifi()) {
    Serial.println("not connected");
    while (1)
      ;
  }
  Serial.println("Wifi connected");
  delay(1000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler do DHT!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C\tHumidity: ");
  Serial.print(h);
  Serial.println(" %");

  tag.sendData("Temperatura (°C):", String(t));
  tag.sendData("Umidade (°C):", String(h));
  delay(1000);
}
