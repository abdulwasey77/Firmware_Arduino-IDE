#include <ESP8266WiFi.h>
String request;
String ClientMac;
String datacheck;
String maccheck;
int value = 0;
char *ssid = "ESP8266_server";             
char *pass = "server1234";  //the password should be 8 char or more
IPAddress server(192,168,4,1);       // the fixed IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Waiting for connection to softAP...");
    delay(500);
  }
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  Serial.println("Connected to Server");
  ClientMac = WiFi.macAddress();
  Serial.println(ClientMac);
  delay(1000);
  client.connect(server, 8080);
}

void loop () {
  
  if(client.available()>=1)
 {
  Serial.println("Connected to Server");
  request = client.readStringUntil('\n');
  if(request!=""){
  Serial.print("request : "); Serial.println(request);
  delay(500);
  int comma = request.indexOf(',');
  maccheck = request.substring(comma,0);
  Serial.print("maccheck : "); Serial.println(maccheck);
  if(maccheck==ClientMac)
  {
    maccheck="";
    int star =request.indexOf('*');
    datacheck = request.substring(star,comma+1);
    Serial.print("datacheck :"); Serial.println(datacheck);
    if(datacheck=="Hello")
    {
        datacheck="";
        Serial.println("in datacheck on");
        String senddata = ClientMac;
        senddata += ",";
        senddata += "Hi";
        senddata += "*";
        client.println(senddata);
        delay(500);
    }
    if(datacheck=="ON")
    {
        datacheck="";
        String senddata = ClientMac;
        senddata += ",";
        senddata += "OFF";
        senddata += "*";
        client.println(senddata);
        delay(500);
      }
         if(datacheck=="Good")
    {
        datacheck="";
        String senddata = ClientMac;
        senddata += ",";
        senddata += "Bad";
        senddata += "*";
        client.println(senddata);
        delay(500);
      }
              if(datacheck=="True")
    {
        datacheck="";
        String senddata = ClientMac;
        senddata += ",";
        senddata += "False";
        senddata += "*";
        client.println(senddata);
        delay(500);
      }
   }
  }
 }
}
