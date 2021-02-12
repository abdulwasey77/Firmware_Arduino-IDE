#include <LiquidCrystal_I2C.h>
#define Input1 15
#define Input2 32
#define Input3 4
#define Input4 5
#define Input5 18
#define Input6 19
#define Input7 23
#define Input8 25

int lcdColumns = 20;
int lcdRows = 4;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

unsigned long lastDB1=0,lastDB2=0,lastDB3=0,lastDB4=0,lastDB5=0,lastDB6=0,lastDB7=0,lastDB8=0;
unsigned long timer1sec=millis(),timer1min=millis(),timer1hour=millis(),timerInline0=millis();
int btn1State=1,btn2State=1,btn3State=1,btn4State=1,btn5State=1,btn6State=1,btn7State=1,btn8State=1;
int secCont1,secCont2,secCont3,secCont4,secCont5,secCont6,secCont7,secCont8;
int minCont1,minCont2,minCont3,minCont4,minCont5,minCont6,minCont7,minCont8;
int hourCont1,hourCont2,hourCont3,hourCont4,hourCont5,hourCont6,hourCont7,hourCont8;
int Inline0=1;

void setup(){
  Serial.begin(115200);
  pinMode(Input1, INPUT_PULLUP);
  pinMode(Input2, INPUT_PULLUP);
  pinMode(Input3, INPUT_PULLUP);
  pinMode(Input4, INPUT_PULLUP);
  pinMode(Input5, INPUT_PULLUP);
  pinMode(Input6, INPUT_PULLUP);
  pinMode(Input7, INPUT_PULLUP);
  pinMode(Input8, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Input1), Btn1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Input2), Btn2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Input3), Btn3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Input4), Btn4, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Input5), Btn5, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Input6), Btn6, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Input7), Btn7, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Input8), Btn8, CHANGE);
  lcd.init();                     
  lcd.backlight();
}

void loop(){
     if(millis()-timerInline0>5000){
      timerInline0=millis();
      Inline0 = !Inline0;
     }
    ReadBtn();
    showData();
    showDisplay();
}

void Btn1(){
  btn1State = digitalRead(Input1);
  lastDB1= millis();
  } 
void Btn2(){
  btn2State = digitalRead(Input2);
  lastDB2= millis();
  } 
void Btn3(){
  btn3State = digitalRead(Input3);
  lastDB3= millis();
  } 
void Btn4(){
  btn4State = digitalRead(Input4);
  lastDB4= millis();
  } 
void Btn5(){
  btn5State = digitalRead(Input5);
  lastDB5= millis();
  } 
void Btn6(){
  btn6State = digitalRead(Input6);
  lastDB6= millis();
  } 
void Btn7(){
  btn7State = digitalRead(Input7);
  lastDB7= millis();
  }
void Btn8(){
  btn8State = digitalRead(Input8);
  lastDB8= millis();
  }  


void ReadBtn()
{
  if(btn1State == LOW && millis()- lastDB1 >= 50)
  {  
  lastDB1=0;
  btn1State=1;
  Serial.println("Btn1pressed");
  secCont1++;
  }
  if(btn2State == LOW && millis()- lastDB2 >= 50)
  {  
  lastDB2=0;
  btn2State=1;
  Serial.println("Btn2pressed");
  secCont2++;
  }
  if(btn3State == LOW && millis()- lastDB3 >= 50)
  {  
  lastDB3=0;
  btn3State=1;
  Serial.println("Btn3pressed");
  secCont3++;
  }
  if(btn4State == LOW && millis()- lastDB4 >= 50)
  {  
  lastDB4=0;
  btn4State=1;
  Serial.println("Btn4pressed");
  secCont4++;
  }
  if(btn5State == LOW && millis()- lastDB5 >= 50)
  {  
  lastDB5=0;
  btn5State=1;
  Serial.println("Btn5pressed");
  secCont5++;
  }
  if(btn6State == LOW && millis()- lastDB6 >= 50)
  {  
  lastDB6=0;
  btn6State=1;
  Serial.println("Btn6pressed");
  secCont6++;
  }
  if(btn7State == LOW && millis()- lastDB7 >= 50)
  {  
  lastDB7=0;
  btn7State=1;
  Serial.println("Btn7pressed");
  secCont7++;
  }
  if(btn8State == LOW && millis()- lastDB8 >= 50)
  {  
  lastDB8=0;
  btn8State=1;
  Serial.println("Btn8pressed");
  secCont8++;
  }
}


void showDisplay()
{
  lcd.setCursor(0,1);
  lcd.print("Sec");
  lcd.setCursor(0,2);
  lcd.print("Min");
  lcd.setCursor(0,3);
  lcd.print("Hrs");
 if(Inline0)
  {
  lcd.setCursor(4,0);
  lcd.print("In1");
  lcd.setCursor(8,0);
  lcd.print("In2");
  lcd.setCursor(12,0);
  lcd.print("In3");
  lcd.setCursor(16,0);
  lcd.print("In4");

  lcd.setCursor(4,1);
  lcd.print("   ");
  lcd.setCursor(4,1);
  lcd.print(secCont1);
  lcd.setCursor(4,2);
  lcd.print("   ");
  lcd.setCursor(4,2);
  lcd.print(minCont1);
  lcd.setCursor(4,3);
  lcd.print("   ");
  lcd.setCursor(4,3);
  lcd.print(hourCont1);

  lcd.setCursor(8,1);
  lcd.print("   ");
  lcd.setCursor(8,1);
  lcd.print(secCont2);
  lcd.setCursor(8,2);
  lcd.print("   ");
  lcd.setCursor(8,2);
  lcd.print(minCont2);
  lcd.setCursor(8,3);
  lcd.print("   ");
  lcd.setCursor(8,3);
  lcd.print(hourCont2);

  lcd.setCursor(12,1);
  lcd.print("   ");
  lcd.setCursor(12,1);
  lcd.print(secCont3);
  lcd.setCursor(12,2);
  lcd.print("   ");
  lcd.setCursor(12,2);
  lcd.print(minCont3);
  lcd.setCursor(12,3);
  lcd.print("   ");
  lcd.setCursor(12,3);
  lcd.print(hourCont3);

  lcd.setCursor(16,1);
  lcd.print("   ");
  lcd.setCursor(16,1);
  lcd.print(secCont4);
  lcd.setCursor(16,2);
  lcd.print("   ");
  lcd.setCursor(16,2);
  lcd.print(minCont4);
  lcd.setCursor(16,3);
  lcd.print("   ");
  lcd.setCursor(16,3);
  lcd.print(hourCont4);      
  }
  else
  {
  lcd.setCursor(4,0);
  lcd.print("In5");
  lcd.setCursor(8,0);
  lcd.print("In6");
  lcd.setCursor(12,0);
  lcd.print("In7");
  lcd.setCursor(16,0);
  lcd.print("In8");

  lcd.setCursor(4,1);
  lcd.print("   ");
  lcd.setCursor(4,1);
  lcd.print(secCont5);
  lcd.setCursor(4,2);
  lcd.print("   ");
  lcd.setCursor(4,2);
  lcd.print(minCont5);
  lcd.setCursor(4,3);
  lcd.print("   ");
  lcd.setCursor(4,3);
  lcd.print(hourCont5);

  lcd.setCursor(8,1);
  lcd.print("   ");
  lcd.setCursor(8,1);
  lcd.print(secCont6);
  lcd.setCursor(8,2);
  lcd.print("   ");
  lcd.setCursor(8,2);
  lcd.print(minCont6);
  lcd.setCursor(8,3);
  lcd.print("   ");
  lcd.setCursor(8,3);
  lcd.print(hourCont6);

  lcd.setCursor(12,1);
  lcd.print("   ");
  lcd.setCursor(12,1);
  lcd.print(secCont7);
  lcd.setCursor(12,2);
  lcd.print("   ");
  lcd.setCursor(12,2);
  lcd.print(minCont7);
  lcd.setCursor(12,3);
  lcd.print("   ");
  lcd.setCursor(12,3);
  lcd.print(hourCont7);
  
  lcd.setCursor(16,1);
  lcd.print("   ");
  lcd.setCursor(16,1);
  lcd.print(secCont8);
  lcd.setCursor(16,2);
  lcd.print("   ");
  lcd.setCursor(16,2);
  lcd.print(minCont8);
  lcd.setCursor(16,3);
  lcd.print("   ");
  lcd.setCursor(16,3);
  lcd.print(hourCont8);  
  }
}


void showData(){
      if(millis()-timer1sec>1000){
      timer1sec=millis();
      minCont1=minCont1+secCont1;
      minCont2=minCont2+secCont2;
      minCont3=minCont3+secCont3;
      minCont4=minCont4+secCont4;
      minCont5=minCont5+secCont5;
      minCont6=minCont6+secCont6;
      minCont7=minCont7+secCont7;
      minCont8=minCont8+secCont8;
      secCont1=0;secCont2=0;secCont3=0;secCont4=0;secCont5=0;secCont6=0;secCont7=0;secCont8=0; 
      }
      
      if(millis()-timer1min>60000){
      timer1min=millis();
      showDisplay();
      hourCont1=hourCont1+minCont1;
      hourCont2=hourCont2+minCont2;
      hourCont3=hourCont3+minCont3;
      hourCont4=hourCont4+minCont4;
      hourCont5=hourCont5+minCont5;
      hourCont6=hourCont6+minCont6;
      hourCont7=hourCont7+minCont7;
      hourCont8=hourCont8+minCont8;
      minCont1=0;minCont2=0;minCont3=0;minCont4=0;minCont5=0;minCont6=0;minCont7=0;minCont8=0;
      
    }
      if(millis()-timer1hour>3600000){
      timer1hour=millis();
      showDisplay();
      hourCont1=0;hourCont2=0;hourCont3=0;hourCont4=0;hourCont5=0;hourCont6=0;hourCont7=0;hourCont8=0;
    }

}
