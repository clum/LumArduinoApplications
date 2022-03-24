/*
Control a passive buzzer and play a song.

Christopher Lum
lum@uw.edu

Version History
11/14/21: created
03/21/22: updated documentation
*/

#include "pitches.h"

//Constants
int PinLED_R = A5;
int PinLED_G = A4;
int PinLED_B = A3;

int PinBuzzer = 8;

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinLED_R,OUTPUT);
  pinMode(PinLED_G,OUTPUT);
  pinMode(PinLED_B,OUTPUT);

  //Buzzer
  pinMode(PinBuzzer,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // notes in the melody:

//  //shave and a haircut
//  int melodyLength = 8;
//  int melody[] = {
//    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
//  };
//  
//  // note durations: 4 = quarter note, 8 = eighth note, etc.:
//  int noteDurations[] = {
//    4, 8, 8, 4, 4, 4, 4, 4
//  };

  //jingle bells
  int melodyLength = 27;
  int melody[] = {
    NOTE_E4, NOTE_E4, NOTE_E4,                    //jingle bells
    NOTE_E4, NOTE_E4, NOTE_E4,                    //jingle bells
    NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, 0,  //jingle all the way
    NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4,   //oh what fun it is to ride
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4,    //in a one horse open sleigh
    NOTE_G4 //hey
  };
  
  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 4, 2,  //3
    4, 4, 2,  //6
    4, 4, 3, 8, 2, 2, //12
    4, 4, 4, 4, 4, 4, 4,  //19
    8, 8, 4, 4, 4, 4, 2,   //26
    2     //27
  };


  // iterate over the notes of the melody:
  int lightNumber = 1;
  for (int thisNote = 0; thisNote < melodyLength; thisNote++) {
    //---
    //LED
    //---
    //flash a light
    if(melody[thisNote]!=0) {
      switch(lightNumber) {
        case 1:
          digitalWrite(PinLED_R,HIGH); 
          digitalWrite(PinLED_G,LOW);
          digitalWrite(PinLED_B,LOW);
          lightNumber = 2;
          break;
  
        case 2:
          digitalWrite(PinLED_R,LOW); 
          digitalWrite(PinLED_G,HIGH);
          digitalWrite(PinLED_B,LOW);        
          lightNumber = 3;
          break;
  
        case 3:
          digitalWrite(PinLED_R,LOW); 
          digitalWrite(PinLED_G,LOW);
          digitalWrite(PinLED_B,HIGH);
          lightNumber = 1;
          break;
      }
    }

    //------
    //BUZZER
    //------
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
//    int noteDuration = 3000 / noteDurations[thisNote];
    tone(PinBuzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // stop the tone playing:
    noTone(PinBuzzer);
  }

  //delay between repetitions
  delay(3000);
    
}
