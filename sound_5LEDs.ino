const int buzzerPin = 7;
int ledPins[] = {9,10,11,12,13}; // LED connected to digital pin 13
const int sensor = 2; // Audio sensor connected to digital pin 2
boolean is_on = false; //To determine/track if led is on or off
const int numberOfLeds = 5;
// Existing arrays for Jingle Bells song
char notes[] = "eee eee egcde fff ffee eeggfdc ";
int beats[] = {2,2,3,1, 2,2,3,1, 2,2,3,1,4,4, 2,2,3,0, 1,2,2,2,0, 1,1,2,2,2,2,4,4};
int tempo = 100;

int songLength = 31;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensor, INPUT); // Set the audio sensor pin as an input
  for(int i=0; i<5;i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(0)); // Initialize random seed only once
}

void loop() {
  int duration;
 
  for (int i = 0; i < songLength; i++) {
    duration = beats[i] * tempo;
    
    if (notes[i] == ' ') {
      delay(duration);
    } else {
      tone(buzzerPin, frequency(notes[i]), duration);
      ledControl(); // Call the function to control the LED
      delay(duration);
    }
    noTone(buzzerPin);
    ledControl(); // Call the function to control the LED
    delay(tempo/10);
}
}
int frequency(char note) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
  
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      return(frequencies[i]);
    }
  }
  return(0);
}

void ledControl() {
  int data = digitalRead(sensor);
if (data == 1) { // 1 is sent from sensor when loud noise is detected
    int ledToLight = random(0, numberOfLeds); 

    // Turn off all LEDs
    for (int i = 0; i < numberOfLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }

    digitalWrite(ledPins[ledToLight], HIGH);
    digitalWrite(ledPins[ledToLight+1], HIGH);
    }
    else 
    { // else if led is off then turn it on
      for (int i = 0; i < numberOfLeds; i++) 
      {
        digitalWrite(ledPins[i], LOW);
      }
    }
      delay(100); 
}
