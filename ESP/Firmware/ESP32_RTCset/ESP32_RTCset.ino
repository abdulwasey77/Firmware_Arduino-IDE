#include <WiFi.h>
#include "time.h"

const char* ssid       = "I-Tech-Router";
const char* password   = "0512303189T";

//const char* ssid       = "Chili Garlic";
//const char* password   = "Mayonnaise200ml";
 
  
  
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;

void printLocalTime()
{
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%d/%B/%Y %H:%M:%S", &timeinfo);
  String timeset = String(timeStringBuff);
  Serial.println(timeset);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("hello");
  delay(10000);
  WiFi.begin(ssid, password);
  configTime(0, 0, "");
}

void loop()
{
  delay(1000);
  printLocalTime();
}
