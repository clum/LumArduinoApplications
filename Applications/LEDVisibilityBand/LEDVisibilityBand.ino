/*
Create a band/sash that can be worn for increased visibility at night.

2021 Christmas gift for Alison

Christopher Lum
lum@uw.edu

Version History
12/12/21: Created
 */

#include "FastLED.h"
#include "LumFastLED.h"

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define PIN_LED     3
#define NUM_LEDS    60

#define BRIGHTNESS  20

//constants
CRGB  leds[NUM_LEDS];

//mode of operation
//  0 = riseAndFall
//  1 = rainbowWithGlitterLum
//  2 = confettiLum
//  3 = bpmLum
int   mode = 3;

void setup() {
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,PIN_LED,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  if(mode==0) {
    CRGB color = CRGB(150,10,5);
    uint16_t deltaT_ms = 10;
    riseAndFall(leds,NUM_LEDS,color,deltaT_ms);
    
  }
  else if(mode==1) {
    fract8 chanceOfGlitter = 20;
    rainbowWithGlitterLum(leds,NUM_LEDS,chanceOfGlitter);
    
  }
  else if(mode==2) {
    uint8_t gHue = 200;
    uint16_t deltaT_ms = 20;
    confettiLum(leds,NUM_LEDS,gHue,deltaT_ms);

  }
  else if(mode==3) {
    uint8_t beatsPerMinute = 60;
    uint8_t gHue = 200;
    bpmLum(leds,NUM_LEDS,beatsPerMinute,gHue);

  }
  else {
    allOff(leds,NUM_LEDS);
  }
    
  FastLED.show();  
}
