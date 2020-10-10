
#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}



byte data[1];
void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {

  data[0] = 1;

  
  Wire.write(data,1); // respond with message of 6 bytes
  // as expected by master
}
