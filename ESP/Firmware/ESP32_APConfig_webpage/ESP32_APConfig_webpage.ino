#include <WiFi.h>
#include <WebServer.h>

const char* ssid_STA     = "I-Tech-Router";
const char* password_STA = "0512303189T";
const char* ssid = "ESP_in_APmode";
const char* password = "1234567890";
String webpage = "";
String Argument_Name;
String ccSSID;
String ccPassword;
String ccID;
String ccTimeZone;
String ccCountry;

WebServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
    server.begin();
    Serial.println ( "HTTP server started" );
    server.on("/",sendStr);
}

void sendStr(){
webpage =  "<html>";
webpage += "<head><title>Dog Monitor</title>";
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

        if((server.arg(i)!=0))
        {
        ccSSID=server.arg(i);
        
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


void loop(){
 server.handleClient();
}
