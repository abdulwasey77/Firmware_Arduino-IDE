/*
  ESP32 Web Server - AP Mode
*/
 
#include <WiFi.h>
#include <WebServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h> 

AsyncWebServer server(80);
// SSID & Password
const char* ssid = "ESP32_APmode";  // Enter your SSID here
const char* password = "123456789";  //Enter your Password here

const char* PARAM_INPUT = "input";


// HTML web page to handle input field
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input: <input type="text" name="input">
    <input type="submit" value="Submit">
  </form><br>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
 
  // Create SoftAP
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
 
 
  
  Serial.println();
  Serial.println();
  Serial.print("SSID :  ");
  Serial.println(ssid);
  Serial.print("Password :  ");
  Serial.println(password);
  Serial.println("IP Address details");
  Serial.print("IP Address :  ");
  Serial.println(IP);

 // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      inputParam = PARAM_INPUT;
    }   
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.onNotFound(notFound);
  server.begin();
}
 
void loop() {
  
}
