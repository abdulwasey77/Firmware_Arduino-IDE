#include <WiFi.h>
#include <WiFiAP.h>
#include <HTTPClient.h>
// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update";
// Service API Key
String apiKey = "GDKZYY76S4G4HLQX";

unsigned long lastTime = 0;
// Set timer to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Timer set to 10 seconds (10000)
unsigned long timerDelay = 10000;

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
  if (client.connected()) {
  Serial.println(".");
  client.println("readvalue?\r");  // sends the message to the server
  delay(500);
  String value = client.readStringUntil('\n');   // receives the answer from the sever
  Serial.print("value: ");
  Serial.println(value);
  client.flush();
        int posComma1 = value.indexOf(',');
        int posComma2 = value.indexOf(',' , posComma1 + 1);
        int posComma3 = value.indexOf(',' , posComma2 + 1);

        String val1 = value.substring(posComma1,0);
        String val2 = value.substring((posComma2),posComma1+1);
        String val3 = value.substring((posComma3),posComma2+1);
        String val4 = value.substring(posComma3+1);

        Serial.print("val1: "); Serial.println(val1);
        Serial.print("val2: "); Serial.println(val2);
        Serial.print("val3: "); Serial.println(val3);
        Serial.print("val4: "); Serial.println(val4);

        if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    Serial.println("millis working");
    if(WiFi.status()== WL_CONNECTED){
      Serial.println("wifi connected");
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData1 = "api_key=" + apiKey + "&field1=" + val1+ "&field2=" + val2+ "&field3=" + val3+ "&field4=" + val4;           
      http.POST(httpRequestData1);

        Serial.print("val1: "); Serial.println(val1);
        Serial.print("val2: "); Serial.println(val2);
        Serial.print("val3: "); Serial.println(val3);
        Serial.print("val4: "); Serial.println(val4);
//      String httpRequestData2 = "api_key=" + apiKey + "&field2=" + String(random(50));           
//      http.POST(httpRequestData2);
//     
//      String httpRequestData3 = "api_key=" + apiKey + "&field3=" + String(random(50));           
//      http.POST(httpRequestData3);
//      
//      String httpRequestData4 = "api_key=" + apiKey + "&field4=" + String(random(50));           
//      http.POST(httpRequestData4);
      

http.end();
      /*
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      // JSON data to send with HTTP POST
      String httpRequestData = "{\"api_key\":\"" + apiKey + "\",\"field1\":\"" + String(random(40)) + "\"}";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);*/
     

    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }   
    }
    client.stop();              
  }
}
