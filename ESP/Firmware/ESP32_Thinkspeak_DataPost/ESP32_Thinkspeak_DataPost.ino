#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "I-Tech-Router";
const char* password = "0512303189T";

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

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 seconds
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData1 = "api_key=" + apiKey + "&field1=" + String(random(10))+ "&field2=" + String(random(10,21))+ "&field3=" + String(random(20,31))+ "&field4=" + String(random(30,41));           
      http.POST(httpRequestData1);

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
