#include <WiFi.h>

const char* ssid     = "I-Tech-Router";
const char* password = "0512303189T";
const int buttonPin = 12;  // the number of the pushbutton pin
int c=0;
unsigned long lastDBtime=0;
int buttonState = 1;

void setup() {
  Serial.begin(115200);  
    WiFi.mode(WIFI_AP_STA);
  Serial.println("Setting AP (Access Point)…");
  WiFi.softAP("esp32_Ap", "123456789");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  Serial.print("connecting to...");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  for (int tr = 0; tr <= 30; tr++)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print("...");
      delay(500);
    }
    else
    {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());

      break;
    }
  }
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(buttonPin), Btn1, CHANGE);

}

void loop() {
  if(buttonState==0 && millis()- lastDBtime >= 200){  
  c++; 
  buttonState=1; 
  Serial.print("count = ");
  Serial.println(c);
  }
 
}

void Btn1(){
  buttonState=digitalRead(buttonPin);
  lastDBtime= millis();
  } 
 
