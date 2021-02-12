 #include <WiFi.h>
 #include <WebServer.h>
#include <HTTPClient.h>

const char *ssid = "Master_thinkspeak";
const char *password = "master1234";

const char *ssid_STA     = "I-Tech-Router"; // the ssid/name of the wifi, the esp will be connected to
const char *password_STA = "0512303189T"; // the password of that wifi



// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update";
// Service API Key
String apiKey = "GDKZYY76S4G4HLQX";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Set timer to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Timer set to 10 seconds (10000)
unsigned long timerDelay = 10000;
WebServer server(80);
float Sensor_Value = 0.0;

void setup() {
  Serial.begin(115200);
  //WiFi.mode(WIFI_AP_STA);
  
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/",handleIndex);
  server.on("/update",handleUpdate);
  server.begin(); 
    //station part
//  Serial.print("connecting to...");
//  Serial.println(ssid_STA);
//
//  WiFi.begin(ssid_STA,password_STA);
//
//  while(WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.print("Connected to WiFi network with IP Address: ");
//  Serial.println(WiFi.localIP());

}

void loop() {
  
server.handleClient();
   
//  if ((millis() - lastTime) > timerDelay) {
//    //Check WiFi connection status
//    if(WiFi.status()== WL_CONNECTED){
//      HTTPClient http;
//      http.begin(serverName);
//      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(random(10))+ "&field2=" + String(random(10,21))+ "&field3=" + String(random(20,31))+ "&field4=" + String(random(30,41));           
//      http.POST(httpRequestData);
//      http.end();
//    }
//    else {
//      Serial.println("WiFi Disconnected");
//    }
//    lastTime = millis();
//  }
}

void handleIndex(){
  server.send(200,"text/plain",String(Sensor_Value));
}
void handleUpdate(){
  Sensor_Value = server.arg("value").toFloat();
  Serial.println(Sensor_Value);
  server.send(200,"text/plain","Updated");
}
