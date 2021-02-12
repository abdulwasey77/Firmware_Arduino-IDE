#include "SPIFFS.h"
String line="";
String getdata="";
String dataread;

unsigned long count=0;

void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
Serial.begin(115200);
Serial.setRxBufferSize(1024*60);
//delay(1000);
Serial.println("print");
  if (!SPIFFS.begin(true)) {
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
  }
//  delfile();
//  readfile();
//
//  if(dataread==""){
//    Serial.println("Enter File data");
//    while (Serial.available() == 0){  
//     } 
//     long check1 =millis();  
//    while(Serial.available()!=0 || millis()-check1<=10000)
//    {
//     while(Serial.available()!=0){
//      char c= Serial.read();
//      dataread+=String(c);
//      count++;
//      //delayMicroseconds(50);
//     }
//    }
//    
//    delay(50);
//    Serial.print("count : "); Serial.println(count);
//    count=0;
//   
//}
// writefile();
// dataread="";
// delay(1);

   delfile2();
   readfile2();

  if(getdata==""){
    Serial.println("Enter File data");
    while (Serial.available() == 0){  
     } 
     long check2 =millis();  
    while(Serial.available()!=0 || millis()-check2<=10000)
    {
     while(Serial.available()!=0){
      char c= Serial.read();
      getdata+=String(c);
      count++;
      //delayMicroseconds(50);
     }
    }
    
    delay(50);
    Serial.print("count : "); Serial.println(count);
    count=0;
   
}
     writefile2();
     getdata="";
     delay(1);

    
    readfile2();
    delay(1);
    readfile();
    delay(1);
    if(dataread==getdata){
      Serial.println("File Matched");
      Serial.println();
      Serial.print("Get data : "); Serial.println(getdata);
      
      Serial.println();
      Serial.print("readdata : "); Serial.println(dataread);
      }else{
      Serial.println("File not Matched");
      Serial.println();
      Serial.print("Get data : "); Serial.println(getdata);
      
      Serial.println();
      Serial.print("readdata : "); Serial.println(dataread);
    }

}

void loop() {

}


void readfile(){
  File file = SPIFFS.open("/test.txt");
  Serial.println(file);
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }

 while(file.available()>0){
    char readdata = (char)file.read();
    dataread += String(readdata);

    
  }
  file.close();
}

void readfile2(){
  File file = SPIFFS.open("/test2.txt");
  Serial.println(file);
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }

 while(file.available()>0){
    char dataget = (char)file.read();
    getdata += String(dataget);

  }
  file.close();
}

void writefile(){
  File file = SPIFFS.open("/test.txt", FILE_WRITE);
  if (file.print(dataread)) {
    Serial.println("File was written : ");
    Serial.println(dataread);
  } else {
    Serial.println("File write failed");
    file.close();
    writefile();
  }
  file.close();
}

void writefile2(){
  File file = SPIFFS.open("/test2.txt", FILE_WRITE);
  if (file.print(getdata)) {
    Serial.println("File was written : ");
    Serial.println(getdata);
  } else {
    Serial.println("File write failed");
    file.close();
    writefile2();
  }
  file.close();
}
void delfile(){
  SPIFFS.remove("/test.txt");

  dataread = "";

  
}

void delfile2(){

  SPIFFS.remove("/test2.txt");

  getdata="";
  
}
