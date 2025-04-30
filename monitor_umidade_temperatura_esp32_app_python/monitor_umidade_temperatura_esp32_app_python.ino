#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>

#define DHTPIN 5       
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "CLARO_2G9F971E";  // Substitua pelo seu SSID
const char* password = "WrZHU48hzz";   // Substitua pela sua senha

WebServer server(80);

void handleRoot() {
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verifica se a leitura do sensor foi bem-sucedida
  if (isnan(umidade) || isnan(temperatura)) {
    server.send(500, "text/plain", "Erro ao ler do sensor DHT");
    return;
  }

  String response = String(umidade) + "e" + String(temperatura);
  server.send(200, "text/plain", response);  // Envia os dados
}

void handleNotFound() {
  String message = "Arquivo não encontrado\n";
  server.send(404, "text/plain", message);
}

void setup() {
  dht.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Aguarda a conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("Servidor MDNS iniciado");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop(void) {
  server.handleClient();
  delay(1500);
  float u = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Umidade (%): ");
  Serial.print(u, 1);
  Serial.print("\t");
  Serial.print("Temperatura (C): ");
  Serial.print(t, 1);
  Serial.print("\t");
  Serial.println();
}