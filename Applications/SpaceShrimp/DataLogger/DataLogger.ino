/*
Log data to an SD card.  The data comes from various sources

-DS18B20 sensors (2 sensors)
-GPS module

Info on multiple DS18B20 sensors located at https://lastminuteengineers.com/multiple-ds18b20-arduino-tutorial/

Christopher Lum
lum@uw.edu

Version History
12/27/21: Created
01/01/22: Changed data type for return of millis from 'uint16_t' to 'unsigned long' to avoid overflow
01/08/22: Added GPS module
01/10/22: Updating
01/12/22: Updating.  Encountered issue where SD.open failed.  This might have been due to running out of memory on Nano.  Fixed by leaving out some floats.  Verified to work on Nano.
*/

//----------------------------
//SD Interface
#include <SD.h>
#define PIN_CS  10    //card select pin

File myFile;
const char fileName[] = "Log05.csv";   //cannot be a long file name
//----------------------------

//----------------------------
//DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
//----------------------------

//----------------------------
//GPS Module
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "LumTinyGPSPlus.h"

#define PIN_GPS_RX  4
#define PIN_GPS_TX  3
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(PIN_GPS_RX, PIN_GPS_TX);
//----------------------------

void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  pinMode(PIN_CS, OUTPUT);
 
  if (!SD.begin(PIN_CS)) {
    Serial.println("initialization failed!");
    return;
  }
  
  Serial.println("initialization done.");
 
  //Start up the sensor library
  sensors.begin();

  //start software serial
  ss.begin(GPSBaud);
}
 
void loop()
{
  //get current time since start
  unsigned long t_ms = millis();

  //delay and give gps object time to consume serial data
  unsigned long delayDeltaT_ms = 1000;
  DelayAndEncodeGPSViaSoftwareSerial(delayDeltaT_ms,&gps,&ss);
  
  //-----------gather data to log---------------
  sensors.requestTemperatures(); 

  //temperature
  float temperatureA_c = sensors.getTempCByIndex(0);
  float temperatureB_c = sensors.getTempCByIndex(1);

  //GPS module
  TinyGPSLocation gps_location    = gps.location;
  TinyGPSDate     gps_date        = gps.date;
  TinyGPSTime     gps_time        = gps.time;
  TinyGPSSpeed    gps_speed       = gps.speed;
  TinyGPSCourse   gps_course      = gps.course;
  TinyGPSAltitude gps_altitude    = gps.altitude;
  TinyGPSInteger  gps_satellites  = gps.satellites;
  TinyGPSHDOP     gps_hdop        = gps.hdop;

  //unpack data structure
  bool      gps_isValid           = gps_location.isValid();
  double    gps_location_lat_deg  = gps_location.lat();
  double    gps_location_lng_deg  = gps_location.lng();
  
  uint16_t  gps_date_year         = gps_date.year();
  uint8_t   gps_date_month        = gps_date.month();
  uint8_t   gps_date_day          = gps_date.day();

  uint8_t   gps_time_hour         = gps_time.hour();
  uint8_t   gps_time_minute       = gps_time.minute();
  uint8_t   gps_time_second       = gps_time.second();
  
  double    gps_speed_mph         = gps_speed.mph();

  double    gps_course_deg        = gps_course.deg();

  double    gps_altitude_ft       = gps_altitude.feet();

  uint32_t  gps_satellites_value  = gps_satellites.value();

  double    gps_hdop_fraction     = gps_hdop.hdop();

  //-----------log data---------------
  //generate a string for float values
  char comma[2] = ",";
  char str_floats[100] = "";

  uint8_t minWidth = 9;
  uint8_t precision = 5;
  
  //temperatureA_c
  char str_temperatureA_c[8];
  minWidth = 4;
  precision = 2;
  dtostrf(temperatureA_c,minWidth,precision,str_temperatureA_c);
  strcat(str_floats,str_temperatureA_c);
  strcat(str_floats,comma);  

  //temperatureB_c
  char str_temperatureB_c[8];
  minWidth = 4;
  precision = 2;
  dtostrf(temperatureB_c,minWidth,precision,str_temperatureB_c);
  strcat(str_floats,str_temperatureB_c);
  strcat(str_floats,comma);
    
  //str_gps_location_lat_deg
  char str_gps_location_lat_deg[15];
  minWidth = 7;
  precision = 5;
  dtostrf(gps_location_lat_deg,minWidth,precision,str_gps_location_lat_deg);
  strcat(str_floats,str_gps_location_lat_deg);
  strcat(str_floats,comma);  

  //str_gps_location_lng_deg
  char str_gps_location_lng_deg[15];
  minWidth = 7;
  precision = 5;
  dtostrf(gps_location_lng_deg,minWidth,precision,str_gps_location_lng_deg);
  strcat(str_floats,str_gps_location_lng_deg);
  strcat(str_floats,comma);

  //gps_speed_mph
  char str_gps_speed_mph[8];
  minWidth = 4;
  precision = 2;
  dtostrf(gps_speed_mph,minWidth,precision,str_gps_speed_mph);
  strcat(str_floats,str_gps_speed_mph);
  strcat(str_floats,comma);

  /*
   * MIGHT NEED TO LEAVE OUT AS INCLUDING MIGHT GIVE US MEMORY OVERFLOW ISSUES AND MAKE IT SO WE CANNOT OPEN SD CARD FILE
  //gps_course_deg
  char str_gps_course_deg[8];
  minWidth = 4;
  precision = 2;
  dtostrf(gps_course_deg,minWidth,precision,str_gps_course_deg);
  strcat(str_floats,str_gps_course_deg);
  strcat(str_floats,comma);
  */

  //gps_altitude_ft
  char str_gps_altitude_ft[15];
  minWidth = 4;
  precision = 2;
  dtostrf(gps_altitude_ft,minWidth,precision,str_gps_altitude_ft);
  strcat(str_floats,str_gps_altitude_ft);
  strcat(str_floats,comma);

  //gps_hdop_fraction
  char str_gps_hdop_fraction[8];
  minWidth = 4;
  precision = 2;
  dtostrf(gps_hdop_fraction,minWidth,precision,str_gps_hdop_fraction);
  strcat(str_floats,str_gps_hdop_fraction);
  strcat(str_floats,comma);
  
  //generate the complete csv string
  char str[150];

  //cast some variables to a different data type so sprintf will format them correctly
  uint8_t gps_satellites_value2 = (uint8_t)gps_satellites_value;

  //sprintf(str,"%s",str_floats);   //works
  sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%s",gps_isValid,gps_date_year,gps_date_month,gps_date_day,gps_time_hour,gps_time_minute,gps_time_second,gps_satellites_value2,str_floats);   //fails
  
  //print to serial monitor
  Serial.println(str);
  
  //write str to file
  myFile = SD.open(fileName, FILE_WRITE);    
  if (myFile) {
    myFile.println(str);
    
    // close the file:
    myFile.close();
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
    
  }  
}
