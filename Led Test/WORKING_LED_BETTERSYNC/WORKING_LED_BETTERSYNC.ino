
#include <SoftwareSerial.h>


  //Pot Test Tweak

  
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

//For setting the state of the ball
int manualState = 1;

  //Pot Test Tweak


//data variable stores data read from serial. Initialized to 255 to signify that the user is initially not looking at the other ball 
int data = 255; 

const int led = 13; //LED output for testing

const int breakBeamPin = 2; //digital input from breakbeam IR receiver
const int strobePin = 3; //digital output to strobe


//digital inputs from IR receivers
const int optical_In1 = 7; 
const int optical_In2 = 8; 
const int optical_In3 = 9; 
const int RX = 10; 
const int TX = 12; 
//initialize software serial using pins 10,11 
SoftwareSerial mySerial(RX,TX); //RX, TX
/*** ASSIGNING PIN NUMBERS FOR ARDUINO I/O ***/

/*** ASSIGNING THRESHOLDS TO BE USED IN CODE ***/
unsigned long STROBEFLASHTIME = 10;  //sets strobe 'on' time
const int CANDIDATETHRESHOLD = 50;  //sets minimum duration of candidate pulse
/*** ASSIGNING THRESHOLDS TO BE USED IN CODE***/

/*** ASSIGNING STATE VARIABLES ***/
bool breakbeam = false; //whether breakbeam has triggered
bool looking = false;   //whether user is looking at ball
bool looking_remote = false; 
bool looking_local = false; 
bool lookingtemp = false; 
bool looking_change_local = true;  

//states of individual 'looking' detectors
bool optical_In1_state = false; 
bool optical_In2_state = false; 
bool optical_In3_state = false; 

/*** ASSIGNING STATE VARIABLES ***/

/*** ASSIGNING ADDITIONAL VARIABLES ***/
//these are accessed during interrupts
//they track timing of events using millis()
volatile unsigned long last_breakbeam_change = NULL;
volatile unsigned long now = NULL; 

//these track timing of events using millis()
unsigned long candidate_change = NULL;      //time index of candidate 'looking' event
  
unsigned long next = NULL;                  //time index of next scheduled strobe flash
unsigned long last_breakbeam = NULL;  //time index of last time the breakbeam triggered a strobe flash
unsigned long last_flash = NULL;            //time index of last time any strobe flash was triggered

//this is an estimate of the spinning ball's period
unsigned long global_period = NULL;

//this is the state the ball collapses to if the user is looking. It is randomized each time
int collapsed_state = 0; 
int collapsed_state_for_other_ball = 255; 

//N is the number of strobe states desired when not looking
int N = 8; 

//this ensures that an extra flash isn't scheduled when the ball returns close to the breakbeam position
int bonus_flash_counter = 0; 
/*** ASSIGNING ADDITIONAL VARIABLES ***/

//this is called once, to configure the arduino before it runs the main program
void setup() {
  /*** ASSIGNING PINMODES ***/
  pinMode(optical_In1, INPUT); 
  pinMode(optical_In2, INPUT); 
  pinMode(optical_In3, INPUT); 
  pinMode(breakBeamPin, INPUT); 
  pinMode(RX,INPUT); 
  pinMode(strobePin, OUTPUT); 
  pinMode(led, OUTPUT); 
  pinMode(TX,OUTPUT); 
  /*** ASSIGNING PINMODES ***/

  //preparing random number generator (used for choosing different collapsed states when user is looking)
  //Pot Test Tweak
  //randomSeed(analogRead(0));
  
  // Attaching interrupt to breakbeam pin so that 'breakBeamCheck' is triggered each time stick passes across beam. 
  // Note that stick is off center, so that only one side of stick breaks beam
  // (thus, the breakbeam should trigger only once per revolution)
  attachInterrupt(digitalPinToInterrupt(breakBeamPin), breakBeamCheck, RISING); // was 'CHANGE'

  // Assigning initial values to output pins 
  digitalWrite(strobePin, LOW);
  digitalWrite(led, LOW);

  //Serial is used for debugging. Not needed for final  code
  //Serial.begin(9600); 

  //begin mySerial, used for communication between two Arduinos
  //mySerial.begin(115200); 
  Serial.begin(9600);
  //while(! Serial); 
  //Serial.println("Here we go!"); 
}

//this is the main loop, which is called endlessly
void loop() {


    //Pot Test Tweak
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

    //Pot Test Tweak

    
  //assign 'now' to current time, for consistency across all functions 
  now = millis(); 

  //check if user is looking at the other ball 
  checkOtherBall(); 
  

  //if data == 255, this means that the user is not looking at the other ball, meaning we should go ahead
  //and check if they are looking at this ball
  if(data == 255){
      //function to check if the user is looking at the ball or not 
      //looking_remote = false;

      //Pot Test Tweak (Comment out lookingCheck - Add looking_local = true)
      //lookingCheck();

      //looking_local = false;
      //Smooths
      looking_local = false;
      //Sets All Ball Stobe States Individually
      setState(state);  
  }
  //the user is looking at the other ball, so assume the opposing collapsed state as transmitted via serial 
  else{
    looking_remote = true; 
    collapsed_state = data; 
  }
  looking = looking_local || looking_remote; 
 
  if(looking_change_local == true){
     sendData();
     looking_change_local = false; 
  }
   
 
   //function to schedule strobe flashes 
  flashScheduler(); 

  //function to trigger strobe flashes
  flash(); 
  
}

void sendData(){
  if(looking_local == true){
            //Pot Test Tweak
            collapsed_state = int(manualState); 

            //calculate the desired state of the other ball
            collapsed_state_for_other_ball = ((N / 2) + collapsed_state) % N; 

            //send over the state of the other ball
            //Serial.print("Sending: "); 
            //Serial.println(byte(collapsed_state_for_other_ball));
            mySerial.write(byte(collapsed_state_for_other_ball)); 
          // mySerial.write(byte(1)); 
  }
  else if(looking_local == false){
           //Serial.print("Sending"); 
           //Serial.println(byte(255)); 
            mySerial.write(byte(255));  
  }
}
/*******/
//the checkOtherBall() function receives the opposing ball position via software serial when the user is looking at the other ball
/*******/

void checkOtherBall(){
  if(mySerial.available()){
    data = mySerial.read(); 
    //Serial.print("reading data:"); 
    //Serial.println(data); 

    //Pot Test Tweak
    data = 255;
   }
}

/*******/
//The breakBeamCheck() function is triggered via an interrupt and sets the 'breakbeam' state variable 
/******/

void breakBeamCheck(){
  breakbeam = true; 
}


/*******/
//The lookingCheck() function is called by the main loop
//It reads the state of the 3 optical detectors and determines whether they indicate that the user is looking at the ball
//Note that lookingCheck() uses the CANDIDATETHRESHOLD value to filter out spurious signals
/******/


void lookingCheck(){
   //read the optical inputs
  optical_In1_state = digitalRead(optical_In1); 
  optical_In2_state = digitalRead(optical_In2); 
  optical_In3_state = digitalRead(optical_In3); 
 
  //perform logical OR of optical inputs, so that any one will trigger a change
  //note that the IR receiver outputs go low when a signal is present, so we invert each sensor's state to maintain the idea that 'true' = 'signal present'
  //also note that we only populate a temporary variable until the state change is verified as legitimate
   if(!optical_In1_state || !optical_In2_state || !optical_In3_state){ 
    lookingtemp = true;
  }
  else{
    lookingtemp = false; 
  }
  //if the looking state has changed
  if(lookingtemp != looking_local){
    //and if there isn't a candidate change we're waiting to evaluate
    if(!candidate_change){
          //record a new candidate change
          candidate_change = now; 
    }
   
    //if there is a candidate change already, and it it longer than the threshold
    if(((now - candidate_change) > CANDIDATETHRESHOLD)){
        //then there really is a change in looking state!
        //record the new time, and update looking state
        looking_change_local = true; 
        looking_local = lookingtemp;  
    }    
  }
  //either nothing new has happened, or there was a very fast change between sensor reads
  //in either case, there probably wasn't a legitimate signal, so reset the candidate change (start looking for a new one)
  else if(looking_local == lookingtemp){
    candidate_change = NULL; 
  }
}


/*******/
//The flashScheduler() function is called by the main loop
//It decides when the next strobe flash should happen, based on the breakbeam and 'looking' states
/******/
void flashScheduler(){
  //if the breakbeam is triggered, the next flash to schedule is /always/ 'now', whether or not the person is looking
  if(breakbeam){
          //if the breakbeam has flashed at least once before, then calculate the ball's period
          if(last_breakbeam){
                    global_period = now - last_breakbeam; 
          }
          //schedule a flash, update the last breakbeam flash time, and reset breakbeam state
         
          last_breakbeam = now;  
          breakbeam = false;

 
          if(!looking){
            next = now;  
          }
          else{
            next = now + global_period / N * collapsed_state; 
          }
             
          bonus_flash_counter = 0; 
  }
  //if breakbeam wasn't triggered, schedule 'superposition state' flashes, only if user isn't looking
  //also make sure there isn't a breakbeam flash about to happen, and that the ball's period has been determined
  else if((!looking) && global_period && (!next) && (bonus_flash_counter < (N-1))){
     next = last_flash + global_period / N;     //add flash corresponding to next of N superposition states
     bonus_flash_counter = bonus_flash_counter + 1; 
  }
 
}

/*******/
//The flash() function is called by the main loop
//It controls the 'on' time when the strobe is flashed, so that the lighting effect is consistent
//Note that it references STROBEFLASHTIME, which sets the minimum flash 'on' time
/******/
void flash(){
  //if a flash has been scheduled
  if(next){
        //and it's time for the strobe to be on
        if(now >= next){ 
          //turn the strobe on and update the last flash time
           
           last_flash = next;  
            
        }
       //or it's time for the strobe to be off (minimum 'on' time has elapsed)
        if(now >= (STROBEFLASHTIME + next)){
           //turn the strobe off, and clear 'next', which indicates no new flashes are scheduled
           //digitalWrite(strobePin, LOW);
           //digitalWrite(led, LOW);
           digitalWrite(strobePin, HIGH);
           digitalWrite(led, HIGH);
           delay(1);
           digitalWrite(strobePin, LOW);
           digitalWrite(led, LOW);
           next = NULL; 
        }  
  } 
}

//Pot Test Tweak

void setState(String AnalogState){
  if (AnalogState == "0000"){
    //Sets neutral state
    looking_local = false;
  } 
  if (AnalogState == "1000"){
    //0 State
    looking_local = true;
    //manualState = 0;
    collapsed_state = int(0); 
  }
  if (AnalogState == "0100"){
    //1 State
    looking_local = true;
    //manualState = 1;
    collapsed_state = int(1); 
  }
  if (AnalogState == "0010"){
    //2 State
    looking_local = true;
    //manualState = 2;
    collapsed_state = int(2); 
  }
  if (AnalogState == "0001"){
    //3 State
    looking_local = true;
    //manualState = 3;
    collapsed_state = int(3); 
  }
  if (AnalogState == "1100"){
    //4 State
    looking_local = true;
    //manualState = 4;
    collapsed_state = int(4); 
  }
  if (AnalogState == "0110"){
    //5 State
    looking_local = true;
    //manualState = 5;
    collapsed_state = int(5); 
  }
  if (AnalogState == "0011"){
    //6 State
    looking_local = true;
    //manualState = 6;
    collapsed_state = int(6); 
  }
  if (AnalogState == "1110"){
    //7 State
    looking_local = true;
    //manualState = 7;
    collapsed_state = int(7); 
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
//Pot Test Tweak
