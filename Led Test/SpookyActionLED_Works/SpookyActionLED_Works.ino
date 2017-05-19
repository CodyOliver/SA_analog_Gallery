/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

const int breakBeamPin = 2; //digital input from breakbeam IR receiver

int stateNum = 0;

void setup() {
    // initialize serial communications at 9600 bps:
    pinMode(3, OUTPUT);
    pinMode(13, OUTPUT);
pinMode(breakBeamPin, INPUT);
Serial.begin(9600);
}

void loop() {
 attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);

 
}

void breakBeamCheck(){
  if (stateNum == 0){
    neutralState();
  }
  if (stateNum == 1){
    stateOne();
  }
  if (stateNum == 2){
    stateTwo();
  }
}

void neutralState(){
  flash();
  delay(1500);
  flash();
  delay(1500);
  flash();
  delay(1500);
  flash();
  delay(1500);
  flash();
  delay(1500);
  flash();
  delay(1500);
  flash();
  delay(1200);
  flash();
}

void stateOne(){
  flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1200);
  //flash();
}
void stateTwo(){
  //flash();
  delay(1500);
  flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1200);
  //flash();
}

void flash(){
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(1);              // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)

  delay(1);              // wait for a second
}

