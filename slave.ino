/*
name: Bryan Chung
studentnummer: 0990458
*/




#include <Arduino.h>
#include <Wire.h>

int adress = 2;
int onvalueUp = LOW;
int onvalueDown = LOW; 
byte data[3];
int liftPosition = 0;
int OpenLift = 0;


int ledRed = 7;
int ledGreen = 8;

int latchPin = 11; // connect to the ST_CP of 74HC595 (pin 3,latch pin)
int clockPin = 9;  // connect to the SH_CP of 74HC595 (pin 4, clock pin)
int dataPin = 12;  // connect to the DS of 74HC595 (pin 2)
int digit = 0; // display the digit
int IRSensor = 2; // connect ir sensor to arduino pin 2
int ButtonUp = 3;
int ButtonDown = 5;
int LEDButtonUp = 4;
int LEDButtonDown = 6;

 // conect Led to arduino pin 13

byte sevenSegDigits[10] = { B01111011   ,  // = 0
                            B00001001   ,  // = 1
                            B10110011   ,  // = 2
                            B10011011   ,  // = 3
                            B11001001   ,  // = 4
                            B11011010   ,  // = 5
                            B11111000   ,  // = 6
                            B00001011   ,  // = 7
                            B11111011   ,  // = 8
                            B11001011      // = 9
                           };
byte sevenSegDP = B00000100;  // = DP

byte sevenSegAlpha[] = {  B11101011   , // = A
                          B11111000   , // = b
                          B01110010   , // = C
                          B10111001   , // = d
                          B11110010   , // = E
                          B11100010   , // = F
                          B11011011   , // = g
                          B11101000   , // = h
                          B01100000     // = I   
};
/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
bool bAddDecimalPoint = true;            // display state of show decimal point

/* ***********************************************************
 *                         Void setup                        *
 * ********************************************************* */
void setup() {
    // Set latchPin, clockPin, dataPin as output
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
     Wire.begin(adress);                // join i2c bus with address #0
     Wire.onRequest(requestEvent); // register event
     Wire.onReceive(getLiftRelatedData);
    pinMode (IRSensor, INPUT); // sensor pin INPUT
    pinMode(ButtonUp, INPUT);
    pinMode(ButtonDown, INPUT);
    pinMode(LEDButtonUp,OUTPUT);
    pinMode(LEDButtonDown,OUTPUT);
    pinMode(ledGreen,OUTPUT);
    pinMode(ledRed,OUTPUT);
    Serial.begin(9600);
   
}

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */ 
// display a alpha, binary value, or number on the digital segment display
void sevenSegWrite(byte digit, bool bDP = false, char switchValue='D') {
    /*       digit = array pointer or binary value, as a byte 
     *         bDP = true-include decimal point, as boolean
     * switchValue = 'A' alpha
     *               'B' binary
     *               'D' digits <default>, as char           */
    
    // set the latchPin to low potential, before sending data
    digitalWrite(latchPin, LOW);
     
    // the data (bit pattern)
    if (switchValue=='A'){
        // alpha
        shiftOut(dataPin, clockPin, MSBFIRST, sevenSegAlpha[digit]+(sevenSegDP*bDP)); 
    } else if (switchValue=='B'){
        // binary
        shiftOut(dataPin, clockPin, MSBFIRST, digit+(sevenSegDP*bDP));
    } else {
        // digits
        shiftOut(dataPin, clockPin, MSBFIRST, sevenSegDigits[digit]+(sevenSegDP*bDP));   
    }
 
    // set the latchPin to high potential, after sending data
    digitalWrite(latchPin, HIGH);
}

void sevenSegBlank(){
    // set the latchPin to low potential, before sending data
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);  
    // set the latchPin to high potential, after sending data
    digitalWrite(latchPin, HIGH);
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */


void loop() {
 


SensorState();
 
  onvalueUp = digitalRead(ButtonUp);
  onvalueDown = digitalRead(ButtonDown);
    int detection = digitalRead (IRSensor);

  
  if (onvalueUp == HIGH){

     ButtonState(1,0);
    digitalWrite(LEDButtonUp,HIGH);
    digitalWrite(LEDButtonDown,LOW);
    Serial.println("Off");

  }else if(onvalueDown == HIGH ){

     ButtonState(0,1);
     digitalWrite(LEDButtonUp,LOW);
     digitalWrite(LEDButtonDown,HIGH);
     Serial.println("On");

  }



  if(detection == LOW){
  
     digitalWrite(LEDButtonUp,LOW);
     digitalWrite(LEDButtonDown,LOW);
     digitalWrite(ledRed, HIGH );
     digitalWrite(ledGreen, LOW );
     
  }else  {

     
     digitalWrite(ledRed, LOW ); 
     digitalWrite(ledGreen, HIGH );
     
}





  

}

void requestEvent() {

  
  Wire.write(data,3); // respond with message of 6 bytes
  // as expected by master
}


void SensorState(){
  
  int detection = digitalRead (IRSensor);

 
  if (detection == 1){
    detection = 0;
    ButtonState(0,0);
     
  }
  
  else
  {
    
    detection = adress;
    ButtonState(2,2);
  }

  data[0] = detection;
  
  
}

void getLiftRelatedData() {
  // Get liftPosition and show it on LED display
  liftPosition = Wire.read(); // Receive byte containing current lift position
  OpenLift = Wire.read();
  Serial.println(liftPosition);
  Serial.println(OpenLift);
  displayLed(liftPosition);
  check(OpenLift);


  
}


void displayLed(int x){

sevenSegWrite(x,bAddDecimalPoint); // The number 9 will appear on the 7 segment
  
}

void check(int x){



  
}

void ButtonState(int x, int y){

 
  
  int stateUp,stateDown;
  int on = 1;
  int off = 0;

 if (x == 1 && y == 0){

  stateUp = 1;
  stateDown = 0;
  
 }

 if (x == 0 && y == 1){

    stateUp = 0;
    stateDown = 1;
  
 }

 if(x == 2 && y == 2){
  
    stateUp = 2;
    stateDown = 2;

 }

 
   data[1] = stateUp;
   data[2] = stateDown;

}

  


 






 
