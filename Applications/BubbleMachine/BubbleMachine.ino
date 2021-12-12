/* Run the bubble machine
 *  Created by Amara and Cora

10/24/21: created
11/02/2021 motor only spins when wand is in front of it- and working!
*/

#include <Servo.h>

int PinSERVO  = 9;
int PinAIN1   = 5;
int PinAIN2   = 6;
int PinSLP    = 2;
int delayTime_ms = 2000;

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  //Serial
  Serial.begin(9600);
  
  myservo.attach(PinSERVO);  // attaches the servo on pin 9 to the servo object
  pinMode(PinSLP,OUTPUT); // pin sending out
  pinMode(PinAIN1,OUTPUT);
  pinMode(PinAIN2,OUTPUT);
}

void loop() {
  Serial.println("Move servo to motor");
  for (pos = 120; pos >= 35; pos -= 1) {
    myservo.write(pos);
    delay(30);
  }
  
  //enable DRV8833 chip
  Serial.println("Enabling DRV8833");
  digitalWrite(PinSLP,HIGH);// turns on motor driver
  
  //Spin motor to blow bubbles
  Serial.println("Spin motor forward");
  digitalWrite(PinAIN1,HIGH); 
  digitalWrite(PinAIN2,LOW);
  delay(delayTime_ms);
  
  digitalWrite(PinAIN1,LOW); 
  digitalWrite(PinAIN2,LOW);
  
  for (pos = 35; pos <= 120; pos += 1) {
    // in steps of 1 degree
    myservo.write(pos);
    delay(30);
  }
     
  delay(1000);      
}
