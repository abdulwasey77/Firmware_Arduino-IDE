#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void setup() {
Serial.begin(115200);
 if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
 DateTime now = rtc.now();


 Serial.print(now.hour(), DEC);
 Serial.print(":");
 Serial.print(now.minute(), DEC);
 Serial.print(":");
 Serial.print(now.second(), DEC);
 Serial.print("  ");
 Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
 Serial.print("  ");
 Serial.print(now.day(), DEC);
 Serial.print("/");
 Serial.print(now.month(), DEC);
 Serial.print("/");
 Serial.println(now.year(), DEC);
 delay(1000);
}
