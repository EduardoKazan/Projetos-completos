#define rele 3

void setup() {
  pinMode(rele, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(rele, 1);
  Serial.print("LIGADO");
  delay(500);
  digitalWrite(rele, 0);
  Serial.print("DESLIGADO");
  delay(500);
}
