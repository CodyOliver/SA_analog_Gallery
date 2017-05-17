int potPin = 2;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor

long randNumber;

bool trig = false;

void setup() {
  Serial.begin(9600);
  //Pins for position indication
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  //Pins for communication
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  //Pins for data
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);

}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor
  //Serial.println(val);
  delay(100);
  
  //This is left
  if (val >= 0 && val <=330){
    //Indicator LEDS for position
     digitalWrite(13, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(11, LOW);
     //Generate random number 1-8
     getRandomSequence();
  } 
  //This is center
  else if (val >= 330 && val <=610){
    //Indicator LEDS for position
     digitalWrite(13, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(11, LOW);
     neutralState();
     trig = false;
  } 
  //This is right
  else if (val >= 610 && val <=1023){
    //Indicator LEDS for position
     digitalWrite(13, LOW);
     digitalWrite(12, LOW);
     digitalWrite(11, HIGH);
     //Generate random number 1-8
     getRandomSequence();
  } 
}
  void getRandomSequence(){
    if (trig == false){
    // print a random number from 1 to 8
    randNumber = random(1, 9);
    Serial.println(randNumber);
    //Send communication
    createOutputCommunication(randNumber);
    //Stop sequence from running more than once
    trig = true;
    }
    
  }

  void neutralState(){
       digitalWrite(7, LOW);
       digitalWrite(6, LOW);
       digitalWrite(5, LOW);
       digitalWrite(4, LOW);

       //Data representation
       digitalWrite(10, LOW);
       digitalWrite(9, LOW);
       digitalWrite(8, LOW);
       digitalWrite(2, LOW);
  }
  
  void createOutputCommunication(int randomNumber){
    if (randomNumber == 1){
       digitalWrite(7, HIGH);
       digitalWrite(6, LOW);
       digitalWrite(5, LOW);
       digitalWrite(4, LOW);

       //Data representation
       digitalWrite(10, HIGH);
       digitalWrite(9, LOW);
       digitalWrite(8, LOW);
       digitalWrite(2, LOW);
    }
    if (randomNumber == 2){
       digitalWrite(7, LOW);
       digitalWrite(6, HIGH);
       digitalWrite(5, LOW);
       digitalWrite(4, LOW);

       //Data representation
       digitalWrite(10, LOW);
       digitalWrite(9, HIGH);
       digitalWrite(8, LOW);
       digitalWrite(2, LOW);
    }
    if (randomNumber == 3){
       digitalWrite(7, LOW);
       digitalWrite(6, LOW);
       digitalWrite(5, HIGH);
       digitalWrite(4, LOW);

       //Data representation
       digitalWrite(10, LOW);
       digitalWrite(9, LOW);
       digitalWrite(8, HIGH);
       digitalWrite(2, LOW);
    }
    if (randomNumber == 4){
       digitalWrite(7, LOW);
       digitalWrite(6, LOW);
       digitalWrite(5, LOW);
       digitalWrite(4, HIGH);

       //Data representation
       digitalWrite(10, LOW);
       digitalWrite(9, LOW);
       digitalWrite(8, LOW);
       digitalWrite(2, HIGH);
    }
    if (randomNumber == 5){
       digitalWrite(7, HIGH);
       digitalWrite(6, HIGH);
       digitalWrite(5, LOW);
       digitalWrite(4, LOW);

       //Data representation
       digitalWrite(10, HIGH);
       digitalWrite(9, HIGH);
       digitalWrite(8, LOW);
       digitalWrite(2, LOW);
    }
    if (randomNumber == 6){
       digitalWrite(7, LOW);
       digitalWrite(6, HIGH);
       digitalWrite(5, HIGH);
       digitalWrite(4, LOW);

       //Data representation
       digitalWrite(10, LOW);
       digitalWrite(9, HIGH);
       digitalWrite(8, HIGH);
       digitalWrite(2, LOW);
    }
    if (randomNumber == 7){
       digitalWrite(7, LOW);
       digitalWrite(6, LOW);
       digitalWrite(5, HIGH);
       digitalWrite(4, HIGH);

       //Data representation
       digitalWrite(10, LOW);
       digitalWrite(9, LOW);
       digitalWrite(8, HIGH);
       digitalWrite(2, HIGH);
    }
    if (randomNumber == 8){
       digitalWrite(7, HIGH);
       digitalWrite(6, HIGH);
       digitalWrite(5, HIGH);
       digitalWrite(4, LOW);

       //Data representation
       digitalWrite(10, HIGH);
       digitalWrite(9, HIGH);
       digitalWrite(8, HIGH);
       digitalWrite(2, LOW);
    }
  }

 
