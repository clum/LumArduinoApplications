/*
Interface with a GPS unit and print out the serial output from the GPS.

GPS Connections
PPS -> N/A
RX  -> D3 (note this is reversed)
TX  -> D4 (note this is reversed)
GND -> GND
VCC -> 5V

References
https://create.arduino.cc/projecthub/amalmathewtech/arduino-gps-module-destination-notifier-288a55
https://youtu.be/kwk3qzaIcCU?t=839

Christopher Lum
lum@uw.edu

Version History
01/07/22: Created
 */

#include <SoftwareSerial.h>

static const int RXPin = 4;   //reverse, TX on GPS is the RX pin on the Arduino
static const int TXPin = 3;   //reverse, RX on GPS is the TX pin on the Arduino
static const uint32_t GPSBaud = 9600;

SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  while (ss.available() > 0){
    //constantly read incoming serial chars
    int valInt = ss.read();
    char valChar = (char)valInt;
    
    Serial.print(valChar);
  }
}
