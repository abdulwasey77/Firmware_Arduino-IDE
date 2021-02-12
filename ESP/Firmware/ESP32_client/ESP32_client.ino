#include <WiFi.h>

int value = 0;
char *ssid = "ESP32_server";             
char *pass = "server1234";  //the password should be 8 char or more

IPAddress ip(192,168,4,2);            // set the client's address
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress server(192,168,4,1);       // the fixed IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Waiting for connection to softAP...");
    delay(500);
  }
  Serial.println("Connected to wifi");
}

void loop () {
  String datavalue = String(random(11))+','+String(random(10,21))+','+String(random(20,31))+','+String(random(30,41));
  delay(500);
  client.connect(server, 80);
  Serial.println(".");
  String request = client.readStringUntil('\n');    
  Serial.print("send from client: "); Serial.println(datavalue);
  client.flush();
  client.println(datavalue);
  client.readStringUntil('\n');
    
  
     // Connection to the server
                 
}
