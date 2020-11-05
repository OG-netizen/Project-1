#include <Wire.h>
#include <Keypad.h>
#include <Stepper.h>
#define STEPS 32

 int stepsPerRevolution = 10000; 
Stepper stepper(STEPS, 8, 10, 9, 11);

byte currentFloor = 0;
int CONNECTED_SLAVES = 5;
int val = 0;

int DoorNumber;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {38, 40, 42, 44}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {46, 48, 50, 52}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);// start serial for output
  pinMode(13,OUTPUT);
    stepper.setSpeed(1000);

}

void loop() {

 
getAndSendDataToAllFloors();
KeypadFunction();  
  

}


 void getAndSendDataToAllFloors() {
  
  for (int i = 1; i <= CONNECTED_SLAVES; i++) { 
    getButtonPressedOfFloor(i); 
    sendLiftRelatedData(i);
   
  }
}

  void getButtonPressedOfFloor(int floorCount){
  
  Wire.requestFrom(floorCount,3);

  int number = Wire.read();
  int ButtonUp = Wire.read();
  int ButtonDown = Wire.read();
  
    
   Serial.println(number);

     Serial.println(ButtonUp);
  Serial.println(ButtonDown);
  LiftLocation(number); 
 moveLift(ButtonUp, ButtonDown);


  
 }


 void moveLift(int x, int y){


if (x == 0 && y == 1){
    stepper.step(10000);
  
}

if (x == 2 && y == 2){
   
   
      stepper.step(0);

  
}
  
 }

  

  void sendLiftRelatedData(int floorCount){
    

  Wire.beginTransmission(floorCount);               
  Wire.write(currentFloor);
  Wire.write(DoorNumber);                                        
  Wire.endTransmission();                  
 

  }





  void LiftLocation( int x){

 if ( x == 1){

     currentFloor = 0;
  
 }
 
 if( x == 2){
     
     currentFloor = 1;

  
 }if( x == 3){

     currentFloor = 2;

  
 }if( x == 4){

     currentFloor = 3;

  
 }if( x == 5){

     currentFloor = 4;

  
 }
  }
 void openDoor(int x){

  if (x == 1){
   
    DoorNumber = 1;
    
  }  if (x == 2){

    DoorNumber = 2;
   
  }
   if (x == 3){

    DoorNumber = 3;
    
  }  if (x == 4){

    DoorNumber = 4;
    
  }
   if (x == 5){

    DoorNumber = 5;
    
  }


 }

  void KeypadFunction(){

char key = keypad.getKey();

  if (key == '0'){

     
  stepper.step(-10000); 
   
    openDoor(1);

  }

  if (key == '1'){
  
    openDoor(2);

  }
    if (key == '2'){
   
    openDoor(3);

  } 
  
  if (key == '3'){
  
    openDoor(4);

  }
    if (key == '4'){
 
    openDoor(5);

  }


    
  }

  
