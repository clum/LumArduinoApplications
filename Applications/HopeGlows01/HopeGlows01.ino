/*
Control an external RGB LED for the Hope Glows event.

This uses a non-addressable LED strip.

This also uses a HC-SR04 to measure the change the color based on the distance.

Christopher Lum
lum@uw.edu

Version History
12/06/21: created
12/11/21: Adding reference to LumArrays
12/26/21: Updated documentation
*/

#include "LumArrays.h"
#include "LumHCSR04.h"

//Constants
int PinLED_R          = 9;
int PinLED_G          = 10;
int PinLED_B          = 11;

int PinHCS04Trigger   = 4;
int PinHCS04Echo      = 5;

//Save previous measurements
int duration_ms_k1 = 0;
int duration_ms_k2 = 0;
int duration_ms_k3 = 0;
int duration_ms_k4 = 0;

void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinLED_R,OUTPUT);
  pinMode(PinLED_G,OUTPUT);
  pinMode(PinLED_B,OUTPUT);

  //HC-SR04
  pinMode(PinHCS04Trigger,OUTPUT);
  pinMode(PinHCS04Echo,INPUT);
}

void loop() {
  int red = 255;
  analogWrite(PinLED_R,red);

  //Use HC-SR04 to determine distance
  int timeOfFlight_microseconds = HCSR04GetTimeOfFlight_ms(PinHCS04Trigger, PinHCS04Echo);

  //get rid of spikes
  if (duration_ms>3500) {
    duration_ms = 3500;
  }
  
  //average out some noise
  unsigned int numSamples = 5;
  int duration_vec_ms[numSamples];
  duration_vec_ms[0] = duration_ms;
  duration_vec_ms[1] = duration_ms_k1;
  duration_vec_ms[2] = duration_ms_k2;
  duration_vec_ms[3] = duration_ms_k3;
  duration_vec_ms[4] = duration_ms_k4;  
  
  int average_duration_ms = average(duration_vec_ms,numSamples);
  
  //convert duration_ms to a value in the range [0,255]
  int greenUF = map(duration_ms,0,3500,0,255);  
  int green = map(average_duration_ms,0,3500,0,255);

  Serial.print(greenUF);
  Serial.print(",");
  Serial.println(green);
  
  analogWrite(PinLED_G,green);  

  int blue = 0;
  analogWrite(PinLED_B,blue);

  //save values
  duration_ms_k1 = duration_ms;
  duration_ms_k2 = duration_ms_k1;
  duration_ms_k3 = duration_ms_k2;
  duration_ms_k4 = duration_ms_k3;  

  delay(25);
}
