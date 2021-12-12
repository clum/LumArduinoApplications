/*
Interface with a 2 axis joystick and use these values to control 2 LEDs

Christopher Lum
lum@uw.edu

Version History
10/27/21: created
*/

#include "LumLibrary.h"

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

  //map joystick values to brightness
  int brightnessRed = 0;
  int brightnessGreen = 0;
  int brightnessBlue = 0;

  brightnessRed = map(Xval,0,1024,0,255);
  brightnessGreen = map(Yval,0,1024,0,255);

  if(Sval==HIGH) {
    brightnessBlue = 0;
  } else {
    brightnessBlue = 255;
  }
  
  //print values
  Serial.println("(X,Y) = (" + (String)Xval + "," + (String)Yval + "), switch = " + (String)Sval);  

  int a = 2;
  int b = 5;
  int c = addTwoInts(a, b);
  Serial.println("calling function " + (String)c);
  
  //activate LEDs
  analogWrite(PinLEDRed, brightnessRed);
  analogWrite(PinLEDGreen, brightnessGreen);
  analogWrite(PinLEDBlue, brightnessBlue);
  
  delay(100);
}
