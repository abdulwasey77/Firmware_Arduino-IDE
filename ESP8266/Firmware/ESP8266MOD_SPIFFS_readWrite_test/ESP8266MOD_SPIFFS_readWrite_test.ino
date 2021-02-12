#include <FS.h>
 
void setup() {
 
  Serial.begin(115200);
  Serial.println();
 
  bool success = SPIFFS.begin();
 
  if (!success) {
    Serial.println("Error mounting the file system");
    return;
  }
  SPIFFS.remove("/file.txt");
  File file = SPIFFS.open("/file.txt", "w");
 
  if (!file) {
    Serial.println("Error opening file for writing");
    return;
  }
  String writedata="$ssid_wifi,pwd_wifi,broker_mqtt,port_mqtt*";
  int bytesWritten = file.print(writedata);
 
  if (bytesWritten == 0) {
    Serial.println("File write failed");
    return;
  }
 
  file.close();
 
 
  File file2 = SPIFFS.open("/file.txt", "r");
 
  if (!file2) {
    Serial.println("Failed to open file for reading");
    return;
  }
 
  Serial.println("File Content:");
  String dataread;
  while (file2.available()) {
 
    char c=file2.read();
    dataread+=c;
  }
 Serial.print("Data : "); Serial.println(dataread);
  file2.close();
 
}
 
void loop() {}
