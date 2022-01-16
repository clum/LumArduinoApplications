/* 
Move servo to set positions and interfacing with the HC-SR04 sensor.

Cora and Amara Lum

Version History
01/15/22: Created
*/

#include <Servo.h>

Servo myservo;
int PinServo = 9;

#include "LumHCSR04.h"

int PinHCS04Trigger   = 4;
int PinHCS04Echo      = 5;

void setup() {
  //Serial
  Serial.begin(9600);

  //Servo
  myservo.attach(PinServo);

  //HC-SR04
  pinMode(PinHCS04Trigger,OUTPUT);
  pinMode(PinHCS04Echo,INPUT);
}

void loop() {
  //HC-SR04
  int distance_cm = HCSR04GetDistance_cm(PinHCS04Trigger, PinHCS04Echo);

  Serial.println("distance_cm = "+(String)distance_cm);  
  
  //Servo  
  int pos = 10*distance_cm;
  myservo.write(pos);
  delay(100); 
}
