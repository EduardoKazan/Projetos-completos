/*
  Projeto adaptado do canal INTERNET E COISAS
  Rastreamento via GPS e MQTT

**************Links importantes**************
Página Exemplo:
https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbk1iSTg0QThPeGxNY3FRNEhhSWh1TFlpdDBMUXxBQ3Jtc0trbU5BTVdRelhWaldNOHRCYTJrWFE1a2ZURk1BcC1hNm5nX2N1NzhQbks0c1hIXzFxOWpXTE4ybVhOWFE1WURJWmFCeTJRYUVRUS1MUG8zYlZsQkZLUXk2djVoMFpiVl9QN2lkN2FyYkVodGVmLUJQYw&q=http%3A%2F%2Finternetecoisas.com.br%2Fexemplo%2FIeC72.htm&v=q13g1ONijd8

Sketch de Teste:
https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbUZBU05jZllGS1RGMUgtSUpoRHNvMVNKVzM5d3xBQ3Jtc0tuVWp3YnZ0OW9kWjZxckd3WFh3VEJVUm9FVGphVkZCODJ0UXgxdjFITGQxN3B3emJodnRyMDZqNmNlWnNYQkhyQm1Uc0kxNkd2RFVzY19jSlFUbS14OTc5bnhZVzZ3bmpXU3k0WF9kZkRSYTZDLTZsYw&q=https%3A%2F%2Finternetecoisas.com.br%2Fdownload%2FIeC72-RastreamentoGPS.zip&v=q13g1ONijd8

Ambiente MQTT Internet e Coisas:
https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbW5Ra0RHVTdfelREMTNqcHRKUUNSMXowUjFCZ3xBQ3Jtc0tsc2NWWVdFVWoxN25GZ1VMTFl2UjFsTzhaVlJCSmZ2TnJvaEJGc1Y0czZPSHc2WHkya2VoYnVkYkdIaXdFdGhBeG5SbGRaQ3RzZmU1NWRueWFMYWFRdFdxNlZBd0Jqa1N0Z0hETmhZSHVrdFZ3Q0ZoRQ&q=https%3A%2F%2Finternetecoisas.com.br%2F%3Fmqtt&v=q13g1ONijd8
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <TimeLib.h>
#include <TinyGPS++.h>
#include "Wifi_Config.h"

const int GPS_BPS = 115200;                                             // GPS Velocidade
const int DATETIME_INT = 60;                                            // Intervalo atualizacao Data/Hora (60s)
const char* MQTT_SERVER = "mqtt.internetecoisas.com.br";                // Broker
const int MQTT_PORT = 8883;                                             // Porta
const char* MQTT_CLIENT = "IeCTracking";                                // Cliente
const char* MQTT_GPS_LAT_TOPIC = "IeCTracking/posicao/latitude";        // Topico Latitude
const char* MQTT_GPS_LON_TOPIC = "IeCTracking/posicao/longitude";       // Topico Longitude
const char* MQTT_GPS_AGE_TOPIC = "IeCTracking/posicao/age";             // Topico Age
const char* MQTT_GPS_HDOP_TOPIC = "IeCTracking/posicao/hdop";           // Topico HDOP
const char* MQTT_GPS_UPDATE_TOPIC = "IeCTracking/posicao/atualizacao";  // Topico Atualizacao

WiFiClient espClient;            // Instancia para WiFi
PubSubClient client(espClient);  // Instancia para MQTT
TinyGPSPlus gps;

float absolute(const float x) {
  return x < 0 ? -x : x;  // Retorna valor absoluto
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connectando Broker...");
    if (client.connect(MQTT_CLIENT)) {  // Usando MQTT_CLIENT diretamente
      Serial.println("Conectado");
    } else {
      Serial.println("Falha");
      delay(5000);
    }
  }
}

time_t timeGPS() {
  // Obtem data/hora do GPS
  if (gps.time.isValid() && gps.time.age() < 1000) {
    // Obtem Data/Hora do GPS
    Serial.println("Data/Hora atualizada");
    setSyncInterval(DATETIME_INT);
    TimeElements te;
    te.Year = gps.date.year() - 1970;
    te.Month = gps.date.month();
    te.Day = gps.date.day();
    te.Hour = gps.time.hour();
    te.Minute = gps.time.minute();
    te.Second = gps.time.second();
    return makeTime(te);
  }
  Serial.println("Falha obtendo Data/Hora");
  setSyncInterval(2);
  return 0;
}

String dateTimeStr(time_t t, const int8_t tz = 0, const bool flBr = true) {
  // Retorna time_t como "yyyy-mm-dd hh:mm:ss" ou "dd/mm/yyyy hh:mm:ss"
  if (t == 0) {
    return F("N/A");
  }
  t += tz * 3600;
  String sFn;
  if (flBr) {
    // dd/mm/yyyy hh:mm:ss
    sFn = "";
    if (day(t) < 10) {
      sFn += '0';
    }
    sFn += String(day(t)) + '/';
    if (month(t) < 10) {
      sFn += '0';
    }
    sFn += String(month(t)) + '/' + String(year(t)) + ' ';
  } else {
    // yyyy-mm-dd hh:mm:ss
    sFn = String(year(t)) + '-';
    if (month(t) < 10) {
      sFn += '0';
    }
    sFn += String(month(t)) + '-';
    if (day(t) < 10) {
      sFn += '0';
    }
    sFn += String(day(t)) + ' ';
  }
  if (hour(t) < 10) {
    sFn += '0';
  }
  sFn += String(hour(t)) + ':';
  if (minute(t) < 10) {
    sFn += '0';
  }
  sFn += String(minute(t)) + ':';
  if (second(t) < 10) {
    sFn += '0';
  }
  sFn += String(second(t));
  return sFn;
}

String dateTimeISO8601(const time_t& t, const int8_t tz = 0) {
  // Retorna time_t como ISO8601
  String s = dateTimeStr(t, tz, false);
  s.replace(" ", "T");
  if (tz == 0) {
    // Fuso UTC
    s += "Z";
  } else {
    // Fuso especificado
    s = s + ((tz < 0) ? "-" : "+") + ((tz < 10) ? "0" : "") + String(abs(tz)) + ":00";
  }
  return s;
}

void setup() {
  Serial.begin(GPS_BPS);  // Inicializa a Serial padrão para GPS

  randomSeed(analogRead(0));

  // Conecta Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Conectando WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nWiFi conectado");
  }

  // Define Data/Hora
  setSyncProvider(timeGPS);
}

// Variaveis globais
float lat = 0;          // Latitude
float lon = 0;          // Longitude
float hdop = 0;         // HDOP
time_t nextUpdate = 0;  // Data/Hora
bool flUpdate = false;  // Flag atualizacao

void loop() {
  // Conexao ao Broker
  if (client.connected()) {
    client.loop();
  } else {
    reconnect();
  }

  // Processa GPS
  while (Serial.available()) {
    gps.encode(Serial.read());
  }

  // Verifica alteracao
  if (gps.time.isUpdated()) {
    // Dados disponiveis
    Serial.print("Satélites: ");
    Serial.print(gps.satellites.value());
    Serial.printf("\t Data/Hora: %02d/%02d/%02d %02d:%02d:%02d\n",
                  gps.date.day(),
                  gps.date.month(),
                  gps.date.year(),
                  gps.time.hour(),
                  gps.time.minute(),
                  gps.time.second());
    if (gps.location.isValid()) {
      // Posicao
      if (absolute(lat - gps.location.lat()) > 0.00009) {
        // Atualiza Latitude
        Serial.println("Atualiza Latitude");
        lat = gps.location.lat();
        client.publish(MQTT_GPS_LAT_TOPIC, String(lat, 6).c_str(), true);  // Publica a latitude
        flUpdate = true;
      }
      if (absolute(lon - gps.location.lng()) > 0.00009) {
        // Atualiza Longitude
        Serial.println("Atualiza Longitude");
        lon = gps.location.lng();
        client.publish(MQTT_GPS_LON_TOPIC, String(lon, 6).c_str(), true);  // Publica a longitude
        flUpdate = true;
      }
      if (gps.hdop.isValid()) {
        // HDOP
        if (absolute(hdop - gps.hdop.hdop()) > 0.1) {
          // Atualiza HDOP
          Serial.println("Atualiza HDOP");
          hdop = gps.hdop.hdop();
          client.publish(MQTT_GPS_HDOP_TOPIC, String(hdop, 1).c_str(), true);  // Publica o HDOP
          flUpdate = true;
        }
      }
    }
  }
  if ((flUpdate || now() >= nextUpdate)) {
    // Atualizacao ou intervalo
    nextUpdate = now();
    // Exibe dados no Serial Monitor
    Serial.println("Publicando: " + dateTimeISO8601(nextUpdate) + "\tLat: " + String(lat, 6) + "\tLon: " + String(lon, 6) + "\tHDOP: " + String(hdop, 1));
    // Atualiza Age
    client.publish(MQTT_GPS_AGE_TOPIC, String(gps.location.age()).c_str(), true);  // Publica a idade
    // Atualiza Data/Hora
    client.publish(MQTT_GPS_UPDATE_TOPIC, dateTimeISO8601(nextUpdate).c_str(), true);  // Publica a data /hora
    // Proxima atualizacao em 60s
    nextUpdate += 60;
    flUpdate = false;
  }
}