/*
Add contingency handling for car using simple polling

Christopher Lum and Amara Lum and Cora Lum
slowest motor turns = 100

Version History
11/14/21: created
11/24/21: Changed PinBIN1 to 11 so we do not use pin 10 which might be disabled by Servo library
*/

//Constants
int PinSLP    = 4;
int PinFLT    = 5;

int PinAIN1   = 6;
int PinAIN2   = 7;
int PinBIN1   = 11;
int PinBIN2   = 12;

//contingency
int PinSwitch01 = 2;
int state = 1;    //1 = nominal, 2 = contingency
int turnTime_ms = 500;

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
  pinMode(PinSwitch01,INPUT_PULLUP);
  
  //allow time to switch on car and extract hand
  delay(1000);

  //enable DRV8833 chip
  Serial.println("Enabling DRV8833");
  digitalWrite(PinSLP,HIGH);
}

void loop() {
  //determine state of the switch
  bool switch01Pressed = !digitalRead(PinSwitch01);

  //choose an action based on the state of the switch
  if(switch01Pressed==0) { 
    goForward();
    
  } else {
    stopCar();
    goBackward();
    turnRight(turnTime_ms);
    stopCar();
  }
      
  Serial.println("");
}


void Performance01() {
  
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
  analogWrite(PinAIN2,130);
  analogWrite(PinBIN1,0); 
  analogWrite(PinBIN2,200);
}

void goBackward() {
  Serial.println("Spin backward");
  analogWrite(PinAIN1,150); 
  analogWrite(PinAIN2,0);
  analogWrite(PinBIN1,150); 
  analogWrite(PinBIN2,0);
  delay(1000); 
}
