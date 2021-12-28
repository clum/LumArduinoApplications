/* 
Move servo to set positions

Cora and Amara Lum

Version History
12/03/2021 Created
12/27/2021 edited
*/

#include <Servo.h>

Servo myservo;
int PinServo = 9;

void setup() {
  myservo.attach(PinServo);
}

void loop() {
  int pos = 0;
  myservo.write(pos);
  delay(3000);
  pos = 180;   //in range of [0,180]
  myservo.write(pos); 
  delay(3000); 
}
