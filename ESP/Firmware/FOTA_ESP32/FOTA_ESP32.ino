#include "ArduinoJson.h"
#include <WiFi.h>
#include "esp32fota.h"
#include <WiFiClientSecure.h>


const char* ssid     = "I-Tech-Router";     // your network SSID (name of wifi network)
const char* password = "0512303189T"; // your network password

WiFiClientSecure clientForOta;
secureEsp32FOTA secureEsp32FOTA("esp32-fota-https", 1);

void setup(){
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  byte retries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(100);
  }
  Serial.println("");
  Serial.print("Connected, IP: ");
  Serial.println(WiFi.localIP());
     
  secureEsp32FOTA._host="raw.githubusercontent.com"; //e.g. example.com
  secureEsp32FOTA._descriptionOfFirmwareURL="/abdulwasey77/TestFOTAesp32/main/fota/firmware.json"; //e.g. /my-fw-versions/firmware.json
 // secureEsp32FOTA._certificate=test_root_ca;
  secureEsp32FOTA.clientForOta=clientForOta;
}


void loop()
{
  bool shouldExecuteFirmwareUpdate=secureEsp32FOTA.execHTTPSCheck();
  if(shouldExecuteFirmwareUpdate)
  {
    Serial.println("Firmware update available!");
    secureEsp32FOTA.executeOTA();
  }
}
