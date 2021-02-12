#include <SoftwareSerial.h>
#define RX 10
#define TX 11
String ssid_Sta = "I-Tech-Router";        //  SSID Station
String password_Sta = "0512303189T";      //  PASSWORD Station

String ssid_AP = "ESP8266Mod";        //  SSID Station
String password_AP = "espconnect";      //  PASSWORD Station

String API = "GDKZYY76S4G4HLQX";          //  API Key
String HOST = "api.thingspeak.com";       //  Host where to post data
String PORT = "80";                       //  Server port
int countTrueCommand;
int countTimeCommand; 
boolean found = false;

SoftwareSerial esp8266(RX,TX); 
 
  
void setup() {
  Serial.begin(9600);
  esp8266.begin(9600);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=2",5,"OK");
  sendCommand("AT+CWSAP=\""+ssid_AP+"\",\""+password_AP+"\",1,4",20,"OK");  //ApMode
  sendCommand("AT+CWLIF",5,"OK");
  sendCommand("AT+CIPAP?",5,"OK");
  sendCommand("AT+CIPMUX=1",5,"OK");
  sendCommand("AT+CIPSERVER=1,80",5,"OK");

  
 // sendCommand("AT+CWJAP=\""+ssid_Sta+"\",\""+password_Sta+"\"",20,"OK");  //StationMode
  
}
void loop() {
if(esp8266.find(":"))//ok
    {
         if ( esp8266.available() )   {  Serial.write( esp8266.read() );  }
      
    }

// String getData = "GET /update?api_key="+ API + "&field1=" + String(random(10))+ "&field2=" + String(random(10,21))+ "&field3=" + String(random(20,31))+ "&field4=" + String(random(30,41));
// sendCommand("AT+CIPMUX=1",5,"OK");
// sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
// sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
// esp8266.println(getData);delay(3000);countTrueCommand++;
// sendCommand("AT+CIPCLOSE=0",5,"OK");
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("PASS");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
