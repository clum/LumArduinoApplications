/*
Log data to an SD card.

This writes (appends to a file).

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
const char fileName[] = "Log01.txt";   //cannot be a long file name

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
  
  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //print the temperature in Celsius
  float temperature_C = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(temperature_C);
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");
  
  //print the temperature in Fahrenheit
  Serial.print((temperature_C * 9.0) / 5.0 + 32.0);
  Serial.print((char)176);//shows degrees character
  Serial.println("F");

  //write current temperature to file
  myFile = SD.open(fileName, FILE_WRITE);
    
  if (myFile) {
    myFile.println((String)t_ms+","+(String)temperature_C);
    
    // close the file:
    myFile.close();
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
    
  }
  
  delay(500);
}
