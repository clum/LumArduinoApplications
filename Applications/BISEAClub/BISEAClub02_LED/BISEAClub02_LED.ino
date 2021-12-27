/*
LED control for BI SEA Club meeting.

Use sinPulse function

Christopher Lum
lum@uw.edu

Version History
12/26/21: Created
 */

#include "FastLED.h"
#include "LumFastLED.h"

//----------LED--------------
#define LED_TYPE                WS2812B
#define COLOR_ORDER             GRB

#define PIN_LED                 2
#define NUM_LEDS                20

CRGB  leds[NUM_LEDS];

void setup() {   
  //LED
  FastLED.addLeds<LED_TYPE,PIN_LED,COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setDither(0);
}

void loop()
{ 
  uint8_t redA    = 220;  //in between 0 and 255
  uint8_t greenA  = 30;   //in between 0 and 255
  uint8_t blueA   = 0;    //in between 0 and 255

  uint8_t redB    = 50;   //in between 0 and 255
  uint8_t greenB  = 150;   //in between 0 and 255
  uint8_t blueB   = 42;   //in between 0 and 255

  float omega_rps = 3;

  int brightness  = 25;   //in between 0 and 255
  
  //set LEDs using sinPulse
  CRGB colorA = CRGB(redA,greenA,blueA);
  CRGB colorB = CRGB(redB,greenB,blueB);

  sinPulse(leds,NUM_LEDS,colorA,colorB,omega_rps);

  FastLED.setBrightness(brightness);
  FastLED.show();
}
