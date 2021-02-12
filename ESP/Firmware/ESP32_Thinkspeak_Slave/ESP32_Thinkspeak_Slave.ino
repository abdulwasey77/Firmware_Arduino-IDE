#include <WiFi.h>

const char *ssid = "Master_thinkspeak";
const char *password = "master1234";
const char *host = "192.168.4.1";

WiFiClient client;


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to master");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.begin(ssid,password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
   
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());


}

void loop() {
    if(client.connect(host,80)){
      String url = "/update?value=";
      url += String(random(10));
      client.print(String("GET ") + url + "HTTP/1.1\r\n" + "Host: " + host +
      "\r\n" + "Connection: keep-alive\r\n\r\n" );
      Serial.print("url: "); Serial.println(url);
      delay(10);
    } 

while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);
}
//   byte ip[] = { 192,168,4,1 };
//  if(!client.connect(ip,80)){
//        Serial.println("connection failed");
//        return;
//  }
//        String datavalue = String(random(11))+','+String(random(10,21))+','+String(random(20,31))+','+String(random(30,41));
//        char buff[20]; 
//        datavalue.toCharArray(buff,20);
//        Serial.println(buff);
//        server.write(buff,10);
//        Serial.print("While server is here connected and available buff is : ");
//        Serial.println(buff);
//        client.write(buff,20);
//        delay(3000);

}
