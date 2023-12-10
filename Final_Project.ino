#include <IRremote.h>

const int buzzerPin = 7;
int ledPins[] = {9, 10, 11, 12, 13}; // LED pins
const int numberOfLeds = 5;
const int sensor = 2; // Audio sensor pin
boolean isEnabled = false; // To track if LED is on or off
const int RECV_PIN = 14; // IR receiver pin
IRrecv irrecv(RECV_PIN);
decode_results results;
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// Melody for "We Wish You a Merry Christmas"
int melodyWWYAMC[] = {
    NOTE_C5,4, //1
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
  NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
  NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
  NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,

  NOTE_F5,2, NOTE_C5,4, //8 
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
  NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
  NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
  NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
  NOTE_F5,2, NOTE_C5,4,

  NOTE_F5,4, NOTE_F5,4, NOTE_F5,4,//17
  NOTE_E5,2, NOTE_E5,4,
  NOTE_F5,4, NOTE_E5,4, NOTE_D5,4,
  NOTE_C5,2, NOTE_A5,4,
  NOTE_AS5,4, NOTE_A5,4, NOTE_G5,4,
  NOTE_C6,4, NOTE_C5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
  NOTE_F5,2, NOTE_C5,4, 
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
  
  NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, //27
  NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
  NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
  NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
  NOTE_F5,2, NOTE_C5,4,
  NOTE_F5,4, NOTE_F5,4, NOTE_F5,4,
  NOTE_E5,2, NOTE_E5,4,
  NOTE_F5,4, NOTE_E5,4, NOTE_D5,4,
  
  NOTE_C5,2, NOTE_A5,4,//36
  NOTE_AS5,4, NOTE_A5,4, NOTE_G5,4,
  NOTE_C6,4, NOTE_C5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
  NOTE_F5,2, NOTE_C5,4, 
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
  NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, 
  NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
  
  NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,//45
  NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
  NOTE_F5,2, NOTE_C5,4,
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
  NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
  
  NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, //53
  NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
  NOTE_F5,2, REST,4
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
    if (results.value == 0xFFA25D) { // Example IR code to disable IR response
      isEnabled = !isEnabled; // Toggle the IR response on/off
    }

    if (isEnabled) {
      switch (results.value) {
        case 0xFF30CF:
          playJingleBells();
          playJingleBells();
          break;
        case 0xFF18E7:
          playWeWishYouAMerryChristmas();
          break;
        // Add more cases for additional songs
      }
    }
    irrecv.resume(); // Receive the next value
  }
}

void playJingleBells() {
    char notes[] = "eee eee egcde fff ffee eeggfdc ";
    int beats[] = {2,2,3,1, 2,2,3,1, 2,2,3,1,4,4, 2,2,3,0, 1,2,2,2,0, 1,1,2,2,2,2,4,4};
    int tempo = 180;
    int songLength = sizeof(notes) - 1;
    playSong(notes, beats, songLength, tempo);
}

void playSong(char* notes, int* beats, int songLength, int tempo) {
  int duration;
  for (int i = 0; i < songLength; i++) {
    duration = beats[i] * tempo;
    if (notes[i] != ' ') {
      tone(buzzerPin, frequency(notes[i]), duration);
      ledControl(); // Call the function to control the LED
    }
    delay(duration);
    noTone(buzzerPin);
    ledControl(); // Call the function to control the LED again
    delay(tempo/10);
  }
}

void playWeWishYouAMerryChristmas() {
  int tempo = 140;
  int notesWWYAMC = sizeof(melodyWWYAMC) / sizeof(melodyWWYAMC[0]) / 2;
  int wholenoteWWYAMC = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;
    for (int thisNote = 0; thisNote < notesWWYAMC * 2; thisNote += 2) {
        divider = melodyWWYAMC[thisNote + 1];
        if (divider > 0) {
            noteDuration = wholenoteWWYAMC / divider;
        } else if (divider < 0) {
            noteDuration = wholenoteWWYAMC / abs(divider) * 1.5;
        }
        tone(buzzerPin, melodyWWYAMC[thisNote], noteDuration * 0.9);
        ledControl(); // Control the LED
        delay(noteDuration);
        noTone(buzzerPin);
        ledControl(); // Control the LED
        delay(100); // Short pause between notes
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
