#include <Wire.h>
int IRSensor = 2; 
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

  pinMode (IRSensor, INPUT);
  
}



byte data[1];

void loop() {
int statusSensor = digitalRead (IRSensor);
  if (statusSensor == 1){
    statusSensor = 0;
  }
  
  else
  {
    statusSensor = 1;
  }

  data[0] = statusSensor;
  

  
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {

  
  Wire.write(data,1); // respond with message of 6 bytes
  // as expected by master
}
