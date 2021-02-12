
#include <WiFi.h>
#include <PubSubClient.h>

#define BUILTIN_LED 13
const char* ssid = "I-Tech-Router";
const char* password = "0512303189T";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
char datarec[40];
String datanew;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
   datarec[i]=payload[i];
  }
  Serial.println(datarec);
  datanew=String(datarec);
  Serial.print("String: "); Serial.println(datanew);

  // Switch on the LED if an 1 was received as first character
  if (datanew == "HIGH") {
    digitalWrite(BUILTIN_LED, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("LED: ");
    Serial.println("HIGH");
    client.publish("CC32ESP_OUT", "LED is HIGH");
      for (int i = 0; i < 40; i++) {
   datarec[i]=0;
  }
    
  } if(datanew == "LOW") {
    digitalWrite(BUILTIN_LED, LOW);  // Turn the LED off by making the voltage HIGH
    Serial.print("LED: ");
    Serial.println("LOW");
    client.publish("CC32ESP_OUT", "LED is LOW");
         for (int i = 0; i < 40; i++) {
   datarec[i]=0;
  }

    } if(datanew == "TOGGLE") {
    // delay(500); 
    if(digitalRead(BUILTIN_LED)==HIGH){
      // Turn the LED off by making the voltage HIGH
      digitalWrite(BUILTIN_LED,LOW);
      client.publish("CC32ESP_OUT", "LED is LOW");
    }else if(digitalRead(BUILTIN_LED)==LOW){
            digitalWrite(BUILTIN_LED, HIGH);
      client.publish("CC32ESP_OUT", "LED is HIGH");
    }
         for (int i = 0; i < 40; i++) {
   datarec[i]=0;
  }
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("CC32ESP_IN");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
