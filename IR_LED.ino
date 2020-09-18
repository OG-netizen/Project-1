int LEDState=LOW;
int LEDPin=8;
int buttonPin=9;
int IRSensor = 7;
int detection = HIGH;// no obstacle
int buttonState = LOW;

int offbutton = 5;
int onvalue = 0;
int offvalue = 0;

int led =13;


 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 
pinMode(LEDPin, OUTPUT);
pinMode(buttonPin, INPUT);
pinMode (IRSensor, INPUT);
 
}
 
void loop() {


  onvalue = digitalRead(buttonPin);

  if ( onvalue == LOW){
    digitalWrite(LEDPin, HIGH);
  }

  detection = digitalRead(IRSensor);

  if ( detection == LOW){
    digitalWrite(LEDPin, LOW);
     Serial.print("There is an obstacle!\n");
  }else{ 
    Serial.print("No obstacle!\n");
        

  }



 
  



 
}
 
