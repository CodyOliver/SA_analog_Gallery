
// Analog input pin that the potentiometer is attached to
const int analogInPin0 = A0;
const int analogInPin1 = A1;
const int analogInPin2 = A2;
const int analogInPin3 = A3;

int A0Read;
int A1Read;
int A2Read;
int A3Read;

String state;

int stateNum = 0;


const int breakBeamPin = 2; //digital input from breakbeam IR receiver
const int strobePin = 3; //digital output to strobe


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(breakBeamPin, INPUT);
  pinMode(3, OUTPUT);
  
}

void loop() {
  // read the analog in value:
  A0Read = analogRead(analogInPin0);
  A0Read = pinCheck(A0Read);
  
  A1Read = analogRead(analogInPin1);
  A1Read = pinCheck(A1Read);
  
  A2Read = analogRead(analogInPin2);
  A2Read = pinCheck(A2Read);
  
  A3Read = analogRead(analogInPin3);
  A3Read = pinCheck(A3Read);
  
  //Serial.println("Pins = " + String(A0Read) + String(A1Read) + String(A2Read) + String(A3Read));

  String state = String(A0Read)+String(A1Read)+String(A2Read)+String(A3Read);
  Serial.println(state);

  //Create visual representation of data
  setState(state);
  
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  //delay(2);
}

void setState(String AnalogState){
  if (AnalogState == "0000"){
    stateNum = 0;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  } 
  if (AnalogState == "1000"){
    stateNum = 1;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  }
  if (AnalogState == "0100"){
    stateNum = 2;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  }
  if (AnalogState == "0010"){
    stateNum = 3;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  }
  if (AnalogState == "0001"){
    stateNum = 4;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  }
  if (AnalogState == "1100"){
    stateNum = 5;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  }
  if (AnalogState == "0110"){
    stateNum = 6;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  }
  if (AnalogState == "0011"){
    stateNum = 7;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  }
  if (AnalogState == "1110"){
    stateNum = 8;
    attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING);
  }
  if (AnalogState == "1111"){
    stateNum = stateNum;
  }
}

//Checks if pin is high above threshold of 100
int pinCheck(int aRead){
  if (aRead > 100){
    aRead = 1;
  } else {
    aRead = 0;
  }
  return aRead;
}

void flash(){
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(1);              // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW

  delay(1);              // wait for a second
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

void stateThree(){
  //flash();
  delay(1500);
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
  delay(1200);
  //flash();
}

void stateFour(){
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1200);
  //flash();
}

void stateFive(){
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1500);
  flash();
  delay(1500);
  //flash();
  delay(1500);
  //flash();
  delay(1200);
  //flash();
}

void stateSix(){
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
  flash();
  delay(1500);
  //flash();
  delay(1200);
  //flash();
}

void stateSeven(){
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
  delay(1500);
  flash();
  delay(1200);
  //flash();
}

void stateEight(){
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
  delay(1500);
  //flash();
  delay(1200);
  flash();
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
  if (stateNum == 3){
    stateThree();
  }
  if (stateNum == 4){
    stateFour();
  }
  if (stateNum == 5){
    stateFive();
  }
  if (stateNum == 6){
    stateSix();
  }
  if (stateNum == 7){
    stateSeven();
  }
  if (stateNum == 8){
    stateEight();
  }
}
