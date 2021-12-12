/*
Activate a servo as part of a Lego system.

Christopher Lum
lum@uw.edu

Version History
10/28/21: created
*/

#include <Servo.h>

//Servo
Servo myservo;
int PinServo = 9;

//Joystick
int PinX    = A0;
int PinY    = A1;
int PinS    = 7;

//LED
int PinLEDRed   = 2;
int PinLEDGreen = 3;
int PinLEDBlue  = 4;

void setup() {
  //Serial
  Serial.begin(9600);

  //Servo
  myservo.attach(PinServo);
  
  //Pins: /Joystick
  pinMode(PinX,INPUT);
  pinMode(PinY,INPUT);
  pinMode(PinS,INPUT);

  //instead of using a pullup resistor, write PinS to HIGH to leverage internal pullup resistor (see https://youtu.be/B6YEQj4d5WU?t=784)
  digitalWrite(PinS,HIGH);   
  
  //Pins: LED
  pinMode(PinLEDRed, OUTPUT);
  pinMode(PinLEDGreen, OUTPUT);
  pinMode(PinLEDBlue, OUTPUT);
}

void loop() {
  //Read joystick values
  int Xval = analogRead(PinX);
  int Yval = analogRead(PinY);
  bool Sval = digitalRead(PinS);

  //map joystick values servo position
  int servoPosition = map(Yval,0,1024,0,180);
  myservo.write(servoPosition);
    
  //print values
  Serial.println("(X,Y) = (" + (String)Xval + "," + (String)Yval + "), servoPosition = " + (String)servoPosition);  
  
  delay(100);
}
