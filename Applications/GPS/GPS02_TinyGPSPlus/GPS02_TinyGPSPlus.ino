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

  //extract data from the TinyGPSPlus class
  TinyGPSLocation gps_location    = gps.location;
  TinyGPSDate     gps_date        = gps.date;
  TinyGPSTime     gps_time        = gps.time;
  TinyGPSSpeed    gps_speed       = gps.speed;
  TinyGPSCourse   gps_course      = gps.course;
  TinyGPSAltitude gps_altitude    = gps.altitude;
  TinyGPSInteger  gps_satellites  = gps.satellites;
  TinyGPSHDOP     gps_hdop        = gps.hdop;

  //unpack data structure
  double    gps_location_lat_deg = gps_location.lat();
  double    gps_location_lng_deg = gps_location.lng();
  
  uint16_t  gps_date_year       = gps_date.year();
  uint8_t   gps_date_month      = gps_date.month();
  uint8_t   gps_date_day        = gps_date.day();

  uint8_t   gps_time_hour       = gps_time.hour();
  uint8_t   gps_time_minute     = gps_time.minute();
  uint8_t   gps_time_second     = gps_time.second();
  uint8_t   gps_time_centisecond  = gps_time.centisecond();

  double    gps_speed_mph       = gps_speed.mph();

  double    gps_course_deg      = gps_course.deg();

  double    gps_altitude_ft     = gps_altitude.feet();

  uint32_t  gps_satellites_value = gps_satellites.value();

  double    gps_hdop_fraction       = gps_hdop.hdop();
    
  //print data to Serial monitor
  Serial.println("gps_location_lat_deg: " + (String)gps_location_lat_deg);
  Serial.println("gps_location_lng_deg: " + (String)gps_location_lng_deg);
  Serial.println("");
  Serial.println("gps_date_year: " + (String)gps_date_year);
  Serial.println("gps_date_month: " + (String)gps_date_month);
  Serial.println("gps_date_day: " + (String)gps_date_day);
  Serial.println("");
  Serial.println("gps_time_hour: " + (String)gps_time_hour);
  Serial.println("gps_time_minute: " + (String)gps_time_minute);
  Serial.println("gps_time_second: " + (String)gps_time_second);
  Serial.println("gps_time_centisecond: " + (String)gps_time_centisecond);
  Serial.println("");
  Serial.println("gps_speed_mph: " + (String)gps_speed_mph);
  Serial.println("");
  Serial.println("gps_course_deg: " + (String)gps_course_deg);
  Serial.println("");
  Serial.println("gps_altitude_ft: " + (String)gps_altitude_ft);
  Serial.println("");
  Serial.println("gps_satellites_value: " + (String)gps_satellites_value);
  Serial.println("");
  Serial.println("gps_hdop_fraction: " + (String)gps_hdop_fraction);  
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
