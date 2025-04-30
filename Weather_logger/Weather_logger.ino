#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "CLARO_2G9F971E";
const char* password = "WrZHU48hzz";
const char* mqttServer = "test.mosquitto.org";  // Servidor MQTT
const char* mqttTopic1 = "temperature";         // Tópico MQTT 1
const char* mqttTopic2 = "humidity";            // Tópico MQTT 2
const char* mqttId = "Kazan";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado!");

  client.setServer(mqttServer, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler do DHT!");
    return;
  }

  String message1 = String("Temperature: ") + t + String(" degrees Celsius");
  String message2 = String("Humidity: ") + h + String("%");

  // Publica a mensagem no tópico MQTT 1
  Serial.println(message1);
  client.publish(mqttTopic1, message1.c_str());
  delay(1000);

  // Publica a mensagem no tópico MQTT 2
  Serial.println(message2);
  Serial.println();
  client.publish(mqttTopic2, message2.c_str());

  // Aguarda 1 segundo antes da próxima leitura
  delay(1000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect(mqttId)) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}
