/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
*/

#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
 
#define DHTPIN 2
//our sensor is DHT22 type
#define DHTTYPE DHT22
//create an instance of DHT sensor
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;
  
void setup() {
  Serial.begin(115200);
  Serial.println("start");
  dht.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
  while (1) {}
  }
}
  
void loop() {
    //use the functions which are supplied by library.
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
}
  Serial.println("--------------------------Reading Sensor Values of BMP180-------------------------");
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.print(" *C");
  Serial.print("     ");
  Serial.print("Pressure = ");
  String a =String(bmp.readPressure());
  Serial.print(a);
  Serial.print(" Pa");
  Serial.print("     ");
  Serial.print("Pressure at sea level = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");
    
  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("        ");
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.print(" meters");
  Serial.print("                ");
  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(102000));
  Serial.println(" meters");
  Serial.println();
  
  Serial.println("--------------------------Reading sensor values of DHT22--------------------------");
  Serial.print("             ");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %         \t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.println();
  Serial.println();
  Serial.println();
  delay(3000);
}
