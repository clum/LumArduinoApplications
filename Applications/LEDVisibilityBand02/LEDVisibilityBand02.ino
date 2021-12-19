/*
Create a band/sash that can be worn for increased visibility at night.

2021 Christmas gift for Alison

Christopher Lum
lum@uw.edu

Version History
12/12/21: Created
12/18/21: Adding changing mode
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

#define BRIGHTNESS  255

//constants
CRGB  leds[NUM_LEDS];

//mode of operation
//  0 = riseAndFall
//  1 = rainbowWithGlitterLum
//  2 = confettiLum
//  3 = bpmLum
int   mode = 0;

//switch
int PinSwitch = 2;
int lastSwitchState = 0;


void setup() {  
  //Serial
  Serial.begin(9600);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,PIN_LED,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  //switch
  pinMode(PinSwitch, INPUT_PULLUP);
}

void loop()
{
  //Mode Select
  int stateSwitch = !digitalRead(PinSwitch);
  
  //detect rising edge
  int risingEdge = 0;
  if(stateSwitch != lastSwitchState) {
    //change in state
    if(stateSwitch==1) {
      //switch went high
      risingEdge = 1;
    } else {
      //switch went low
      risingEdge = 0;
    }

    lastSwitchState = stateSwitch;
    
  } else {
    //state is the same
    risingEdge = 0;
  }

  //update the mode
  int numModes = 4;
  if(risingEdge) {
    if(mode==numModes-1) {
      mode = 0;
    } else {
      mode++;
    }    
  }
  
  //LED
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

  //Debugging
  Serial.println((String)stateSwitch + "," + (String)risingEdge);
}
