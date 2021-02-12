#include "SPIFFS.h"
 
void listAllFiles(){
 
  File root = SPIFFS.open("/");
 
  File file = root.openNextFile();
 
  while(file){
 
      Serial.print("FILE: ");
      Serial.println(file.name());
 
      file = root.openNextFile();
  }
 
}
 String fileread;
void setup() {
 
  Serial.begin(115200);
 
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
 
//writefile();
readfile();
//delfile();
 
}
 
void loop() {}

void readfile(){
  File file = SPIFFS.open("/test.txt");

  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }
 
 while(file.available()){
  char readdata = (char)file.read();
  fileread += String(readdata);
  }
  Serial.println(fileread);
  file.close();
}

void writefile(){
  File file = SPIFFS.open("/test.txt", FILE_WRITE);
  if (file.print("hello world")) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
  file.close();
}

void delfile(){
  SPIFFS.remove("/test.txt");

}
