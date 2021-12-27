/*
LED control for Hope Glows event.

This includes:
-Addressable LED strip
-Two buttons to switch mode and brightness

Christopher Lum
lum@uw.edu

Version History
12/26/21: Created
 */

#include "FastLED.h"
#include "LumFastLED.h"

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

//----------LED--------------
#define LED_TYPE                WS2812B
#define COLOR_ORDER             GRB

#define PIN_LED                 2
#define NUM_LEDS                69

#define BRIGHTNESS              255

CRGB  leds[NUM_LEDS];

//---------SWITCH MODE----------
#define PIN_SWITCHMODE          3

int switchModeLastState       = 0;
int currentLEDMode            = 0;
int numModes                  = 4;

////---------SWITCH BRIGHTNESS----------
#define PIN_SWITCHBRIGHTNESS    4
int switchBrightnessLastState = 0;
int currentBrightness         = 20;
int deltaBrightness           = 50;

void setup() {  
  //Serial
  //Serial.begin(9600);
  
  //LED
  FastLED.addLeds<LED_TYPE,PIN_LED,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  FastLED.setBrightness(BRIGHTNESS);

  //switch mode
  pinMode(PIN_SWITCHMODE, INPUT_PULLUP);

  //switch brightness
  pinMode(PIN_SWITCHBRIGHTNESS, INPUT_PULLUP);
}

void loop()
{
  //---------SWITCH MODE----------
  int switchModeState = !digitalRead(PIN_SWITCHMODE);
  
  //detect rising edge
  int risingEdgeMode = 0;
  if(switchModeState != switchModeLastState) {
    //change in state
    if(switchModeState==1) {
      //switch went high
      risingEdgeMode = 1;
    } else {
      //switch went low
      risingEdgeMode = 0;
    }

    switchModeLastState = switchModeState;
    
  } else {
    //state is the same
    risingEdgeMode = 0;
  }

  //update the mode
  if(risingEdgeMode) {
    if(currentLEDMode==numModes-1) {
      currentLEDMode = 0;
    } else {
      currentLEDMode++;
    }
  }

  //---------SWITCH BRIGHTNESS----------
  int switchBrightnessState = !digitalRead(PIN_SWITCHBRIGHTNESS);
  
  //detect rising edge
  int risingEdgeBrightness = 0;
  if(switchBrightnessState != switchBrightnessLastState) {
    //change in state
    if(switchBrightnessState==1) {
      //switch went high
      risingEdgeBrightness = 1;
    } else {
      //switch went low
      risingEdgeBrightness = 0;
    }

    switchBrightnessLastState = switchBrightnessState;
    
  } else {
    //state is the same
    risingEdgeBrightness = 0;
  }
  
  //update the brightness
  if(risingEdgeBrightness) {
    if(currentBrightness - deltaBrightness > 255) {
      currentBrightness = deltaBrightness;
    } else {
      currentBrightness = currentBrightness + deltaBrightness;
    }
  }
  
  //-------------LED---------------------
  //currentLEDMode  
  //  0 = rainbowWithGlitterLum
  //  1 = confettiLum
  //  2 = bpmLum
  //  3 = riseAndFall
  if(currentLEDMode==0) {
    fract8 chanceOfGlitter = 20;
    rainbowWithGlitterLum(leds,NUM_LEDS,chanceOfGlitter);
    //rainbowLum(leds,NUM_LEDS);
    
  } else if(currentLEDMode==1) {
    uint8_t gHue = 200;
    uint16_t deltaT_ms = 20;
    confettiLum(leds,NUM_LEDS,gHue,deltaT_ms);

  } else if(currentLEDMode==2) {
    uint8_t beatsPerMinute = 60;
    uint8_t gHue = 200;
    bpmLum(leds,NUM_LEDS,beatsPerMinute,gHue);

  } else if(currentLEDMode==3) {
  CRGB color = CRGB(150,10,5);
    uint16_t deltaT_ms = 10;
    riseAndFall(leds,NUM_LEDS,color,deltaT_ms);
    
  } else {
    allOff(leds,NUM_LEDS);
  }

  FastLED.setBrightness(currentBrightness);
  FastLED.show();

  //Debugging
  //Serial.println((String)switchModeState + "," + (String)risingEdgeMode + "," + (String)switchBrightnessState + "," + (String)risingEdgeBrightness);
  //Serial.println((String)risingEdgeMode + "," + (String)currentLEDMode);
}
