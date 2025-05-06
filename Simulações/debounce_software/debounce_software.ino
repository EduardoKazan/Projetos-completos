// Tecnica de debounce via software
#include <Bounce2.h>

#define buttonPin 2
#define ledPin LED_BUILTIN

Bounce debouncer = Bounce();

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  debouncer.attach(buttonPin);
  debouncer.interval(5);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  debouncer.update();
  int buttonState = debouncer.read();
  if (buttonState == LOW) {
    digitalWrite(ledPin, !digitalRead(ledPin));
    delay(10);
  }
}