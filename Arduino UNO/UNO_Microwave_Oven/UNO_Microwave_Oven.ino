#include "DHT.h"

#define DHTPIN   8
#define ssPin   10
#define minPin  11
#define secPin  12
#define doorPin 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float temperature;
int   ssCount; 
int   doorCount;
int   minCount=0; 
int   secCount=0; 
int   ssmilliscount = 1;
int   doormilliscount = 1;
int   minmilliscount = 1;
int   secmilliscount = 1;
int   ssbtnpress = 0;
int   doorbtnpress = 0;
int   minbtnpress = 0;
int   secbtnpress = 0;
int   addtime=1;
int   doorcheck=1;
int   starttimer=0;

int   timer;
int   minutes;
int   seconds; 

unsigned long ssmillis;
unsigned long doormillis;
unsigned long minmillis;
unsigned long secmillis;
unsigned long timerInMillis=0;

String DoorStr;

void setup() {
Serial.begin(9600);
pinMode(ssPin,INPUT_PULLUP);
pinMode(minPin,INPUT_PULLUP);
pinMode(secPin,INPUT_PULLUP);
pinMode(doorPin,INPUT_PULLUP);
dht.begin();
Serial.println("--------------Microwave Oven Without Interrupt-------------"); 
}

void loop() {
temperature = dht.readTemperature();
if(temperature <= 80){
  if(doorcheck==1){
    DoorStr = "Door closed";
  }else{
    DoorStr = "Door opened";
  }
  doorOpen();
  if(doorcheck==1){  
  TimerStartStop();
  }
  if(addtime==1){
  TimerOneMin();
  TimerOneSec();
  }
  if(starttimer==1){
    if(timerInMillis == 0){
    timerInMillis = millis();
   }
   if(millis()-timerInMillis >= 1000 && doorcheck==1){
    timerInMillis=0;
    if(timer>0){
         timer--;
//         float ftimer = float(timer);
//         ftimer = ftimer/60;
//         minutes = int(ftimer);
//         float fsec = ftimer-float(minutes);
//         fsec = fsec*60;
//         Serial.println(fsec);
//         seconds = int(fsec);
//         Serial.print("Timer = ");
//         Serial.print(minutes);
//         Serial.print(":");
//         Serial.println(seconds);
      timerCount();
    Serial.print("Timer = "); 
    Serial.print(minutes);
    Serial.print(":");
    Serial.print(seconds);
    Serial.print("  Temperature = ");
    Serial.print(temperature);
    Serial.print("*C");
    Serial.print("  Door Status = ");
    Serial.println(DoorStr);
    }
    if(timer==0){
      addtime=1;
      ssCount++;
      starttimer=0;
      Serial.println("timer stop");
    }
   }
  }
}
else{
      Serial.println("Temperature Warning");
    Serial.print("Current Temperature is : ");
    Serial.print(temperature);
    Serial.println(" *C ");
    delay(3000);
    }
  }

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
      seconds = round(readsecF); // no of seconds remaining
}

void TimerStartStop(){
  while(!digitalRead(ssPin)){
    
    if(ssmilliscount==1){
      ssmillis = millis();
      ssmilliscount=0;
    }
    if(millis()-ssmillis >= 100){
      ssbtnpress = 1;
      }      
 }
  if(ssbtnpress==1){
        ssCount++;
        ssmilliscount = 1;
        ssbtnpress =0 ;
        if((ssCount%2)==0){
          addtime = 1;
          starttimer=0;
          Serial.println("timer stop");
  }
         if((ssCount%2)==1){
          addtime = 0;
          starttimer=1;
  }
 }
}

void TimerOneMin(){
  while(!digitalRead(minPin)){
    
    if(minmilliscount==1){
      minmillis = millis();
      minmilliscount=0;
    }
    if(millis()-minmillis >= 100){
     
      minbtnpress = 1;
      }      
 }
  if(minbtnpress==1){
        minCount++;
        minmilliscount = 1;
        minbtnpress =0 ;
        timer=timer+minCount*60+secCount*30;
        Serial.print("timer value = ");
        Serial.print(timer);
        Serial.println(" seconds");
        minCount--;
       
  }
}

void TimerOneSec(){
  while(!digitalRead(secPin)){
    
    if(secmilliscount==1){
      secmillis = millis();
      secmilliscount=0;
    }
    if(millis()-secmillis >= 100){
     
      secbtnpress = 1;
      }      
 }
  if(secbtnpress==1){
        secCount++;
        secmilliscount = 1;
        secbtnpress =0 ;
        timer=timer+minCount*60+secCount*30;
        Serial.print("timer value = ");
        Serial.print(timer);
        Serial.println(" seconds");
        secCount--;
  }
}

void doorOpen(){
  while(!digitalRead(doorPin)){
    
    if(doormilliscount==1){
      doormillis = millis();
      doormilliscount=0;
    }
    if(millis()-doormillis >= 100){
      //start
      doorbtnpress = 1;
      }      
 }
  if(doorbtnpress==1){
        doorCount++;
        doormilliscount = 1;
        doorbtnpress =0 ;
        if((doorCount%2)==0){
          doorcheck=1;
          Serial.println("door close");
  }
         if((doorCount%2)==1){
         doorcheck=0;
         Serial.println("door open");
  }
 }
}
