const int buzzerPin = 7;
const int ledPin = 12; // LED connected to digital pin 13
const int sensor = 2; // Audio sensor connected to digital pin 2
boolean is_on = false; //To determine/track if led is on or off

// Existing arrays for Jingle Bells song
char notes[] = "eee eee egcde fff ffee eeggfdc ";
int beats[] = {2,2,3,1, 2,2,3,1, 2,2,3,1,4,4, 2,2,3,0, 1,2,2,2,0, 1,1,2,2,2,2,4,4};
int tempo = 180;

int songLength = 31;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sensor, INPUT); // Set the audio sensor pin as an input
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
    if (is_on == true) { // If led is on then turn it off
      digitalWrite(ledPin, LOW);
      is_on = false;
    }
    else { // else if led is off then turn it on
      digitalWrite(ledPin, HIGH);
      is_on = true;
    }
}
}
