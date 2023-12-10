#include <IRremote.h>

const int RECV_PIN = 14;
IRrecv irrecv(RECV_PIN);
decode_results results;
int ledPins[] = {9, 10, 11, 12, 13};
const int numberOfLeds = 5;
boolean isEnabled = true;

void setup(){
  irrecv.enableIRIn();
    for (int i = 0; i < numberOfLeds; i++) {
      pinMode(ledPins[i], OUTPUT);
    }
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFA25D) { // Example IR code to disable IR response
      isEnabled = !isEnabled; // Toggle the IR response on/off
    }

    if (isEnabled) {
      switch (results.value) {
        case 0xFF30CF:
          controlLED(0);
          break;
        case 0xFF18E7:
          controlLED(1);
          break;
        case 0xFF7A85:
          controlLED(2);
          break;
        case 0xFF10EF:
          controlLED(3);
          break;
        case 0xFF38C7:
          controlLED(4);
          break;
      }
    }
    irrecv.resume(); // Receive the next value
  }
}

void controlLED(int ledIndex) {
  for (int i = 0; i < numberOfLeds; i++) {
    digitalWrite(ledPins[i], LOW); // Turn off all LEDs
  }
  digitalWrite(ledPins[ledIndex], HIGH); // Turn on the selected LED
  delay(1000);
  digitalWrite(ledPins[ledIndex], LOW); // Turn off the selected LED
}