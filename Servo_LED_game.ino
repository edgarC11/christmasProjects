#include <Servo.h>
#include <IRremote.h>

Servo myServo;  // create servo object

const int servoPin = 3; // Servo motor pin
const int buzzerPin = 7; // Buzzer pin
const int ledPins[] = {8, 9, 10, 11, 12}; // LED pins
const int numLeds = 5;
int ledSequence[5]; // array to store the sequence

const int irPin = 14; // IR receiver pin
IRrecv irrecv(irPin);
decode_results results;

void setup() {
  myServo.attach(servoPin); // attach servo
  pinMode(buzzerPin, OUTPUT); // set buzzer pin as output
  irrecv.enableIRIn(); // start the receiver
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  startBuzz();
}

void loop() {
  generateSequence();
  showSequence();
  endBuzz();
  if (getPlayerInput()) {
    correctBuzz();
  } else {
    incorrectBuzz();
  }
  delay(1000); // Delay before next round
}

void startBuzz() {
  buzzTimes(3, 200);
}

void endBuzz() {
  buzzTimes(5, 200);
}

void correctBuzz() {
  buzzTimes(1, 500);
}

void incorrectBuzz() {
  buzzTimes(2, 500);
}

void buzzTimes(int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(duration);
    digitalWrite(buzzerPin, LOW);
    delay(duration);
  }
}

void generateSequence() {
  for (int i = 0; i < numLeds; i++) {
    ledSequence[i] = random(numLeds);
  }
}

void showSequence() {
  for (int i = 0; i < numLeds; i++) {
    pointToLED(ledSequence[i]);
    delay(1000);
  }
}

void pointToLED(int ledNumber) {
  int angle = map(ledNumber, 0, numLeds - 1, 0, 180);
  myServo.write(angle);
  digitalWrite(ledPins[ledNumber], HIGH);
  delay(500);
  digitalWrite(ledPins[ledNumber], LOW);
}

bool getPlayerInput() {
  int inputCount = 0;
  while (inputCount < numLeds) {
    if (irrecv.decode(&results)) {
      int ledNumber = convertIRToLEDNumber(results.value);
      irrecv.resume(); // Prepare for next IR input
      if (ledNumber != -1) {
        if (ledNumber == ledSequence[inputCount]) {
          buzzTimes(1, 100); // Buzz briefly for correct input
          inputCount++;
        } else {
          incorrectBuzz(); // Buzz twice for incorrect input and start over
          return false;
        }
      }
      delay(500); // Adding a delay for better IR signal handling
    }
  }
  return true; // All inputs were correct
}

int convertIRToLEDNumber(unsigned long irValue) {
  switch (irValue) {
    case 0xFF30CF: return 0; // Button 1
    case 0xFF18E7: return 1; // Button 2
    case 0xFF7A85: return 2; // Button 3
    case 0xFF10EF: return 3; // Button 4
    case 0xFF38C7: return 4; // Button 5
    default: return -1; // Invalid input
  }
}
