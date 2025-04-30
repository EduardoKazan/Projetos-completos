#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>

RotaryEncoder encoder(A0, A1, RotaryEncoder::LatchMode::FOUR3);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  lcd.print("PollRotatorLCD");
}

void loop() {
  static int pos = 0;
  encoder.tick();

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    lcd.setCursor(0, 1);
    lcd.print(newPos);
    lcd.print(" ");
    pos = newPos;
  }
}