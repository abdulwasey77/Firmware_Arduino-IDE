#include <WiFi.h>
#include <WiFiAP.h>
#include <HTTPClient.h>

char *ssid = "ESP32_server";             
char *pass = "server1234";

char *ssidSTA = "I-Tech-Router";             
char *passSTA = "0512303189T";             
WiFiServer server(80);                   

//IPAddress ip(192,168,4,1);            // IP address of the server
//IPAddress gateway(192,168,4,1);           // gateway of your network
//IPAddress subnet(255,255,255,0);          // subnet mask of your network

void setup() {
  Serial.begin(115200);                 
  WiFi.mode(WIFI_AP_STA); //switching to AP mode
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid, pass);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.print("connecting to...");
  Serial.println(ssidSTA);
  WiFi.begin(ssidSTA,passSTA);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  
  server.begin();                         // starts the server
  Serial.println("Server Started");
}

void loop () {

  WiFiClient client = server.available();
  if (client) {
    Serial.print("Client: "); Serial.println(client);
  if (client.connected()) {
  Serial.println("Client Connected");
  client.println("readvalue\n");  // sends the message to the server
  delay(500);
  String value = client.readStringUntil('\n');   // receives the answer from the sever
  Serial.print("value: ");
  Serial.println(value);
  client.flush();
    }
    client.stop();              
  }
}
