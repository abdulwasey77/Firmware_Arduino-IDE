#include <FS.h>
#include <SPIFFS.h>
#include <SD.h> // (or SD_MMC.h)
#include <SPI.h>

#define SD_CS 5

void setup() {
      Serial.begin(115200);
      delay(10);
      Serial.println("Serial Started...");
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }else{
      Serial.println("Card Mount Sucessfully");
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }else{
      Serial.println("SD card attached");
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
    }else{
      Serial.println("SPIFFS done!");
    }
  readFile(SD,"/music.mp3");  
  File sourceFile = SD.open("/music.mp3");
  Serial.println("SD opened file music.mp3");
  File destFile = SPIFFS.open("/musicRecv.mp3", FILE_WRITE);
  Serial.println("SPIFFS opened file musicRecv.mp3");
  static uint8_t buf[512];
  while( sourceFile.read( buf, 512) ) {
  destFile.write( buf, 512 );
  }
  Serial.println("SPIFFS write file musicRecv.mp3");
  destFile.close();
  sourceFile.close();
  //String fileread="/musicRecv.mp3";
 // readfile(fileread);
  Serial.println("file closed..");

  File sourceFile2 = SPIFFS.open("/musicRecv.mp3");
  Serial.println("SPIFFS open file musicRecv.mp3");
  File destFile2 = SD.open("/RecvBack.mp3", FILE_WRITE);
  Serial.println("SD open file RecvBack.mp3");
  static uint8_t buf2[512];
  while( sourceFile2.read( buf2, 512) ) {
  destFile2.write( buf2, 512 );
  }
  Serial.println("SD write file RecvBack.mp3");
  destFile2.close();
  sourceFile2.close();
  Serial.println("file closed..");

  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void readfile(String rec){
  File file = SPIFFS.open(rec);
  Serial.println(file);
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }
  Serial.print("read data from spiffs:");
 while(file.available()){
    char readdata = (char)file.read();
    Serial.print(readdata);
  }
  file.close();
  Serial.println();
}
