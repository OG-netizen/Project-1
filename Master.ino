#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);// start serial for output
  pinMode(13,OUTPUT);
}

void loop() {

 
  Wire.beginTransmission(8);
  Wire.write(0);

  Wire.endTransmission();

  Wire.requestFrom(8,1);

  while(Wire.available()==0);
  int number = Wire.read();

    Serial.println(number);

    if (number == 1){

      digitalWrite(13,HIGH);
    }else{
      digitalWrite(13,LOW);
    }
  
  

}
