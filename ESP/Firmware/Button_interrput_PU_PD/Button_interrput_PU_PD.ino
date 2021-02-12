int Btn0_count=0;
int Btn1_count=0;
int Btn2_count=0;
int Btn3_count=0;

int Btn0_pin=27;
int Btn1_pin=25;
int Btn2_pin=5;
int Btn3_pin=22;

void setup() {
Serial.begin(9600);
Serial.println("serial started");
pinMode(Btn0_pin,INPUT);
pinMode(Btn1_pin,INPUT);
pinMode(Btn2_pin,INPUT);
pinMode(Btn3_pin,INPUT);  
//attachInterrupt(digitalPinToInterrupt(Btn0_pin), Btn0, CHANGE);
//attachInterrupt(digitalPinToInterrupt(Btn1_pin), Btn1, CHANGE);
//attachInterrupt(digitalPinToInterrupt(Btn2_pin), Btn2, CHANGE);
//attachInterrupt(digitalPinToInterrupt(Btn3_pin), Btn3, CHANGE);

}

void loop() {
Btn2();
}

void Btn0(){
  if(digitalRead(Btn0_pin)== HIGH ){
    Btn0_count++;
    Serial.println(Btn0_count);
    }
}
void Btn1(){
  if(digitalRead(Btn1_pin)== HIGH ){
    Btn1_count++;
    Serial.println(Btn1_count);
    }
}
void Btn2(){
  Serial.println("in btn2");
  Serial.println(digitalRead(Btn2_pin));
  if(digitalRead(Btn2_pin)== HIGH ){
    Btn2_count++;
    Serial.println(Btn2_count);
    }
    delay(3000);
}
void Btn3(){
  if(digitalRead(Btn3_pin)== HIGH ){
    Btn3_count++;
    Serial.println(Btn3_count);
    }
}
