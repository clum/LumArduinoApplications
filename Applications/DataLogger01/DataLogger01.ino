/*
Log data to an SD card.

Info on multiple DS18B20 sensors located at https://lastminuteengineers.com/multiple-ds18b20-arduino-tutorial/

Christopher Lum
lum@uw.edu

Version History
12/27/21: Created
01/01/22: Changed data type for return of millis from 'uint16_t' to 'unsigned long' to avoid overflow
*/

//----------------------------
//SD Interface
#include <SD.h>
#define PIN_CS  10    //card select pin

File myFile;
const char fileName[] = "Log03.txt";   //cannot be a long file name
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
}
 
void loop()
{
  //get current time
  unsigned long t_ms = millis();
  
  //gather data to log  
  sensors.requestTemperatures(); 
  float temperatureA_c = sensors.getTempCByIndex(0);
  float temperatureB_c = sensors.getTempCByIndex(1);

  //generate a csv string
  String logString = (String)t_ms+","+(String)temperatureA_c+","+(String)temperatureB_c;

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
  
  delay(500);
}
