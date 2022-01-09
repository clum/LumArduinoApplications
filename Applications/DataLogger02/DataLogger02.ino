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
*/

//----------------------------
//SD Interface
#include <SD.h>
#define PIN_CS  10    //card select pin

File myFile;
const char fileName[] = "Log06.csv";   //cannot be a long file name
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
  smartDelay(1000);
  
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
  double    gps_location_lat_deg  = gps_location.lat();
  double    gps_location_lng_deg  = gps_location.lng();
  
  uint16_t  gps_date_year         = gps_date.year();
  uint8_t   gps_date_month        = gps_date.month();
  uint8_t   gps_date_day          = gps_date.day();

  uint8_t   gps_time_hour         = gps_time.hour();
  uint8_t   gps_time_minute       = gps_time.minute();
  uint8_t   gps_time_second       = gps_time.second();
  uint8_t   gps_time_centisecond  = gps_time.centisecond();

  double    gps_speed_mph         = gps_speed.mph();

  double    gps_course_deg        = gps_course.deg();

  double    gps_altitude_ft       = gps_altitude.feet();

  uint32_t  gps_satellites_value  = gps_satellites.value();

  double    gps_hdop_fraction     = gps_hdop.hdop();

  //-----------log data---------------
  //generate a csv string
  String logString = (String)t_ms + "," +
    (String)temperatureA_c + "," + (String)temperatureB_c + "," +
    (String)gps_location_lat_deg + "," + (String)gps_location_lat_deg + "," +
    (String)gps_date_year + "," + (String)gps_date_month + "," + (String)gps_date_day + "," +
    (String)gps_time_hour + "," + (String)gps_time_minute + "," + (String)gps_time_second + "," + (String)gps_time_centisecond + "," +
    (String)gps_speed_mph + "," + (String)gps_course_deg + "," + (String)gps_altitude_ft + "," + (String)gps_satellites_value + "," + (String)gps_hdop_fraction;

  //print to serial monitor
  Serial.println(logString);
  
  //write current temperature to file
  myFile = SD.open(fileName, FILE_WRITE);
    
  if (myFile) {
    myFile.println(logString);
    
    // close the file:
    myFile.close();
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
    
  }
  
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
