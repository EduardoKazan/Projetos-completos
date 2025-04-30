/*
  ESP-NOW Remote Sensor - Receiver
  esp-now-rcv.ino
  Receives Temperature & Humidity data from other ESP32 via ESP-NOW
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include required libraries
#include <WiFi.h>
#include <esp_now.h>

// Define data structure
typedef struct struct_message {
  float a;
  float b;
} struct_message;

// Create structured data object
struct_message myData;

// Callback function
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  // Get incoming data
  memcpy(&myData, incomingData, sizeof(myData));

  // Print to Serial Monitor
  Serial.print("Temp: ");
  Serial.println(myData.a);

  Serial.print("Humidity: ");
  Serial.println(myData.b);
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);

  // Start ESP32 in Station mode
  WiFi.mode(WIFI_STA);

  // Initalize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}