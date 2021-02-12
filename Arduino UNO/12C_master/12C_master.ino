#include <Wire.h>
String RecData="";
char c=0;
  unsigned long temptime;
  unsigned long humtime;
  unsigned long presstime;
  
  int pressflag=0;
  int tempflag=0;
  int humflag=0;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {

  if(tempflag==0){
  temptime = millis();
  tempflag=1;
  }
  if(millis()-temptime > 9000){
    tempflag=0;
  String temp="Temperature:";
  Wire.beginTransmission(8);
  Wire.write(temp.c_str());
  Wire.endTransmission(); 
  delay(1000);
  Wire.requestFrom(8,8);    // request 6 bytes from slave device #8
  while (Wire.available() && c!='A') { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
    RecData+=c;
  }
  c=0;
  Serial.print("DATA: "); Serial.println(RecData);
  int T=RecData.indexOf('T');
  int A=RecData.indexOf('A');
  if(RecData[T]=="T"){
  RecData[T]=0;
  RecData[A]=0;
  Serial.print("Temperature: "); Serial.println(RecData);
  }
  RecData="";
  }

  if(humflag==0){
  humtime = millis();
  humflag=1;
  }
  if(millis()-humtime > 15000){
    humflag=0;
  String hum="Humidity:";
  Wire.beginTransmission(8);
  Wire.write(hum.c_str());
  Wire.endTransmission(); 
  delay(1000);
  Wire.requestFrom(8,20);    // request 6 bytes from slave device #8
  while (Wire.available() && c!='B') { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
    RecData+=c;
  }
  c=0;
  Serial.print("DATA: "); Serial.println(RecData);
  int H=RecData.indexOf('H');
  int B=RecData.indexOf('B');
  if(RecData[H]=="H"){
  RecData[H]=0;
  RecData[B]=0;
  Serial.print("Humidity: "); Serial.println(RecData);
  }
  RecData="";
  }



  if(pressflag==0){
  presstime = millis();
  pressflag=1;
  }
  if(millis()-presstime > 23000){
    pressflag=0;
  String pres="Pressure:";
  Wire.beginTransmission(8);
  Wire.write(pres.c_str());
  Wire.endTransmission(); 
  delay(1000);
  Wire.requestFrom(8,20);    // request 6 bytes from slave device #8
  while (Wire.available() && c!='C') { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
    RecData+=c;
  }
  c=0;
  Serial.print("DATA: "); Serial.println(RecData);
  int P=RecData.indexOf('P');
  int C=RecData.indexOf('C');
  if(RecData[0]="P"){
  RecData[P]=0;
  RecData[C]=0;
  Serial.print("Pressure: "); Serial.println(RecData);
  }
  RecData="";
  }



}

/*
#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
}

 
 */
