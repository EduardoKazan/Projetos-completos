#include "Wifi_Config.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Wire.h>                // Chama a Wire.h para comunicação I2C
#include <Adafruit_AHTX0.h>      // Biblioteca responsável pelo AHT21
#include <Adafruit_CCS811.h>     // Biblioteca responsável pelo sensor CSS811
#include <Adafruit_BMP085.h>     // Biblioteca responsável pelo sensor BMP085
#include <Adafruit_TSL2561_U.h>  // Biblioteca responsável pelo TSL2561_U
#include <Adafruit_SSD1306.h>    // Biblioteca para o display OLED SSD1306

#define GUVA_OUT_PIN 34           // Pino analógico do sensor UV GUVA-S12S
#define SENSOR_CHUVA_AOUT_PIN 32  // Pino analógico do sensor de chuva
#define SENSOR_CHUVA_DOUT_PIN 33  // Pino digital do sensor de chuva
#define BOTAO_PIN 39              // Pino do botão para alternar entre as telas

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_AHTX0 aht;                                                                  // AHT10 no endereço 0x38
Adafruit_CCS811 ccs;                                                                 // CCS811 no endereço 0x5A
Adafruit_BMP085 bmp;                                                                 // BMP180 no endereço 0x77
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);  // TSL2561 no endereço 0x39

// WiFi e MQTT Client
WiFiClientSecure espClient;
PubSubClient client(espClient);

int sensorAtual = 0;          // Variável para alternar entre os sensores
const int totalSensores = 6;  // Total de sensores conectados

unsigned long tempoAtualizacao = 1000;  // Intervalo de tempo para atualizar o display
unsigned long ultimoTempo = 0;          // Marca o último tempo que o display foi atualizado

// Configurações do broker MQTT com SSL
const char* mqtt_server = "62.146.172.61";
const int mqtt_port = 8883;  // Porta SSL para MQTT
const char* mqtt_user = "Seu_Usuario";
const char* mqtt_password = "Sua_Senha";

void setup() {
  client.setBufferSize(1024);  // Define o tamanho do buffer das mensagens que vão o Servidor para 1024 bytes
  Serial.begin(115200);

  // Configura Wi-Fi
  setup_wifi();

  // Configura o cliente MQTT com o broker
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Configura o certificado SSL
  espClient.setCACert(CERT_CA);           // Set CA certificate
  espClient.setCertificate(CERT_CLIENT);  // Set client certificate
  espClient.setPrivateKey(KEY_CLIENT);    // Set private key

  pinMode(BOTAO_PIN, INPUT);              // Seleciona o pino do botão como entrada
  pinMode(GUVA_OUT_PIN, INPUT);           // Seleciona o pino do sensor GUVA como entrada
  pinMode(SENSOR_CHUVA_AOUT_PIN, INPUT);  // Seleciona o pino analógico do sensor de chuva como entrada
  pinMode(SENSOR_CHUVA_DOUT_PIN, INPUT);  // Seleciona o pino digital do sensor de chuva como entrada

  Wire.begin(21, 22);                                    // Inicializar comunicação I2C
  aht.begin();                                           // Inicializar o sensor AHT10
  ccs.begin();                                           // Inicializar o sensor CCS811
  bmp.begin();                                           // Inicializar o sensor BMP180
  tsl.begin();                                           // Inicializar o sensor TSL2561
  tsl.enableAutoRange(true);                             // Verifica se o TSL2561
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);  // define o tempo de integração do TSL2561

  if (!display.begin()) {  // Inicializar o display SSD1306
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();  // Limpa o display
  display.display();       // Atualiza a tela do display

  // Exibe mensagem inicial
  display.setTextSize(2);               // Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE);  // Define a cor do texto
  display.setCursor(0, 14);
  display.println(F("Estação"));  // seleciona a posição e desenha no display Estação
  display.setCursor(0, 34);
  display.println(F("Meteorológica"));  // Escreve meteorológica
  display.display();                    // atualiza o display, escrevendo a mensagem acima
  display.clearDisplay();               // limpa a tela do display
  delay(1000);                          // delay para limpar a tela
  display.setTextSize(2);               // Define o tamanho do texto
  display.setCursor(0, 14);
  display.println(F("Curto"));  // escreve curto
  display.setCursor(0, 34);
  display.println(F("Circuito"));  // escreve circuito
  display.display();               // atualiza a tela do display, escrevendo a mensagem acima
  display.clearDisplay();          // limpa a tela
  delay(1000);                     // delay de 1 segundo
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int UVLevel = analogRead(GUVA_OUT_PIN);
  float voltage = UVLevel * (3.3 / 4095.0);   // Converte a leitura para a tensão
  float UVIndex = calcularIndiceUV(voltage);  // Calcula o índice UV

  String nivelUV = getNivelUV(UVIndex);


  int valorAnalogico = analogRead(SENSOR_CHUVA_AOUT_PIN);
  int valorDigital = digitalRead(SENSOR_CHUVA_DOUT_PIN);

  String nivelChuva;
  if (valorAnalogico > 2500) {
    nivelChuva = "Sem Chuva";
  } else if (valorAnalogico > 1500) {
    nivelChuva = "Chuva Leve";
  } else if (valorAnalogico > 500) {
    nivelChuva = "Chuva Moderada";
  } else {
    nivelChuva = "Chuva Intensa";
  }
  // Indicação se está chovendo ou não com base na leitura digital
  String statusChuva = (valorDigital == HIGH) ? "Sem chuva" : "Chovendo";

  // Publica uma mensagem a cada 5 segundos
  static unsigned long lastMsg = 0;
  unsigned long now = millis();

  if (now - lastMsg > 60000) {
    lastMsg = now;

    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);

    sensors_event_t event;
    tsl.getEvent(&event);
    ccs.readData();

    //JsonDocument doc(2048);  // Ensure you have the correct version of ArduinoJson

    // Construir manualmente a string JSON
    char buffer[512];
    snprintf(buffer, sizeof(buffer),
             "{"
             "\"AHT21\": {\"Temperatura\": %.2f, \"Umidade\": %.2f},"
             "\"CCS811\": {\"CO2\": %d, \"TVOC\": %d},"
             "\"BMP180\": {\"Pressao\": %ld, \"Altitude\": %.2f},"
             "\"TSL2561\": {\"Lux\": %.2f},"
             "\"Guva\": {\"UV Index\": %.2f, \"Nivel\": \"%s\"},"
             "\"Chuva\": {\"Status\": \"%s\", \"Digital\": \"%s\"}"
             "}",
             temp.temperature,
             humidity.relative_humidity,
             ccs.geteCO2(),
             ccs.getTVOC(),
             bmp.readPressure(),
             bmp.readAltitude(),
             event.light,
             UVIndex,
             nivelUV.c_str(),
             nivelChuva.c_str(),
             (valorDigital == HIGH) ? "Sem Chuva" : "Chovendo");

    Serial.println(buffer);
    // Envia a mensagem via MQTT
    client.publish("Estacao", buffer);
  }


  botao();  // chama a função botão, responsável pela trocar as telas

  // Verifica se é hora de atualizar o display
  unsigned long tempoAtual = millis();  // Tempo atual

  if (tempoAtual - ultimoTempo >= tempoAtualizacao) {
    // Atualiza o display com o sensor selecionado
    switch (sensorAtual)  // Switch com a variavel sensorAtual, definindo qual sensor é mostrado na tela
    {
      case 0:  // Em caso 0, chama a função mostrarAHT21, mostrando no display, as informações do sensor AHT21
        mostrarAHT21();
        break;
      case 1:  // Em caso 1, chama a função mostrarCCS811, mostrando no display, as informações do sensor CCS811
        mostrarCCS811();
        break;
      case 2:  // Em caso 2, chama a função mostrarBMP180, mostrando no display, as informações do sensor BMP180
        mostrarBMP180();
        break;
      case 3:  // Em caso 3, chama a função mostrarTSL2561, mostrando no display, as informações do sensor TSL2561
        mostrarTSL2561();
        break;
      case 4:  // Em caso 4, chama a função mostrarGUVA, mostrando no display, as informações do sensor mostrarGUVA
        mostrarGUVA();
        break;
      case 5:  // Em caso 5, chama a função mostrarSensorChuva, mostrando no display, as informações do sensor Sensor Chuva
        mostrarSensorChuva();
        break;
    }

    display.display();       // Mostra os dados no display
    display.clearDisplay();  // Limpa o display para a próxima atualização

    // Atualiza o último tempo em que o display foi atualizado
    ultimoTempo = tempoAtual;
  }
}

void botao()  // Variavel para controle do botão
{
  static unsigned long lastPress = 0;
  unsigned long now = millis();
  if (digitalRead(BOTAO_PIN) == LOW)  // Quando o botão do pino 39 for pressionado
  {
    if (now - lastPress > 300) {  // debounce de 300ms
      sensorAtual++;              // Adiciona o valor do sensorAtual
      lastPress = now;
    }
  }
  // Essa função reinicia a variavel sensorAtual para voltar a primeira tela
  if (sensorAtual >= totalSensores)  // Se o valor de sensorAtual for igual ou maior que totalSensores
  {
    sensorAtual = 0;  // sensorAtual se torna 0
  }
}


void mostrarAHT21()  // Função que exibe o valor do sensor AHT21
{
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Sensor AHT21:"));
  display.setCursor(0, 20);
  display.print(F("Temp: "));
  display.print(temp.temperature);
  display.print(F(" C"));
  display.setCursor(0, 40);
  display.print(F("Umid:  "));
  display.print(humidity.relative_humidity);
  display.print(F(" %"));
}

void mostrarCCS811()  // Função que exibe o valor do sensor CCS811
{
  ccs.readData();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Sensor CCS811:"));
  display.setCursor(0, 20);
  display.print(F("CO2: "));
  display.print(ccs.geteCO2());
  display.print(F(" ppm"));
  display.setCursor(0, 40);
  display.print(F("TVOC: "));
  display.print(ccs.getTVOC());
  display.print(F(" ppb"));
}

void mostrarBMP180()  // Função que exibe o valor do senso BMP180
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Sensor BMP180:"));
  display.setCursor(0, 20);
  display.print(F("Press: "));
  display.print(bmp.readPressure());
  display.print(F(" Pa"));
  display.setCursor(0, 40);
  display.print(F("Altitude: "));
  display.print(bmp.readAltitude());
  display.print(F(" m"));
}

void mostrarTSL2561()  // Função que exibe o valor do sensor TSL2561
{
  sensors_event_t event;
  tsl.getEvent(&event);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Sensor TSL2561:"));
  if (event.light) {
    display.setCursor(0, 20);
    display.print(F("Lux: "));
    display.print(event.light);
  } else {
    display.setCursor(0, 20);
    display.print(F("Falha na leitura!"));
  }
}

void mostrarGUVA()  // Função que exibe o valor do sensor GUVA
{
  int UVLevel = analogRead(GUVA_OUT_PIN);
  float voltage = UVLevel * (3.3 / 4095.0);   // Converte a leitura para a tensão
  float UVIndex = calcularIndiceUV(voltage);  // Calcula o índice UV

  String nivelUV;
  if (UVIndex <= 2) {
    nivelUV = "Baixo";
  } else if (UVIndex <= 5) {
    nivelUV = "Moderado";
  } else if (UVIndex <= 7) {
    nivelUV = "Alto";
  } else if (UVIndex <= 10) {
    nivelUV = "Muito Alto";
  } else {
    nivelUV = "Extremo";
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Sensor GUVA: "));
  display.setCursor(0, 20);
  display.print(F("UV Index: "));
  display.print(UVIndex);
  display.setCursor(0, 40);
  display.print(F("Nivel: "));
  display.print(nivelUV);
}

float calcularIndiceUV(float voltage)  // Função para controlar indice UV
{
  float UVIndex = voltage * 15.0;
  return UVIndex;
}

String getNivelUV(float UVIndex) {
  if (UVIndex <= 2) {
    return "Baixo";
  } else if (UVIndex <= 5) {
    return "Moderado";
  } else if (UVIndex <= 7) {
    return "Alto";
  } else if (UVIndex <= 10) {
    return "Muito Alto";
  } else {
    return "Extremo";
  }
}

void mostrarSensorChuva()  // Função para ler os valores do sensor de chuva e mostrar na tela
{
  int valorAnalogico = analogRead(SENSOR_CHUVA_AOUT_PIN);
  int valorDigital = digitalRead(SENSOR_CHUVA_DOUT_PIN);

  String nivelChuva;
  if (valorAnalogico > 2500) {
    nivelChuva = "Sem Chuva";
  } else if (valorAnalogico > 1500) {
    nivelChuva = "Chuva Leve";
  } else if (valorAnalogico > 500) {
    nivelChuva = "Chuva Moderada";
  } else {
    nivelChuva = "Chuva Intensa";
  }

  // Indicação se está chovendo ou não com base na leitura digital
  String statusChuva = (valorDigital == HIGH) ? "Sem Chuva" : "Chovendo";

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Sensor de Chuva:"));
  display.setCursor(0, 20);
  display.print(nivelChuva);
  display.setCursor(0, 40);
  display.print(statusChuva);
}
// Função para conectar ao Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}

// Callback quando uma mensagem é recebida
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Função para conectar ao MQTT Broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    // Tenta se conectar
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Conectado");
      // Subscreve a um tópico após conectar
      client.subscribe("Estacao");
    } else {
      Serial.print("Falha na conexão. Código de retorno: ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      // Espera 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}