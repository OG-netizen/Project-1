
#include <Wire.h>


int LED = 5;

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(LED,OUTPUT);
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(0);
  Wire.endTransmission(); 
  Wire.requestFrom(4, 1);


  while(Wire.available() == 0);
  
  int IRpin= Wire.read();

  if (IRpin == 1){
    digitalWrite(LED,HIGH);   
  }else{
    digitalWrite(LED,LOW);
  }

  
}
