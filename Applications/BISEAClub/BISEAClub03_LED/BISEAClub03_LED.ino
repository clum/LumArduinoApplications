/*
LED control for BI SEA Club meeting #3.

Use sinPulse function with multiple sets of colors.

Christopher Lum
lum@uw.edu

Version History
01/05/22: Created
 */

#include "FastLED.h"
#include "LumFastLED.h"

//----------LED--------------
#define LED_TYPE                WS2812B
#define COLOR_ORDER             GRB

#define PIN_LED                 2
#define NUM_LEDS                162

CRGB  leds[NUM_LEDS];

float deltaTModeChange_s  = 5;   //time between mode changes
float tLastModeChange_s   = 0;    //time of the last mode change
int mode                  = 0;
int numModes              = 2;

void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  FastLED.addLeds<LED_TYPE,PIN_LED,COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setDither(0);
}

void loop()
{ 
  //instantiate variables
  uint8_t redA;
  uint8_t greenA;
  uint8_t blueA;

  uint8_t redB;
  uint8_t greenB;
  uint8_t blueB;

  float omega_rps;

  int brightness;

  //get current mode
  uint16_t ms = millis();
  float t = float(ms) / 1000;

  if((t - tLastModeChange_s) > deltaTModeChange_s) {
    //change mode
    if(mode < (numModes - 1)) {
      mode++;
      
    } else {
      mode = 0;
      
    }
    
    tLastModeChange_s = t;
  }
    
  //get parameters (colors, brightness, etc.) for current mode  
  if(mode==0) {
    //Amara colors
    redA        = 0;
    greenA      = 0;
    blueA       = 255;

    redB        = 0;
    greenB      = 255;
    blueB       = 0;

    omega_rps   = 2;
    
    brightness  = 15;
    
  } else if (mode==1) {
    redA        = 200;
    greenA      = 40;
    blueA       = 100;

    redB        = 250;
    greenB      = 34;
    blueB       = 21;

    omega_rps   = 2;
    
    brightness  = 15;

  } else if (mode==2) {
    redA        = 0;
    greenA      = 0;
    blueA       = 200;

    redB        = 0;
    greenB      = 200;
    blueB       = 0;

    omega_rps   = 1;
    
    brightness  = 100;  
  }
  
  //set LEDs using sinPulse
  CRGB colorA = CRGB(redA,greenA,blueA);
  CRGB colorB = CRGB(redB,greenB,blueB);

  sinPulse(leds,NUM_LEDS,colorA,colorB,omega_rps);

  FastLED.setBrightness(brightness);
  FastLED.show();

  Serial.println((String)t + "," + (String)tLastModeChange_s + "," + (String)mode);
}
