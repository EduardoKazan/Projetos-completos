#define led 2
#define interrup 3

void setup() {
  pinMode(led, OUTPUT);
  pinMode(interrup, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrup), interrupcao_ext, RISING);
}

void loop() {
  interrup_int();
}

//FUNCAO INTERRUPCAO EXTERNA

void interrupcao_ext() {
  digitalWrite(led, HIGH);
  delay(5000);
}

void interrup_int() {
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
}