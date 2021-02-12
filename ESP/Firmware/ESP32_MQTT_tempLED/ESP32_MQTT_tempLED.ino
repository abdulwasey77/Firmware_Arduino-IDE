
#include <WiFi.h>
#include <PubSubClient.h>

#define BUILTIN_LED 13
#define BUILTIN_LED2 14
#define PWM_LED 12
const char* ssid = "I-Tech-Router";
const char* password = "0512303189T";
const char* mqtt_server = "broker.hivemq.com";
int mqtt_port = 1883;
String clientId = "esp32_40077";
int count;

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8; //Resolution 8, 10, 12, 15

WiFiClient espClient;
PubSubClient client(espClient);

#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
char datarec[40];
String datanew;
long newmillis;

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

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String Message;
  for (int i = 0; i < length; i++) 
  {
   char c = payload[i];
   Message += c;
  }
  Serial.print("Message: "); Serial.println(Message);
  String PWM=Message;
  if(PWM[0]=='{')
  {
    int collon1 = PWM.indexOf(':');
    int collon2 = PWM.indexOf(':',collon1+1);
    int comma = PWM.indexOf(',',collon2+1);
    String brigthness=PWM.substring(comma,collon2+1);
    Serial.println(brigthness);
    int ledPWM=brigthness.toInt();
    float floatPWM =float(ledPWM);
    floatPWM=floatPWM*2.55;
    ledPWM=int(floatPWM);
    Serial.print("PWM value: "); Serial.println(ledPWM);
    ledcWrite(ledChannel,ledPWM);
    delay(500);
  }
  // Switch on the LED if an 1 was received as first character
  if (Message == "HIGH") 
  {
    digitalWrite(BUILTIN_LED, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    Serial.print("LED: ");
    Serial.println("HIGH");
    client.publish("CC32ESP_OUT", "LED is HIGH");
      for (int i = 0; i < 40; i++) 
      {
   Message="";
  }
    
  }
  if(Message == "LOW") {
    digitalWrite(BUILTIN_LED, LOW);  // Turn the LED off by making the voltage HIGH
    Serial.print("LED: ");
    Serial.println("LOW");
    client.publish("CC32ESP_OUT", "LED is LOW");
         for (int i = 0; i < 40; i++) {
   Message="";
  }

    } if(Message== "TOGGLE1") {
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
   Message="";
  }
  }
  if(Message== "TOGGLE2") {
    // delay(500); 
    if(digitalRead(BUILTIN_LED2)==HIGH){
      // Turn the LED off by making the voltage HIGH
      digitalWrite(BUILTIN_LED2,LOW);
      client.publish("CC32ESP_OUT", "LED is LOW");
    }else if(digitalRead(BUILTIN_LED2)==LOW){
            digitalWrite(BUILTIN_LED2, HIGH);
      client.publish("CC32ESP_OUT", "LED is HIGH");
    }
         for (int i = 0; i < 40; i++) {
   Message="";
  }
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    Serial.println(mqtt_server);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
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
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
   pinMode(BUILTIN_LED2, OUTPUT);   
  pinMode(PWM_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO2 to be controlled
  ledcAttachPin(PWM_LED, ledChannel);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if(count==1){
  newmillis =millis();
 count=0;
  }
  if(millis()-newmillis>5000)
  { 
  int random1 = (random(40));
  char str[8];;
  itoa( random1, str, 10 );
  client.publish("CC32ESP_OUT",str);
  count=1;
  }
}
