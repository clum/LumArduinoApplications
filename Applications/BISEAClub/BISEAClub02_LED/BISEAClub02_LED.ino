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
  uint8_t redA    = 0;  //in between 0 and 255
  uint8_t greenA  = 0;   //in between 0 and 255
  uint8_t blueA   = 255;    //in between 0 and 255

  uint8_t redB    = 0;   //in between 0 and 255
  uint8_t greenB  = 255;   //in between 0 and 255
  uint8_t blueB   = 0;   //in between 0 and 255

  float omega_rps = 2;

  int brightness  = 15;   //in between 0 and 255
  
  //set LEDs using sinPulse
  CRGB colorA = CRGB(redA,greenA,blueA);
  CRGB colorB = CRGB(redB,greenB,blueB);

  sinPulse(leds,NUM_LEDS,colorA,colorB,omega_rps);

  FastLED.setBrightness(brightness);
  FastLED.show();
}
