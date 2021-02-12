/**
 * httpUpdateSPIFFS.ino
 *
 *  Created on: 27.11.2017
 *
 */

#include <Arduino.h>

#include <WiFi.h>

#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

#define USE_SERIAL Serial


const char* ssid     = "I-Tech-Router";     // your network SSID (name of wifi network)
const char* password = "0512303189T"; // your network password

void setup() {

    USE_SERIAL.begin(115200);
  
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  
    // attempt to connect to Wifi network:
    byte retries = 0;
    while (WiFi.status() != WL_CONNECTED) {
      USE_SERIAL.print(".");
      // wait 1 second for re-trying
      delay(100);
    }
    USE_SERIAL.println("");
    USE_SERIAL.print("Connected, IP: ");
    USE_SERIAL.println(WiFi.localIP());

}

void loop() {
    // wait for WiFi connection
    if((WiFi.status() == WL_CONNECTED)) {

        t_httpUpdate_return ret = ESPhttpUpdate.updateSpiffs("https://github.com/abdulwasey77/TestFOTAesp32/blob/main/FOTA_ESP32_SPIFFS/httpUpdateSPIFFS.bin","1");
        USE_SERIAL.println(ret);
        if(ret == HTTP_UPDATE_OK)
        {
            USE_SERIAL.println("Update sketch...");
            ret = ESPhttpUpdate.update("https://github.com/abdulwasey77/TestFOTAesp32/blob/main/FOTA_ESP32_SPIFFS/httpUpdateSPIFFS.bin");

            switch(ret) {
                case HTTP_UPDATE_FAILED:
                    USE_SERIAL.printf("HTTP_UPDATE_FAILED Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                     USE_SERIAL.println();
                    break;

                case HTTP_UPDATE_NO_UPDATES:
                    USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
                    USE_SERIAL.println();
                    break;

                case HTTP_UPDATE_OK:
                    USE_SERIAL.println("HTTP_UPDATE_OK");
                    USE_SERIAL.println();
                    break;
            }
        }
    }
}
