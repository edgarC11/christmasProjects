12/17/23
Today we are going to use a sound sensor, an active buzzer and an IR Remote Controller to select songs and sync music with LEDs to create a Christmas themed project.

In the first project we are going to use the sound sensor to control LEDs with sound.
Note: important to calibrate the sound sensor with the potentiometer.

In the second project, we are going to build on the previous project. We are going to play a Christmas song with the active buzzer and sync the LEDs with the sound using the sound sensor.

In the third project, we are going to use the IR Remote Controller to turn on specific LEDs by pressing certain keys on the controller.

In the final stage, we are going to choose the songs that play on the buzzer and create a light show.
Note: Must modify IRremote library in the Arduino libraries folder:

in the IRremoteInt.h file, in

// Arduino Mega
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  //define IR_USE_TIMER1   // tx = pin 11
  #define IR_USE_TIMER2     // tx = pin 9     <- Comment out
  //#define IR_USE_TIMER3   // tx = pin 5
  //#define IR_USE_TIMER4   // tx = pin 6
  //#define IR_USE_TIMER5   // tx = pin 46





for the servo_LED game,

In the Servo.h file, in
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define _useTimer5
#define _useTimer1       <- modify to 2
#define _useTimer3          
#define _useTimer4
