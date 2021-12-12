/*
Interface with a motors of bi wheeled car via the DRV8833 motor driver

Christopher Lum and Amara Lum and Cora Lum
slowest motor turns = 100

Version History
11/03/21: created
11/09/21: updated
11/11/21: slowing down motors
11/13/21: deconflicting interrupt pins
*/

//Constants
int PinSLP    = 4;
int PinFLT    = 5;

int PinAIN1   = 6;
int PinAIN2   = 7;
int PinBIN1   = 10;
int PinBIN2   = 11;

void setup() {
  //Serial
  Serial.begin(9600);

  //Pins
  pinMode(PinSLP,OUTPUT);
  pinMode(PinFLT,INPUT);
  pinMode(PinAIN1,OUTPUT);
  pinMode(PinAIN2,OUTPUT);
  pinMode(PinBIN1,OUTPUT);
  pinMode(PinBIN2,OUTPUT);
  delay(1000);
}

void loop() {
  //User selections
  int delayTime_ms = 2000;

  //enable DRV8833 chip
  Serial.println("Enabling DRV8833");
  digitalWrite(PinSLP,HIGH);
  
  Performance01();
  goSquare();
  
  Serial.println("");
}

void Performance01() {
  int turnTime_ms = 500;
  
  goForward();
  stopCar();
  goBackward();
  stopCar();
  turnRight(turnTime_ms);
  stopCar();
  turnLeft(turnTime_ms);
  stopCar();
}

void goSquare() {
  int turnTime_ms = 700;
  
  goForward();
  stopCar();
  turnRight(turnTime_ms);
  stopCar();
  goForward();
  stopCar();
  turnRight(turnTime_ms);
  stopCar();
  goForward();
  stopCar();
  turnRight(turnTime_ms);
  stopCar();
  goForward();
  stopCar();
  turnRight(turnTime_ms);
  stopCar();
}

//This makes the car go forward and slowly accelerates the velocity.
void accelerateForward() {
  Serial.println("Spin forward");
  digitalWrite(PinAIN1,LOW); 
  analogWrite(PinAIN2,115);
  digitalWrite(PinBIN1,LOW); 
  analogWrite(PinBIN2,115);
  delay(1000);

  digitalWrite(PinAIN1,LOW); 
  analogWrite(PinAIN2,170);
  digitalWrite(PinBIN1,LOW); 
  analogWrite(PinBIN2,170);
  delay(1000);

  digitalWrite(PinAIN1,LOW);
  analogWrite(PinAIN2,255);
  digitalWrite(PinBIN1,LOW); 
  analogWrite(PinBIN2,255);
  delay(1000); 
}

void stopCar() {
 Serial.println("Stop");
  digitalWrite(PinAIN1,LOW); 
  digitalWrite(PinAIN2,LOW);
  digitalWrite(PinBIN1,LOW);
  digitalWrite(PinBIN2,LOW);
  delay(1000);
}

void accelerateBackward() {
  Serial.println("Spin backward");
  analogWrite(PinAIN1,115); 
  digitalWrite(PinAIN2,LOW);
  analogWrite(PinBIN1,115); 
  digitalWrite(PinBIN2,LOW);
  delay(1000);

  analogWrite(PinAIN1,170); 
  digitalWrite(PinAIN2,LOW);
  analogWrite(PinBIN1,170); 
  digitalWrite(PinBIN2,LOW);
  delay(1000);

  analogWrite(PinAIN1,255); 
  digitalWrite(PinAIN2,LOW);
  analogWrite(PinBIN1,255); 
  digitalWrite(PinBIN2,LOW);
  delay(1000); 
}

//This makes the car turn right
void turnRight(int T) {
  Serial.println("turn right");
  analogWrite(PinAIN1,0); 
  analogWrite(PinAIN2,150);
  analogWrite(PinBIN1,0); 
  analogWrite(PinBIN2,0);
  delay(T);
}

//This makes the car turn left
void turnLeft(int T) {
  Serial.println("turn left");
  analogWrite(PinAIN1,0); 
  analogWrite(PinAIN2,0);
  analogWrite(PinBIN1,0); 
  analogWrite(PinBIN2,150);
  delay(T);
}

void goForward() {
  Serial.println("Spin forward");
  analogWrite(PinAIN1,0);
  analogWrite(PinAIN2,150);
  analogWrite(PinBIN1,0); 
  analogWrite(PinBIN2,150);
  delay(1000); 
}

void goBackward() {
  Serial.println("Spin backward");
  analogWrite(PinAIN1,150); 
  analogWrite(PinAIN2,0);
  analogWrite(PinBIN1,150); 
  analogWrite(PinBIN2,0);
  delay(1000); 
}
