#include <WiFi.h>

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

WiFiServer server(80);

char start = 0;
// Variable to store the HTTP request
String header;

void setup() {
  Serial.begin(115200);
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) { // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = ""; // make a String to hold incoming data from the client
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read();
        Serial.print(c);
      }
    }
      client.stop();
      Serial.println("Client disconnected.");
      Serial.println("");
  }
}
