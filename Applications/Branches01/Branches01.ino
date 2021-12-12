/* 
Move servo to a set/constant position

Cora and Amara Lum

Version History
12/03/2021 Created
*/

#include <Servo.h>

Servo myservo;
int PinServo = 9;

void setup() {
  myservo.attach(PinServo);
}

void loop() {
  int pos = 90;
  myservo.write(pos);
  delay(3000);
  pos = 160;   //in range of [0,180]
  myservo.write(pos); 
  delay(3000); 
}
