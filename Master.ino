#include <Wire.h>

byte currentFloor = 0;
int CONNECTED_SLAVES = 2;


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);// start serial for output
  pinMode(13,OUTPUT);
}

void loop() {

 
getAndSendDataToAllFloors();
  
  

}


 void getAndSendDataToAllFloors() {
  
  for (int i = 0; i < CONNECTED_SLAVES; i++) { 
    getButtonPressedOfFloor(i); 
    sendLiftRelatedData(i);
   
  }
}

  void getButtonPressedOfFloor(int floorCount){
  
  Wire.requestFrom(floorCount,1);

  int number = Wire.read();

    Serial.println(number);

 if ( number == 1){

       currentFloor = 1;
   
  
 }
 
 if( number == 2){
     
     currentFloor = 2;

  
 }

  }

  void sendLiftRelatedData(int floorCount){
    

  Wire.beginTransmission(floorCount);               
  Wire.write(currentFloor);                                        
  Wire.endTransmission();                  
 

  }
