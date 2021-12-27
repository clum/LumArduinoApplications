/*
LED control for BI SEA Club meeting

Use allOn function

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
  uint8_t red     = 220;  //in between 0 and 255
  uint8_t green   = 30;   //in between 0 and 255
  uint8_t blue    = 0;    //in between 0 and 255
  
  int brightness  = 20;   //in between 0 and 255
    
  CRGB color = CRGB(red,green,blue);
  
  allOn(leds,NUM_LEDS,color);

  FastLED.setBrightness(brightness);
  FastLED.show();
}
