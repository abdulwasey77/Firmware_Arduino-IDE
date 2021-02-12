#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
#include "SPIFFS.h"
#include "time.h"

//-----------------define------------------//
#define DHTPIN 2
#define DHTTYPE DHT22
#define Battery 34
#define CartLock 25
#define CartFlooded 26
#define CartPanFlooded  27
#define Relay 14

//-----------------int----------------------//
int Flagdel = LOW;
int FlagSSID = LOW;
int Battvalue;
int Battperct;
int WiFiperct;
int btnpress=0;
int GMTint;
int checkmillis = 1;
int countcheck = 1;
const int   daylightOffset_sec = 0;

//-----------------float---------------------//
float GMTfloat;

//------------------long---------------------//
unsigned long startMillis = 0;
unsigned long previousmillis = 0;
const long  gmtOffset_sec = 3600*5;

//------------------char--------------------//
const char* ssid_PD     = "I-Tech-Router";
const char* password_PD = "0512303189T";
const char* ssid_AP = "ESP_in_APmode";
const char* password_AP = "1234567890";
const char* ssid_STA = "";
const char* password_STA = "";
const char* ntpServer = "pool.ntp.org";

//------------------Strings----------------//
String macRead;
String sendRead;
String pressure;
String ConfigFlashParam;
String ssid;
String password;
String CoustomerID;
String CountryCode;
String TimeZone;
String CartLockStatus;
String CartFloodedStatus;
String CartPanFloodedStatus;
String RelayStatus;
String webpage = "";
String Argument_Name;
String ccSSID;
String ccPassword;
String ccID;
String ccTimeZone;
String ccCountry;
String timeset;
String senddata;


WebServer server(80);
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
//------------------------------------------------------setup---------------------------------//
void setup() {
  Serial.begin(115200);
  pinMode(Battery, INPUT);
  pinMode(CartLock,INPUT);
  pinMode(CartFlooded,INPUT);
  pinMode(CartPanFlooded,INPUT);
  pinMode(Relay,OUTPUT);

  dht.begin();
//  if (!bmp.begin()) {
//  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
//  while (1) {}
//  }
  if (!SPIFFS.begin(true)) {
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
  }

  WiFi.mode(WIFI_AP_STA);
  APconnect();
  server.begin();
  Serial.println ("Go to 192.168.4.1 to config ESP32");
  server.on("/",sendStr);
  readfile();
  Serial.println(ConfigFlashParam);
  if(ConfigFlashParam[0]=='$'){
  Serial.print("in [0]==$  ");
  Serial.println(ConfigFlashParam[0]);
  StationConnect();
  }
}

//-------------------------------------------------------loop------------------------------------//
void loop() {
    server.handleClient();
    if(FlagSSID == HIGH && Flagdel == HIGH){
    StationConnect();
    FlagSSID = LOW;
    Flagdel = LOW;
    }
    if(checkmillis==1){
    startMillis = millis();
    checkmillis = 0;
  }
  if(millis()-startMillis >= 5000){
    checkmillis = 1;
    server.handleClient();
    BattLevelCheck();
    getMacAddress();
    LocalTime();
    WiFiStrenghtInprcnt();
    readInputStatus();
    JSONString();
    Serial.println(senddata);
    //pressure = String(bmp.readPressure()/248.84);
    
    }
}
//-----------------------------------------Wifi Modes----------------------------------//
void APconnect(){
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid_AP, password_AP);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
} 


void StationConnect(){
  CheckingSsidPass();
  WiFi.disconnect();
  delay(10);
  WiFi.disconnect();
  Serial.print("connnecting to SSID : ");
  Serial.println(ssid_STA);
  Serial.print("with Password : ");
  Serial.println(password_STA);
  
  WiFi.begin(ssid_STA,password_STA);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    server.handleClient();
    if(countcheck==1){
      previousmillis = millis();
      countcheck=0;
    }
    if(millis()- previousmillis >= 60000){
      countcheck = 1;
      break;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);  
  LocalTime();
} 



//---------------------------------------ESP webpage config-------------------------------------//
void sendStr(){
  webpage =  "<html>";
  webpage += "<head><title>ESP32 config</title>";
  webpage += "<style>";
  webpage += "body { background-color:powderblue; font-family: Arial; Color: black;}";

  webpage +="table, th, td {\n";
  webpage +="border: 1px solid black;\n";
  webpage +="border-collapse: collapse;\n";
  webpage +="}\n";
  webpage += "</style>";
  webpage += "</head>";

  webpage += "<body>";
  webpage += "<h2>ESP32 device Configuration</h2>";  
  webpage +="<table style=\"width:25%\">";
  webpage += "<form action='http://192.168.4.1' method='POST'>";

  webpage += "<tr>\n";
  webpage += "<td>SSID</td>\n";
  webpage += "<td> <input type=\"text\" name=\"SSID\" style=\"text-align: left;\"></td>\n";
  webpage += "</tr>\n";
  webpage += "<tr>\n";
  webpage += "<td>PASSWORD</td>\n";
  webpage += "<td> <input type=\"text\" name=\"PASSWORD\" style=\"text-align: left;\"></td>\n";
  webpage += "</tr>\n";
  webpage += "<tr>\n";
  webpage += "<td>ccID</td>\n";
  webpage += "<td> <input type=\"text\" name=\"ccID\" style=\"text-align: left;\"></td>\n";
  webpage += "</tr>\n";
  webpage += "<tr>\n";
  webpage += "<td>ccTimeZone</td>\n";
  webpage += "<td> <input type=\"text\" name=\"ccTimeZone\" style=\"text-align: left;\"></td>\n";
  webpage += "</tr>\n";
  webpage += "<tr>\n";
  webpage += "<td>ccCountry</td>\n";
  webpage += "<td> <input type=\"text\" name=\"ccCountry\" style=\"text-align: left;\"></td>\n";
  webpage += "</tr>\n";

  ///Row Submit
  webpage  +="<form action=\"/get\">";
  webpage += "</table>\n";
  webpage += "<input type='submit' value='Submit'>"; // omit <input type='submit' value='Enter'> for just 'enter'
  webpage += "</form>";
  webpage += "</body>";
  webpage += "</html>";

  server.send(200, "text/html", webpage);
  if (server.args() > 0 ) { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Argument_Name = server.argName(i);
      if (server.argName(i) == "SSID") {
        if((server.arg(i)!=0)){
        ccSSID=server.arg(i);
        FlagSSID = HIGH;
        delfile();
        }
        Serial.print("SSID : ");
        Serial.println(server.arg(i));
     }
      if (server.argName(i) == "PASSWORD") {
        if((server.arg(i)!=0)){
        ccPassword=server.arg(i);
        }
        Serial.print("PASSWORD : ");
        Serial.println(server.arg(i));
     }
      if (server.argName(i) == "ccID") {
        if((server.arg(i)!=0)){
        ccID=server.arg(i);
        }
        Serial.print("ccID : ");
        Serial.println(server.arg(i));
     }
      if (server.argName(i) == "ccTimeZone") {
        if((server.arg(i)!=0)){
        ccTimeZone=server.arg(i);
        }
        Serial.print("ccTimeZone : ");
        Serial.println(server.arg(i));
     }
      if (server.argName(i) == "ccCountry") {
        if((server.arg(i)!=0)){
        ccCountry=server.arg(i);
        }
        Serial.print("ccCountry : ");
        Serial.println(server.arg(i));
     }
    }
   }
   combineConfigFlashParam();
   writefile();
  }

//-------------------------------combine ConfigFlashParam------------------------------------//
void combineConfigFlashParam(){
  ConfigFlashParam = '$'+ccSSID+','+ccPassword+','+ccID+','+ccTimeZone+','+ccCountry+'*'; 
  Serial.print("data combined new string is : ");
  Serial.println(ConfigFlashParam);
  }
//----------------------SSID check and convert it into char----------------------------------------//
    
void CheckingSsidPass(){
    //if(ConfigFlashParam[ConfigFlashParam.length()=='*'])
    //if (ConfigFlashParam.startsWith("$") && ConfigFlashParam.endsWith("*") ) {
      int posHeader = ConfigFlashParam.indexOf('$');
      int posTail = ConfigFlashParam.indexOf('*');
      if (posHeader == 0) { // Got "$"
        //Serial.println(ConfigFlashParam);
        int posComma1 = ConfigFlashParam.indexOf(',');
        int posComma2 = ConfigFlashParam.indexOf(',' , posComma1 + 1);
        int posComma3 = ConfigFlashParam.indexOf(',' , posComma2 + 1);
        int posComma4 = ConfigFlashParam.indexOf(',' , posComma3 + 1);

        //string strA = strB.substring(to,from);
        ssid = ConfigFlashParam.substring((posComma1),posHeader+1);
        password = ConfigFlashParam.substring((posComma2),posComma1+1);
        CoustomerID = ConfigFlashParam.substring((posComma3),posComma2+1);
        CountryCode = ConfigFlashParam.substring((posComma4),posComma3+1);
        TimeZone = ConfigFlashParam.substring((posTail),posComma4+1);     
       }
       if(ConfigFlashParam!=0){
       //length of password string
        
        ssid_STA = ssid.c_str();                   
        password_STA = password.c_str();
        Serial.print("SSID STA : ");
        Serial.println(ssid_STA);
        Serial.print("Password STA : ");
        Serial.println(password_STA); 
        Serial.print("CoustomerID : ");
        Serial.println(CoustomerID);
        Serial.print("CountryCode : ");
        Serial.println(CountryCode);        
        Serial.print("TimeZone : ");
        Serial.println(TimeZone);

  } 
}
//-------------------------------------------SPIFFS read write del---------------------------//

void readfile(){
  File file = SPIFFS.open("/test.txt");
  Serial.println(file);
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }

 while(file.available()){
    char readdata = (char)file.read();
    ConfigFlashParam += String(readdata);
  }
  file.close();
}

void writefile(){
  File file = SPIFFS.open("/test.txt", FILE_WRITE);
  if (file.print(ConfigFlashParam)) {
    Serial.println("File was written : ");
    Serial.println(ConfigFlashParam);
  } else {
    Serial.println("File write failed");
  }
  file.close();
}

void delfile(){
  SPIFFS.remove("/test.txt");
  ConfigFlashParam = "";
  Flagdel = HIGH;
}

//------------------------------------------Get Macaddress---------------------------------//

void getMacAddress(){         
  byte mac[6];
  WiFi.macAddress(mac);
  macRead = String(mac[5],HEX);
  macRead += ":";
  macRead += String(mac[4],HEX);
  macRead += ":";
  macRead += String(mac[3],HEX);
  macRead += ":";
  macRead += String(mac[2],HEX);
  macRead += ":";
  macRead += String(mac[1],HEX);
  macRead += ":";
  macRead += String(mac[0],HEX);
}

//-----------------------------Get Value from DHT22 and convert it into String-------------------------------//


String getDHT22humidity(){
  float h = dht.readHumidity();
  String sh=String(h);
  return sh;
}
String getDHT22temperature(){
  float t = dht.readTemperature();
  String st=String(t);
  return st;
}

//-----------------------------------Call JSON String Function-----------------------//

void JSONString(){  
  senddata = "{\"ccCatID\":\""; 
  senddata+= macRead;
  senddata += "\",\"ccCustomerID\":\"";
  senddata += CoustomerID;
  senddata += "\",\"ccCountryCode\":\"";
  senddata += CountryCode;
  senddata += "\",\"ccTimeZone\":\"";
  senddata += TimeZone;
  senddata += "\",\"ccTimeStamp\":\"";
  senddata += timeset;
  senddata += "\",\"ccTempC\":\"";
  senddata += getDHT22temperature();  
  senddata += "\",\"ccRH\":\"";
  senddata += getDHT22humidity();
  senddata += "\",\"ccBMP\":\"";
  senddata += pressure;
  senddata += "\",\"ccCartLock\":\"";
  senddata += CartLockStatus;
  senddata += "\",\"ccCartFlooded\":\"";
  senddata += CartFloodedStatus;
  senddata += "\",\"ccCartPanFlooded\":\"";
  senddata += CartPanFloodedStatus;
  senddata += "\",\"ccRelayOn\":\"";
  senddata += "unknown";
  senddata += "\",\"ccWifi\":\"";
  senddata += String(WiFiperct);
  senddata += "\",\"ccMalfunction\":\"";
  senddata += "unknown";
  senddata += "\",\"ccBattLevel\":\"";
  senddata += String(Battperct);
  senddata += "\",\"ccTimeCartChange\":\"";
  senddata += "not defined";
  senddata += "\",\"ccMessage\":\"";
  senddata += "not defined";
  senddata += "\"}";
}

//-----------------------------------WiFi strength in percentage---------------------//

void WiFiStrenghtInprcnt(){
// to understand what's going on here go to
//https://stackoverflow.com/questions/15797920/how-to-convert-wifi-signal-strength-from-quality-percent-to-rssi-dbm
//https://www.adriangranados.com/blog/dbm-to-percent-conversion
    long rssi = WiFi.RSSI();
    rssi=-rssi;
    if(rssi==0){
      }
    else if (rssi<27&&rssi!=0){
    WiFiperct =100;
    }
    else if(rssi>=27&&rssi<33){
      WiFiperct=150-(5/2.7)*rssi;
    }
    else if(rssi>=33&&rssi<36){
      WiFiperct=150-(5/3)*rssi;
    }
    else if(rssi>=36&&rssi<40){
      WiFiperct=150-(5/3.3)*rssi;
    }
    else if(rssi>=40&&rssi<90){
      WiFiperct=150-(5/3.5)*rssi;
    }
    else if(rssi>=90&&rssi<99){
      WiFiperct=150-(5/3.3)*rssi;
    }
}

//-----------------------------Check Battery level Function-----------------------//


void BattLevelCheck(){
    Battvalue=0;
    for(int i=0;i<100;i++){
    Battvalue =Battvalue+analogRead(Battery);
    delay(10);
  }
  Battvalue=Battvalue/100;
  if (Battvalue >= 3400 && Battvalue <= 4100){
    Battperct= Battvalue-4100;
    Battperct=Battperct+700;
    Battperct =(Battperct*100)/700;
  }
  else if(Battvalue>4100) {
    Battperct=100;
  }
    else{
  Battperct=0;
  
      }
}

//-------------------------------------Read INPUT pins status---------------------------//
void readInputStatus(){
  if(digitalRead(CartLock) == HIGH){
    CartLockStatus = "Yes";
  }else{
    CartLockStatus = "No";
  }
    if(digitalRead(CartFlooded) == HIGH){
    CartFloodedStatus = "Yes";
  }else{
    CartFloodedStatus = "No";
  }
    if(digitalRead(CartPanFlooded) == HIGH){
    CartPanFloodedStatus = "Yes";
  }else{
    CartPanFloodedStatus = "No";
  }
}

//------------------------------------print local time-----------------------------------//
void LocalTime()
{
  time_t rawtime;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
   return;
  }
  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  //print like "const char*"
  //Serial.println(timeStringBuff);

  //Optional: Construct String object 
  timeset = String(timeStringBuff);
}
