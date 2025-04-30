//tecnica de debounce via software

#include <Bounce2.h>

const int buttonPin = 2;
const int ledPin = LED_BUILTIN;

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