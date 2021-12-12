/* 
 Use a servo to act as a voltage level indicator.

 Christopher Lum
 lum@uw.edu
 
 Version History
 10/20/21: Created
 10/21/21: Updated
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  //------------
  //Serial setup  
  //------------
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //------------
  //Servo setup
  //------------
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  //start at 0
  pos = 0;
  myservo.write(pos);
  delay(1000);
  
  //do a single 180 deg and back motion to indicate startup
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 5ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 5ms for the servo to reach the position
  }

  //return to midpoint to await reading
  pos = 90;
  myservo.write(pos); 
  delay(1000);   
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float maxVoltage = 3.3;   //3.3V for Due
  float analogInResolution = 1023;
  float voltage = sensorValue*(maxVoltage/analogInResolution);
  Serial.println(voltage);
  
  //convert voltage to a servo position
  float position = 180*(voltage/1.75);
  int positionInt = (int)position;
  myservo.write(positionInt);
  
  delay(500);
}
