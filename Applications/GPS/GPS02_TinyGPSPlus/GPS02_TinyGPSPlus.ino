/*
Interface with a GPS unit and print out the serial output from the GPS.

This is based off the TinyGPS++ FullExmple.ino example.

Christopher Lum
lum@uw.edu

Version History
01/07/22: Created
 */

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4;   //reverse, TX on GPS is the RX pin on the Arduino
static const int TXPin = 3;   //reverse, RX on GPS is the TX pin on the Arduino
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  //delay and give gps object time to consume serial data
  smartDelay(1000);

  //print data
  Serial.println("#Sat:         " + (String)gps.satellites.value());
  Serial.println("Lat (deg):    " + (String)gps.location.lat());
  Serial.println("Lon (deg):    " + (String)gps.location.lng());
  Serial.println("Alt (m):      " + (String)gps.altitude.meters());
  Serial.println("Speed (kmph): " + (String)gps.speed.kmph());

  Serial.print("Date/Time:    ");
  printDateTime(gps.date, gps.time);
  Serial.println("");
  
  Serial.println("--");
  
}


// This custom version of delay() ensures that the gps object is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  smartDelay(0);
}
