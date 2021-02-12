#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme(BME_CS);
char c;
String temp="";
String hum="";
String pres="";

String Dataget="";
void setup() {
  Serial.begin(9600);
    while (!Serial);
  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
}

void loop() {
  if(!bme.performReading()) {
  Serial.println("Failed to perform reading");
  delay(5000);
  }else{
  if(Dataget=="Temperature"){
   Wire.onRequest(requestEventtemp);
  }
    if(Dataget=="Humidity"){
   Wire.onRequest(requestEventhum);
  }
    if(Dataget=="Pressure"){
   Wire.onRequest(requestEventpress);
  }
  Dataget="";
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEventtemp() {
  if(bme.temperature>=0&&bme.temperature<=130){
    temp="T";
  temp+= String(bme.temperature);
  Serial.print("Sending Temperature: "); Serial.println(temp);
  Wire.write(temp.c_str());
  Wire.write("A"); 
  }else{
  Serial.print("Failed to read Temperature: ");
  temp="TError"; 
  Wire.write(hum.c_str());
  Wire.write("A");
  }
}
void requestEventhum() {
  if(bme.humidity>=20 && bme.humidity<=100){
    hum="H";
  hum+= String(bme.humidity);
  Serial.print("Sending Humidity: "); Serial.println(hum);
  Wire.write(hum.c_str());
  Wire.write("B");
  }else{
  Serial.print("Failed to read Humidity: ");
  hum="HError"; 
  Wire.write(hum.c_str());
  Wire.write("B");
}
}
void requestEventpress() {
  if((bme.pressure/100.0)>=900&&(bme.pressure/100.0)<=1000){
  pres="P";  
  pres+= String(bme.pressure / 100.0);
  Serial.print("Sending Pressure: "); Serial.println(pres);
  Wire.write(pres.c_str());
  Wire.write("C");
  }else{
  Serial.print("Failed to read Humidity: ");
  pres="PError"; 
  Wire.write(hum.c_str());
  Wire.write("C");
  }
  
}


void receiveEvent() {
  while (Wire.available() && c!=":") { // loop through all but the last
    c = Wire.read();   // receive byte as a character
    Dataget+=c;
    //Serial.print(c);
  }
  c=0;
  int collon=Dataget.indexOf(':');
  Dataget[collon]=0;
  Serial.print("Recevied : "); Serial.println(Dataget);
}


/*
  


  #include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

//#define BME_SCK 13
//#define BME_MISO 12
//#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME680 bme; // I2C
Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() {
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
  delay(2000);
}

 
 */













/*

#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
 
 */
