
// Code 1 : Envia 4 entrada digitales (Transmitter)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(10, 9);  // CE, CSN
const byte address[10] = "ADDRESS01";

const int I1_Pin = 2;  // Pushbutton I1
const int I2_Pin = 3;  // Pushbutton I2
const int I3_Pin = 4;  // Pushbutton I3
const int I4_Pin = 5;  // Pushbutton I4
char txt1[] = "I1", txt2[] = "I2", txt3[] = "I3", txt4[] = "I4", txt5[] = "00";

void setup() {
  Serial.begin(9600);
  pinMode(I1_Pin, INPUT);
  pinMode(I2_Pin, INPUT);
  pinMode(I3_Pin, INPUT);
  pinMode(I4_Pin, INPUT);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
};

void loop() {
  int I1_State = digitalRead(I1_Pin);
  int I2_State = digitalRead(I2_Pin);
  int I3_State = digitalRead(I3_Pin);
  int I4_State = digitalRead(I4_Pin);

  if (I1_State == HIGH) {
    radio.write(&txt1, sizeof(txt1));
    Serial.println(txt1);
  } else if (I2_State == HIGH) {
    radio.write(&txt2, sizeof(txt2));
    Serial.println(txt2);
  } else if (I3_State == HIGH) {
    radio.write(&txt3, sizeof(txt3));
    Serial.println(txt3);
  } else if (I4_State == HIGH) {
    radio.write(&txt4, sizeof(txt4));
    Serial.println(txt4);
  } else {
    radio.write(&txt5, sizeof(txt5));
    Serial.println(txt5);
  };
  delay(100);
};
