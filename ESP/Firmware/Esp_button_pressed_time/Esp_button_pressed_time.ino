
const int buttonPin = 4;  // the number of the pushbutton pin
int c=0;
unsigned long timepress=0;
unsigned long timepress2=0;
unsigned long lastDBtime=0;
// variable for storing the pushbutton status 
int buttonState = 1;

void setup() {
  Serial.begin(115200);  
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), Btn1, CHANGE);

}

void loop() {
  //Serial.println(digitalRead(buttonPin));
  if(buttonState == LOW && millis()- lastDBtime >= 200){
    lastDBtime=0;
    if(timepress==0){
   timepress=millis();
    }
  }
  else if(buttonState == HIGH){
    if(timepress!=0)
      timepress2=millis()-timepress;
      timepress2=timepress2/1000;
    Serial.print("button pressed for : ");
    Serial.print(timepress2);
    Serial.println(" sec");
    }
    timepress=0;
  }
  
 
}

void Btn1(){
  buttonState = digitalRead(buttonPin);
  lastDBtime= millis();
  } 
 
