#include <IRremote.h>

// Define the IR receiver pin
#define IR_RECEIVER_PIN 11

// Create an instance of the IRrecv class
IRrecv irrecv(IR_RECEIVER_PIN);

// Define a variable to store the decoded IR signal
decode_results results;

void setup() {
  // Start the serial communication at 9600 baud
  Serial.begin(9600);

  // Initialize the IR receiver
  irrecv.enableIRIn();
}

void loop() {
  // Check if a new IR signal has been received
  if (irrecv.decode(&results)) {
    // Print the hexadecimal code of the IR signal
    Serial.println(results.value, HEX);
    Serial.println();

    // Enable the IR receiver for the next signal
    irrecv.resume();
  }
}