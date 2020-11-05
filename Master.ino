#include <Wire.h>
#include <Keypad.h>
#include <Stepper.h>
int number;

int steps = 0;
boolean moveUp = false;   // Should the motor move clockwise
boolean moveDown = false; // Should the motor move counter-clockwise

boolean clockwise = true;
// Setup stepper
#define IN1 11
#define IN2 10
#define IN3 9
#define IN4 8

byte currentFloor = 0;
int CONNECTED_SLAVES = 5;

int goToFloor;

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
 
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

void loop() {

getAndSendDataToAllFloors();
 
KeypadFunction();

Serial.println("THE CURRENT FLOOR IS");
 Serial.println(currentFloor);  

 Serial.println("THE GO TO FLOOR IS");
 Serial.println(goToFloor);  



 if (goToFloor > currentFloor) {
    Serial.println("lift gaat omhoog");
    moveUp = true;                      
    moveDown = false;     //lift moving up
  }
  if (goToFloor < currentFloor) {
    Serial.println("lift gaat omlaag");
    moveUp = false;
    moveDown = true;      //lift moving down
  }
  if (goToFloor == currentFloor) {
    Serial.println("lift is op bestemming");

    moveUp = false;
    moveDown = false;
  }

  moveLift();
  

}


 void getAndSendDataToAllFloors() {
  
  for (int i = 1; i <= CONNECTED_SLAVES; i++) { 
    getButtonPressedOfFloor(i); 
    sendLiftRelatedData(i);
   
  }
}

  void getButtonPressedOfFloor(int floorCount){
  
  Wire.requestFrom(floorCount,2);

  int number = Wire.read();
  int ButtonState = Wire.read();
  
  
    
   Serial.println(number);
   Serial.println("BUTON UP IS");
   Serial.println(ButtonState);
   
  LiftLocation(number); 
  moveLift(ButtonState);


  
 }


 void moveLift(int x){




if ( x == 1 || x == 6){

  goToFloor = 0;


  
}


if ( x == 2 || x == 7){

  goToFloor = 1;


  
}


if ( x == 3 || x == 8){

  goToFloor = 2;


  
}


if ( x == 4 || x == 9){

  goToFloor = 3;


  
}



if ( x == 5 || x == 10){

  goToFloor = 4;


  
}






  
 }

  

  void sendLiftRelatedData(int floorCount){
    

  Wire.beginTransmission(floorCount);               
  Wire.write(currentFloor);                                        
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
  


  void KeypadFunction(){

char key = keypad.getKey();

  if (key == '0'){

   
    goToFloor = 0;

   

  }

  if (key == '1'){
     
      
      goToFloor = 1;

    

  }
    if (key == '2'){



     goToFloor = 2;

   

  } 
  
  if (key == '3'){


    goToFloor = 3;

   

  }
    if (key == '4'){


   goToFloor = 4;

   

  }

  }



void moveLift() {
  // Controls the lift controller
  if (moveUp) {
    Serial.println("going up");
    liftController(true);
  } else if (moveDown) {
    Serial.println("going down");
    liftController(false);
  }
}



void liftController(boolean up) {
  // Controls how many the stepping motor should rotate
  clockwise = !up;


  for (int i = 0; i < 1000; i++) { // remove or increase when needed,
    // with this for loop the motor moves more between requests.
    stepper();
    delayMicroseconds(2000);
  }
}

void stepper() {
  // controls the steppenmotor
  switch (steps) {
    case 0:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
    case 3:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
  }

  if (clockwise) {
    steps++;
  } else {
    steps--;
  }

  if (steps > 3) {
    steps = 0;
  } else if (steps < 0) {
    steps = 3;
  }
}



  

  
