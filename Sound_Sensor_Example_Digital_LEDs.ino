int ledPins[] = {9, 10, 11, 12, 13}; 
int numberOfLeds = 5;
int soundsensor = 2;

void setup() { 
  pinMode(soundsensor, INPUT);
  for (int i = 0; i < numberOfLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(0)); // Initialize random seed only once
}

void loop() {
  int sensorvalue = digitalRead(soundsensor);

  if (sensorvalue == HIGH) { 
    int ledToLight = random(0, numberOfLeds); 

    // Turn off all LEDs
    for (int i = 0; i < numberOfLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }

    digitalWrite(ledPins[ledToLight], HIGH);
    digitalWrite(ledPins[ledToLight+1], HIGH); 
  } else {
    for (int i = 0; i < numberOfLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
      delay(100); 
}