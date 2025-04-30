#include <IRremoteESP8266.h>

// Define the IR receiver pin
#define IR_RECEIVER_PIN 32

// Create an instance of the IR receiver
IRrecv irReceiver(IR_RECEIVER_PIN);

// Define the decode results variable
decode_results results;

void setup() {
  // Start the serial communication
  Serial.begin(115200);

  // Initialize the IR receiver
  irReceiver.enableIRIn();
}

void loop() {
  // Check if the IR receiver has received a signal
  if (irReceiver.decode(&results)) {
    // Print the decoded value
    Serial.println(results.value, HEX);

    // Decode the next signal
    irReceiver.decode(&results);
  }
}