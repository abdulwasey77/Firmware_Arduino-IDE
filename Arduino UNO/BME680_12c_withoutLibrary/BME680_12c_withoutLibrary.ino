
#include <Wire.h>

#define BME280_ADDRESS (0x76)

int c = 1;
int written_bytes1 = 0;
int written_bytes2 = 0;
byte transmission_status=255;
uint16_t value;
uint16_t AC6;
uint16_t AC5;
int16_t AC1;
int16_t AC2;
int16_t AC3;
uint16_t AC4;
int16_t AC7;
int16_t B2;
int16_t MB;
int16_t MC;
int16_t MD;
byte busStatus;
uint32_t rawpress;
const uint8_t oss = 3;
int32_t B6,B5,B3,X1,X2,X3,p,UP;
uint32_t B4,B7;

void setup() {

Serial.begin(9600);
Wire.begin();
Serial.println("Conected");
AC1=read_2_bytes(0xAA);
AC2=read_2_bytes(0xAC);
AC3=read_2_bytes(0xAE);
AC4=read_2_bytes(0xB0);
AC5=read_2_bytes(0xB2);
AC6=read_2_bytes(0xB4);
AC7=read_2_bytes(0xB6);
B2=read_2_bytes(0xB8);
MB=read_2_bytes(0xBA);
MC=read_2_bytes(0xBC);
MD=read_2_bytes(0xBE);

Serial.print("AC1 : "); Serial.println(AC1);
Serial.print("AC2 : "); Serial.println(AC2);
Serial.print("AC3 : "); Serial.println(AC3);
Serial.print("AC4 : "); Serial.println(AC4);
Serial.print("AC5 : "); Serial.println(AC5);
Serial.print("AC6 : "); Serial.println(AC6);
Serial.print("B1 : "); Serial.println(AC7);
Serial.print("B2 : "); Serial.println(B2);
Serial.print("MB : "); Serial.println(MB);
Serial.print("MC : "); Serial.println(MC);
Serial.print("MD : "); Serial.println(MD);
}

void loop() {
  
Wire.beginTransmission(0x77);
Wire.write(0xF4);
Wire.write(0x2E);
Wire.endTransmission();


delay(5);  
Wire.beginTransmission(0x77);
written_bytes1=Wire.write(0xF6);
busStatus = Wire.endTransmission();
if (busStatus == 0)
{
  busStatus=1;
 //  Serial.println("Slave is Present!");
   Wire.requestFrom(0x77,2);
  uint16_t value = (Wire.read() << 8) | Wire.read(); 
   Serial.println(value, HEX);
  // Serial.println(value);
  // Serial.println(written_bytes1);
  // Serial.println(written_bytes2);
   long y11=value-AC6;
   long y1=y11*AC5;
  // Serial.print("X1 : "); Serial.println(x1);
   long p15=(pow(2,15));
   y1=y1/p15;
  // Serial.print("x1 : "); Serial.println(x1);
   long y2=(MC)*(pow(2,11))/(y1+MD);
  // Serial.print("X2 : "); Serial.println(x2);
   B5=y1+y2;
  // Serial.print("B5 : "); Serial.println(B5);
   long T=(B5+8)/(pow(2,4));
   float temp=T;
   temp=temp/10;
  // Serial.print("T : "); Serial.println(T);
   Serial.print("Temperature : "); Serial.println(temp);

  Wire.beginTransmission(0x77);
  Wire.write(0xF4);
  Wire.write(0x34+(oss<<6));
  Wire.endTransmission();
  delay(26);
  Wire.beginTransmission(0x77);
  Wire.write(0xF6);
  busStatus = Wire.endTransmission();
  if (busStatus == 0)
  {
  busStatus=1;
   Wire.requestFrom(0x77, 3);      
  if(Wire.available() >= 3)
  {
    rawpress = (((int32_t)Wire.read() << 16) | ((int32_t)Wire.read() << 8) | ((int32_t)Wire.read())) >> (8 - oss);  
  }
  
  Serial.print("Raw press Hex: "); Serial.println(rawpress,HEX);
  Serial.print("Raw press value: "); Serial.println(rawpress);
  }
  B6 = B5 - 4000;
  X1 = ((int32_t)B2 * ((B6 * B6) >> 12)) >> 11;
  X2 = ((int32_t)AC2 * B6) >> 11;
  X3 = X1 + X2;
  B3 = ((((int32_t)AC1 * 4 + X3) << oss) + 2) / 4;
  X1 = ((int32_t)AC3 * B6) >> 13;
  X2 = ((int32_t)AC7 * ((B6 * B6) >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  B4 = ((uint32_t)AC4 * (uint32_t)(X3 + 32768)) >> 15;
  B7 = ((uint32_t)rawpress - B3) * (uint32_t)(50000UL >> oss);
    if (B7 < 0x80000000) {
    p = (B7 * 2) / B4;
  } else {
    p = (B7 / B4) * 2;
  }
  X1 = (p >> 8) * (p >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * p) >> 16;
    Serial.print("pressure = ");
  Serial.println(p);
   delay(3000);
   
}
else
{
   Serial.println("Slave could not be detected!");
   delay(3000);
   while(1);    //wait for ever
  }
}

uint16_t read_2_bytes(uint8_t Address)
{
  uint16_t value;
  Wire.beginTransmission(0x77);         
  Wire.write(Address);                               
  Wire.endTransmission();                         
  Wire.requestFrom(0x77, 2);            
  if(Wire.available() >= 2)
  {
    value = (Wire.read() << 8) | Wire.read();     
  }
  return value;                                   
}










  
//if (c == 1)
//{
//
//delay(1000);
//
////Read address of Chip
//Wire.beginTransmission((uint8_t)0x77);
//written_bytes=Wire.write((uint8_t)0xD0);
//transmission_status=Wire.endTransmission();
//Wire.requestFrom((uint8_t)0x77,(byte)1);
//uint8_t value = Wire.read();
//Serial.println(value, HEX);
//Serial.println(written_bytes);
//Serial.println(transmission_status);
//
//c = 2;
//}


















/*
 
#include <Wire.h>
int ADXLAddress = 0x53; // Device address in which is also included the 8th bit for selecting the mode, read in this case.
#define X_Axis_Register_DATAX0 0x32 // Hexadecima address for the DATAX0 internal register.
#define X_Axis_Register_DATAX1 0x33 // Hexadecima address for the DATAX1 internal register.
#define Power_Register 0x2D // Power Control Register
int X0,X1,X_out;
void setup() {
  Wire.begin(); // Initiate the Wire library
  Serial.begin(9600);
  delay(100);
  // Enable measurement
  Wire.beginTransmission(ADXLAddress);
  Wire.write(Power_Register);
  // Bit D3 High for measuring enable (0000 1000)
  Wire.write(8);  
  Wire.endTransmission();
}
void loop() {
  Wire.beginTransmission(ADXLAddress); // Begin transmission to the Sensor 
  //Ask the particular registers for data
  Wire.write(X_Axis_Register_DATAX0);
  Wire.write(X_Axis_Register_DATAX1);
  
  Wire.endTransmission(); // Ends the transmission and transmits the data from the two registers
  
  Wire.requestFrom(ADXLAddress,2); // Request the transmitted two bytes from the two registers
  
  if(Wire.available()<=2) {  // 
    X0 = Wire.read(); // Reads the data from the register
    X1 = Wire.read();   
  }
  
  Serial.print("X0= ");
  Serial.print(X0);
  Serial.print("   X1= ");
  Serial.println(X1);
}

*/
