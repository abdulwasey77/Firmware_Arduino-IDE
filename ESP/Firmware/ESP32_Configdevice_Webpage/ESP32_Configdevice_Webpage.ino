#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
    String esp32;
    String cc3200;
    String arduino1;
    String Stringesp32;
    String Stringcc3200;
    String Stringarduino1;
const char* ssid = "esp8266wifi";  // Enter SSID here
const char* password = "12345678";
ESP8266WebServer server(80);
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  // put your setup code here, to run once:
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP); 
  server.on("/", handle_OnConnect);
  server.on("/get",textbox);
  server.onNotFound(handle_NotFound);
  server.begin();
}

void loop() {
  server.handleClient();
  // put your main code here, to run repeatedly:

}
void textbox()
{
    Stringesp32 =server.arg("ESP32");
    Stringcc3200 =server.arg("CC3200");
    Stringarduino1 =server.arg("ARDUINO");
    if(Stringesp32!=""){
  esp32=Stringesp32;
    }
        if(Stringcc3200!=""){
      cc3200=Stringcc3200;
    }
        if(Stringarduino1!=""){
      arduino1=Stringarduino1;
    }
    server.send(200, "text/html", HtmlString());
}
void handle_OnConnect()
{

  server.send(200, "text/html", HtmlString());
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String HtmlString(){
  String html ="<!DOCTYPE html> <html> <head> <style> table, th, td { border: 1px solid black; border-collapse: collapse; } th, td { padding: 5px; text-align: center; } #t01 th { background-color: black; color: white; } #t01 td { background-color: Red; color: white; } </style> </head> <body>\n";
  html += "<table style=\"width:100%\"> <table id=\"t01\"> <caption><h2>Device Table</h2></caption> <tr> <th>Device Name</th> <th>Status</th> <th>Input</th> </tr> <tr>\n";
  html += "<td>ESP32</td>\n";
  html += "<td>\n";
  html += esp32;
  html += "</td>\n"; 
  html += "<form action=\"/get\"> <td> <input type=\"text\" name=\"ESP32\">\n";
  html += "<input type=\"submit\" value=\"Submit\"></td> </form> \n";
  html += "</tr> <tr> <td>CC3200</td>\n";
  html += "<td>\n";
  html += cc3200;
  html += "</td>\n";
  html += "<form action=\"/get\"> <td> <input type=\"text\" name=\"CC3200\">\n";
  html += "<input type=\"submit\" value=\"Submit\"></td> </form> \n";
  html += "</tr> <tr> <td>Arduino</td>\n";
  html += "<td>\n";
  html += arduino1;
  html += "</td>\n";
  html += "<form action=\"/get\"> <td> <input type=\"text\" name=\"ARDUINO\">\n";
  html += "<input type=\"submit\" value=\"Submit\"></td> </form> \n";
  html += "</tr> </table> </body> </html>";
  return html;
}
