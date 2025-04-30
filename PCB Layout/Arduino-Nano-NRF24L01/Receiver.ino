
// Code 2 : Activa 4 RELE (Receiver)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(10, 9);  // CE, CSN
const byte address[10] = "ADDRESS01";

const int Q1_Pin = A0;  // RELE 1
const int Q2_Pin = A1;  // RELE 2
const int Q3_Pin = A2;  // RELE 3
const int Q4_Pin = A3;  // RELE 4

void setup() {
  Serial.begin(9600);
  pinMode(Q1_Pin, OUTPUT);
  pinMode(Q2_Pin, OUTPUT);
  pinMode(Q3_Pin, OUTPUT);
  pinMode(Q4_Pin, OUTPUT);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
};

void loop() {
  if (radio.available()) {
    char txt[5] = "";
    radio.read(&txt, sizeof(txt));
    switch (txt[1]) {
      case '1':
        digitalWrite(Q1_Pin, HIGH);
        digitalWrite(Q2_Pin, LOW);
        digitalWrite(Q3_Pin, LOW);
        digitalWrite(Q4_Pin, LOW);
        break;
      case '2':
        digitalWrite(Q1_Pin, LOW);
        digitalWrite(Q2_Pin, HIGH);
        digitalWrite(Q3_Pin, LOW);
        digitalWrite(Q4_Pin, LOW);
        break;
      case '3':
        digitalWrite(Q1_Pin, LOW);
        digitalWrite(Q2_Pin, LOW);
        digitalWrite(Q3_Pin, HIGH);
        digitalWrite(Q4_Pin, LOW);
        break;
      case '4':
        digitalWrite(Q1_Pin, LOW);
        digitalWrite(Q2_Pin, LOW);
        digitalWrite(Q3_Pin, LOW);
        digitalWrite(Q4_Pin, HIGH);
        break;
      default:
        digitalWrite(Q1_Pin, LOW);
        digitalWrite(Q2_Pin, LOW);
        digitalWrite(Q3_Pin, LOW);
        digitalWrite(Q4_Pin, LOW);
        break;
    };
    Serial.println(txt);
    delay(100);
  };
};
