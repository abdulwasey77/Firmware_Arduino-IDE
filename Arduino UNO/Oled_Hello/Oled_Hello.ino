#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define incPin  2
#define decPin  3
#define MosfetPin  6
#define ReadswtichPin  4
#define OutPin  5

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int incBtnState = 1;
int decBtnState = 1;
int count_incBtn=0;
int count_decBtn=0;
unsigned int timer_count=0;
unsigned timer;
int displaytimer=0;
uint16_t hours;
uint8_t minutes;
uint8_t seconds;

unsigned long lastDBtime_incBtn=0;
unsigned long lastDBtime_decBtn=0;
unsigned long Onesecmillis=0;
int flagtimer=0;
int startflag=0;
String showseconds;
String showminutes;
String showhours;

void setup() {
  Serial.begin(9600);
  pinMode(incPin,INPUT_PULLUP);
  pinMode(decPin,INPUT_PULLUP);
  pinMode(ReadswtichPin,INPUT_PULLUP); //on LOW start timer
  pinMode(MosfetPin,OUTPUT); //on disconnect pin low   & nornally pin high
  pinMode(OutPin,OUTPUT); //when timer ends low
  pinMode(ReadswtichPin,INPUT_PULLUP);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  //delay(2000);
  display.setFont(&FreeSerif9pt7b);
  display.clearDisplay();
  display.setTextSize(2);             
  display.setTextColor(WHITE);                
  attachInterrupt(digitalPinToInterrupt(incPin), incBtn, CHANGE);
  attachInterrupt(digitalPinToInterrupt(decPin), decBtn, CHANGE);
  //delay(2000); 
}
void loop() {
  Increment();
  Decrement();
  timercal();
  if(displaytimer<=0){
    startflag=0;
  }
  if(startflag==0){
  digitalWrite(MosfetPin,LOW);
  digitalWrite(OutPin,LOW);
  }
  if(digitalRead(ReadswtichPin)==LOW){
    startflag=1;
    digitalWrite(MosfetPin,HIGH);
    digitalWrite(OutPin,HIGH);
  }
  if(flagtimer==0&&startflag==1){
    Onesecmillis=millis();
    flagtimer=1;
  }
  if(millis()-Onesecmillis>=1000&&startflag==1){
  flagtimer=0;
  displaytimer--; 
  }
}

void Increment(){
  if(incBtnState==0 && millis()-lastDBtime_incBtn >= 100){
    lastDBtime_incBtn=0;
    incBtnState=1;
    display.clearDisplay(); 
    displaytimer=displaytimer+30;
  }
}

void Decrement(){
    if(decBtnState==0 && millis()-lastDBtime_decBtn >= 100){
    lastDBtime_decBtn=0;
    decBtnState=1;
    display.clearDisplay();
    Serial.print("displaytimer: " ); Serial.println(displaytimer); 
    if(displaytimer>=30){
    displaytimer=displaytimer-30;
    }else
    displaytimer=0;
    startflag=0;
  }
}
void incBtn(){

  incBtnState = digitalRead(incPin);
  lastDBtime_incBtn= millis();
} 

void decBtn(){

  decBtnState = digitalRead(decPin);
  lastDBtime_decBtn= millis();
} 

void timercal(){
  if(displaytimer>=0){
    timer=displaytimer;
    seconds = timer % 60;
    timer = (timer - seconds)/60;
    minutes = timer % 60;
    timer = (timer - minutes)/60;
    hours = timer;
    
    showseconds=String(seconds);
    showminutes=String(minutes);
    showhours=String(hours);
    
    if(seconds<=9){
      showseconds="0";
      showseconds+=String(seconds);
    }
    if(minutes<=9){
      showminutes="0";
      showminutes+=String(minutes);
    }
    if(hours<=9){
      showhours="0";
      showhours+=String(hours);
    }
    String showtime=showhours;
    showtime+=":";
    showtime+=showminutes;
    showtime+=":";
    showtime+=showseconds;
    
    //Serial.println(showtime);
    display.clearDisplay();                
    display.setCursor(0,45);
    display.println(showtime);
    display.display();   
  }
}
