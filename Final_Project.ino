#include <IRremote.h>
#include "pitches.h"
const int buzzerPin = 7;
int ledPins[] = {8, 9, 10, 11, 12}; // LED pins
const int numberOfLeds = 5;
const int sensor = 2; // Audio sensor pin
boolean isEnabled = false; // To track if LED is on or off
const int RECV_PIN = 14; // IR receiver pin
IRrecv irrecv(RECV_PIN);
decode_results results;

int jingle_bells_melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int jingle_bells_tempo[]  = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};


// Melody for "We Wish You a Merry Christmas"
int wwyamc_melody[] = {
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

int  wwyamc_tempo[] = {
    4,
    4, 8, 8, 8, 8,
    4, 4, 4,
    4, 8, 8, 8, 8,
    4, 4, 4,
    4, 8, 8, 8, 8,
    4, 4, 8, 8,
    4, 4, 4,
    2
};


int santa_melody[] = {
    NOTE_G4,
    NOTE_E4,  NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
    NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
    NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
    NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
    NOTE_D4, NOTE_F4, NOTE_B3,
    NOTE_C4
};

int  santa_tempo[] = {
    8,
    8, 8, 4, 4, 4,
    8, 8, 4, 4, 4,
    8, 8, 4,  4, 4,
    8, 8, 4, 2,
    4, 4, 4, 4,
    4, 2, 4,
    1
};


void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensor, INPUT);
  for (int i = 0; i < numberOfLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(0)); // Initialize random seed
  irrecv.enableIRIn(); // Start the IR receiver
}


void loop() {
if (irrecv.decode(&results)) {
    if (results.value == 0xFFA25D)  { // Example IR code to disable IR response
     isEnabled = !isEnabled;
    }  
    if (isEnabled == 1) {
      switch (results.value) {
        case 0xFF30CF:
          sing(1);
          sing(1);
          break;
        case 0xFF18E7:
          sing(2);
          break;
        case 0xFF7A85:
          sing(3);
          sing(3);
        default:
          break;  
      }
    irrecv.resume(); // Receive the next value
  }
      }
    for (int i = 0; i < numberOfLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}


void ledControl() {
    int data = digitalRead(sensor);
    if (data == 1) {
        int ledToLight = random(0, numberOfLeds);
        for (int i = 0; i < numberOfLeds; i++) {
            digitalWrite(ledPins[i], LOW);
        }
        digitalWrite(ledPins[ledToLight], HIGH);
    } else {
        for (int i = 0; i < numberOfLeds; i++) {
            digitalWrite(ledPins[i], LOW);
        }
    }
}


void playRest() {
  tone(buzzerPin, REST, 1000); // Play the REST note for a duration
  delay(1000); // Wait for the duration
  noTone(buzzerPin); // Stop the tone
}


void sing(int s) {

  int song = s;
  if (song == 3) {
    int size = sizeof(wwyamc_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      // to calculate  the note duration, take one second
      // divided by the note type.
      //e.g.  quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration =  1000 / wwyamc_tempo[thisNote];
      buzz(buzzerPin, wwyamc_melody[thisNote],  noteDuration);
      ledControl();
      // to distinguish the notes, set a minimum time between  them.
      // the note's duration + 30% 
      int pauseBetweenNotes  = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the  tone playing:
      buzz(buzzerPin, 0, noteDuration);
      ledControl();
    }
  } else  if (song == 2) {
    int size = sizeof(santa_melody) / sizeof(int);
    for (int thisNote = 0;  thisNote < size; thisNote++) {
      int noteDuration = 900 / santa_tempo[thisNote];
      buzz(buzzerPin, santa_melody[thisNote], noteDuration);
      ledControl();
      // to  distinguish the notes, set a minimum time between them.
      // the note's duration  + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      buzz(buzzerPin,  0, noteDuration);
      ledControl();
    }
  } else {
    int size = sizeof(jingle_bells_melody) / sizeof(int);
    for (int thisNote  = 0; thisNote < size; thisNote++) {
      // to calculate the note duration,  take one second
      // divided by the note type.
      //e.g. quarter note  = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / jingle_bells_tempo[thisNote];
      buzz(buzzerPin, jingle_bells_melody[thisNote], noteDuration);
      ledControl();
      // to distinguish  the notes, set a minimum time between them.
      // the note's duration + 30%  seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      buzz(buzzerPin, 0, noteDuration);
      ledControl();
    }
  }
}
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate  the delay value between transitions
  //// 1 second's worth of microseconds,  divided by the frequency, then split in half since
  //// there are two phases  to each cycle
  long numCycles = frequency * length / 1000; // calculate the  number of cycles for proper timing
  //// multiply frequency, which is really  cycles per second, by the number of seconds to
  //// get the total number of  cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated  length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin  high to push out the diaphram
    delayMicroseconds(delayValue); // wait for  the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer  pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait  again or the calculated delay value
  }
  digitalWrite(13, LOW);

}
