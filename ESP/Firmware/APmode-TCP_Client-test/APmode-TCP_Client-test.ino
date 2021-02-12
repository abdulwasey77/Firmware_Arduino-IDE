#include <WiFi.h>
#include <WiFiAP.h>

const char *ssid = "ESP32_APmode";             
const char *pass = "123456789";
WiFiServer server(80);   

String Data;
bool DataFlag=false;
void setup() {
    Serial.begin(115200);
    Serial.println("Configuring access point...");

    // You can remove the password parameter if you want the AP to be open.
    WiFi.softAP(ssid, pass);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.begin();
  
    Serial.println("Server started");

}

void loop() {
  
  WiFiClient client = server.available();
  if (client) {
  while (client.connected()) {
        while (client.available()) 
        {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);  
        Data+=c;
        DataFlag=true;
        }
        if(DataFlag){
         DataFlag=false; 
        Serial.println();
        client.println(Data);
        Data="";
        }
      }
    client.stop();              
  }
}
