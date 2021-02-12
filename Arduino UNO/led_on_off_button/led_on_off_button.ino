unsigned long start;
int button = 1;
int led = 1;
void setup() {

pinMode(12, INPUT_PULLUP);
pinMode(13, OUTPUT);

}

void loop() {
    if(button==1 && digitalRead(12) == LOW)
  {
    start = millis();
    button = 0;
    }
    if(millis()- start >= 200 && digitalRead(12) == LOW){
      button = 1;
       led++;
      if((led%2) == 0){
        digitalWrite(13,HIGH);
      }else{
      digitalWrite(13,LOW);
  }
 }
}
