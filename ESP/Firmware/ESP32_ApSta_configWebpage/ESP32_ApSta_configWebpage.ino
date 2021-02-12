/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
//#include <WiFiAP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "ESP_in_APmode";
const char *password = "1234567890";

const char *ssid_PD     = "I-Tech-Router"; // the ssid/name of the wifi, the esp will be connected to
const char *password_PD = "0512303189T"; // the password of that wifi

const char *ssid_STA; 
const char *password_STA;

String webpage = "";
String Argument_Name;
String ccSSID;
String ccPassword;
String ccID;
String ccTimeZone;
String ccCountry;

int FlagSSID = LOW;
ESP8266WebServer server(80);


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_AP_STA);
  APconnect();
  server.begin();
  Serial.println ("Go to 192.168.4.1 to config ESP32");
  server.on("/",sendStr);
}

void loop() {
  
  server.handleClient();
  if(FlagSSID == HIGH){
    StationConnect();
    FlagSSID = LOW;
  }
  
}

void APconnect(){
  
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
} 


void StationConnect(){
  WiFi.disconnect();
  delay(10);
  WiFi.disconnect();
  ssid_STA = ccSSID.c_str();
  password_STA = ccPassword.c_str();
  Serial.print("connnecting to SSID : ");
  Serial.println(ssid_STA);
  Serial.print("with Password : ");
  Serial.println(password_STA);
  
  WiFi.begin(ssid_STA,password_STA);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   
  
} 

void sendStr(){
webpage =  "<html>";
webpage += "<head><title>ESP32 Config</title>";
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

        if((server.arg(i)!=0))
        {
        ccSSID=server.arg(i);
         FlagSSID = HIGH;
        }
        Serial.print("SSID : ");
        Serial.println(server.arg(i));
     }
      if (server.argName(i) == "PASSWORD") {

        if((server.arg(i)!=0))
        {
        ccPassword=server.arg(i);
        
        }
        Serial.print("PASSWORD : ");
        Serial.println(server.arg(i));
     }
      if (server.argName(i) == "ccID") {

        if((server.arg(i)!=0))
        {
        ccID=server.arg(i);
        
        }
        Serial.print("ccID : ");
        Serial.println(server.arg(i));
     }
      if (server.argName(i) == "ccTimeZone") {

        if((server.arg(i)!=0))
        {
        ccTimeZone=server.arg(i);
        
        }
        Serial.print("ccTimeZone : ");
        Serial.println(server.arg(i));
     }
      if (server.argName(i) == "ccCountry") {

        if((server.arg(i)!=0))
        {
        ccCountry=server.arg(i);
        
        }
        Serial.print("ccCountry : ");
        Serial.println(server.arg(i));
     }

     
    }
   }  
  }
