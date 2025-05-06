#define LATCH_pin 8   // (8) ST_CP [RCK] no 74HC595
#define CLCOK_pin 12  // (12) SH_CP [SCK] no 74HC595
#define DATA_pin 11   // (11) DS [S1] no 74HC595

unsigned char binary_pattern[] = {
  0b11111010,
  0b01100000,
  0b11011100,
  0b11110100,
  0b01100110,
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,
  0b11100110,
};
unsigned int counter = 0;

void clock_signal(void) {
  digitalWrite(CLCOK_pin, HIGH);
  delayMicroseconds(500);
  digitalWrite(CLCOK_pin, LOW);
  delayMicroseconds(500);
}
void latch_enable(void) {
  digitalWrite(LATCH_pin, HIGH);
  delayMicroseconds(500);
  digitalWrite(LATCH_pin, LOW);
}
void send_data(unsigned int data_out) {
  int i;
  unsigned hold;
  for (i = 0; i < 8; i++) {
    if ((data_out >> i) & (0x01))
      digitalWrite(DATA_pin, HIGH);
    else
      digitalWrite(DATA_pin, LOW);

    clock_signal();
  }
  latch_enable();  // Dados finalmente enviados
}

void setup() {
  pinMode(LATCH_pin, OUTPUT);
  pinMode(DATA_pin, OUTPUT);
  pinMode(CLCOK_pin, OUTPUT);
  digitalWrite(LATCH_pin, LOW);  // (11) ST_CP [RCK] no 74HC595
  digitalWrite(CLCOK_pin, LOW);  // (9) SH_CP [SCK] no 74HC595
  digitalWrite(DATA_pin, LOW);   // (12) DS [S1] no 74HC595
  Serial.begin(9600);
}

void loop() {

  send_data(binary_pattern[counter]);
  counter++;
  if (counter > 9)
    counter = 0;
  delay(500);
}