//    1 but start/stop
//    1 but 1 min timer incremet
//    1 but 30 sec timer increment
//    Temp monitor if temp exceed 80 deg auto off
//
//    1 button jo door lock ka hota hai k door lock hai ya nahi 
//
//    Door lock na ho tou system work na kry ... 
//    Or system chalty chalty door open kr dya jaye tou timer jahan hai waheen ruk jaye
#include "DHT.h"
#define DHTPIN 26
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


const int butStart_Stop=13;
const int but_1min=12;
const int but_30sec=14;
const int but_door=27;

int Btn1State = 1;
int Btn2State = 1;
int Btn3State = 1;
int Btn4State = 1;
int count_Btn1=0;
int count_Btn2=0;
int count_Btn3=0;
int count_Btn4=0;
int timer=0;
int showDisplay=1;
int DoorcheckFlag = 1;
int minutes;
int Seconds;
int door=1;

float temperature;

unsigned long lastDBtime_Btn1=0;
unsigned long lastDBtime_Btn2=0;
unsigned long lastDBtime_Btn3=0;
unsigned long lastDBtime_Btn4=0;
unsigned long timerInMillis;
unsigned long timervalue;

String DoorStr="Closed";

void setup() {
  Serial.begin(115200);
  pinMode(butStart_Stop,INPUT_PULLUP);
  pinMode(but_1min,INPUT_PULLUP);
  pinMode(but_30sec,INPUT_PULLUP);
  pinMode(but_door,INPUT_PULLUP);
  dht.begin();
  attachInterrupt(digitalPinToInterrupt(butStart_Stop), Btn1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(but_1min), Btn2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(but_30sec), Btn3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(but_door), Btn4, CHANGE);
  Serial.println("                  Microwave Oven");
}

void loop() {
   temperature = dht.readTemperature();
   if(temperature <= 80){
    DoorCheck();
   }
   else{
    Serial.println("Temperature Warning");
    Serial.print("Current Temperature is : ");
    Serial.print(temperature);
    Serial.println(" *C ");
    delay(3000);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------//

void startStop(){
    if(digitalRead(but_door) == HIGH){
  if(Btn1State == LOW && millis()-lastDBtime_Btn1 >= 100){ 
     lastDBtime_Btn1=0;
     Btn1State=1;
     count_Btn1++;
  }
  if( (count_Btn1 % 2) == 0){
    minuteIncr();
    secIncr();
    DoorcheckFlag = 0;
    
  }else{
    DoorcheckFlag = 1;
   if(timerInMillis == 0){
    timerInMillis = millis();
   }
   if(millis()-timerInMillis >= 1000 && timer >= 1){
    timerInMillis=0;
    timerCount();
    if(showDisplay==1&&timer!=0){
      Serial.println("Timer Started");
      showDisplay=0;
    }
    temperature = dht.readTemperature();
    Serial.print("Timer = "); 
    Serial.print(minutes);
    Serial.print(":");
    Serial.print(Seconds);
    Serial.print("  Temperature = ");
    Serial.print(temperature);
    Serial.print("*C");
    Serial.print("  Door Status = ");
    Serial.println(DoorStr);
    timer--;
    if(timer==0){
      Serial.println("Timer Ended");
      count_Btn1++;
      showDisplay=1;
      }
    }
   }
  }
}

//---------------------------------------------------------------------------------------------------------------------//

void DoorCheck(){
  if(Btn4State==LOW && millis()-lastDBtime_Btn4 >= 150){
  count_Btn4++;
  Btn4State=1;
  lastDBtime_Btn4=0;
  }
   if( (count_Btn4 % 2) == 0){
    DoorStr="Closed";
    if(door==0){
    Serial.print("Door Status = ");
    Serial.println(DoorStr);
    door = 1;
      }
    startStop();
   }else{
   if(DoorcheckFlag == 1){
   count_Btn1++;
   DoorStr="Opened";
   if(door == 1){
    Serial.print("Door Status = ");
    Serial.println(DoorStr);
    door=0;
    }
   DoorcheckFlag=0;
   }
  }
 }

//------------------------------------------------------------------------------------------------------------------//

void Btn1(){
  Btn1State = digitalRead(butStart_Stop);
  lastDBtime_Btn1= millis();
} 

void Btn2(){
  Btn2State = digitalRead(but_1min);
  lastDBtime_Btn2= millis();
} 

void Btn3(){
  Btn3State = digitalRead(but_30sec);
  lastDBtime_Btn3= millis();
} 

void Btn4(){
  Btn4State = digitalRead(but_door);
  lastDBtime_Btn4= millis();
} 

//------------------------------------------------------------------------------------//

void minuteIncr(){
    if(Btn2State == LOW && millis()-lastDBtime_Btn2 >= 150){
      lastDBtime_Btn2=0;
      Btn2State=1;
      count_Btn2++;
      timer=timer+count_Btn2*60+count_Btn3*30;
      timerCount();
    Serial.print("Timer value is set to "); 
    Serial.print(minutes);
    Serial.print(":");
    Serial.println(Seconds);  
      count_Btn2=0;    
      lastDBtime_Btn2=0;
    }
}

void secIncr(){
    if(Btn3State == LOW && millis()-lastDBtime_Btn3 >= 150){
      lastDBtime_Btn3=0;
      Btn3State=1;
      count_Btn3++;
      timer=timer+count_Btn2*60+count_Btn3*30;
      count_Btn3=0;
      timerCount();
    Serial.print("Timer value is set to "); 
    Serial.print(minutes);
    Serial.print(":");
    Serial.println(Seconds);  
      lastDBtime_Btn3=0;
    }  
}

//-----------------------------------------------------------------------------------//

void timerCount(){
      float timernew=float(timer);
      timernew=timernew/60;      
      minutes = timernew;    // no of minutes remaining
      String sec=String(timernew);
      int dot = sec.indexOf('.');
      int endsec = sec.length();
      String readsec = sec.substring(dot ,endsec);
      float readsecF = readsec.toFloat();
      readsecF= readsecF*60;
      Seconds = round(readsecF); // no of seconds remaining
}
