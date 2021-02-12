#include <LiquidCrystal_I2C.h>
#define Input1 A0
#define Input2 A1
#define Input3 A2
#define Input4 A3
#define Input5 A4
#define Input6 A5
#define Input7 A6
#define Input8 A7

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
float rawValue1,rawValue2,rawValue3,rawValue4,rawValue5,rawValue6,rawValue7,rawValue8;
float zeroLevel = 536;           
float pulseVolts1,pulseVolts2,pulseVolts3,pulseVolts4,pulseVolts5,pulseVolts6,pulseVolts7,pulseVolts8;;
char pulseFlag1,pulseFlag2,pulseFlag3,pulseFlag4,pulseFlag5,pulseFlag6,pulseFlag7,pulseFlag8;

void setup(){
  Serial.begin(115200);
  pinMode(Input4, INPUT);
//  pinMode(Input2, INPUT);
//  pinMode(Input3, INPUT);
//  pinMode(Input4, INPUT);
//  pinMode(Input5, INPUT);
//  pinMode(Input6, INPUT);
//  pinMode(Input7, INPUT);
//  pinMode(Input8, INPUT);
  lcd.init();                     
  lcd.backlight();
}

void loop(){
     if(millis()-timerInline0>5000){
      timerInline0=millis();
      Inline0 = !Inline0;
     }
//  Serial.print ("rawValue1 : ");
//  Serial.println (rawValue1);
//  delay(100);
    ReadBtn();
    showData();
    showDisplay();
}


void ReadBtn()
{
  for(int i=0;i<=10;i++)
  {
    rawValue1 = rawValue1+analogRead(Input4)-zeroLevel;
//    rawValue2 = rawValue2+analogRead(Input2)-zeroLevel;
//    rawValue3 = rawValue3+analogRead(Input3)-zeroLevel; 
//    rawValue4 = rawValue4+analogRead(Input4)-zeroLevel; 
//    rawValue5 = rawValue5+analogRead(Input5)-zeroLevel; 
//    rawValue6 = rawValue6+analogRead(Input6)-zeroLevel;
//    rawValue7 = rawValue7+analogRead(Input7)-zeroLevel; 
//    rawValue8 = rawValue8+analogRead(Input8)-zeroLevel;    
  }
  rawValue1/=10;rawValue2/=10;rawValue3/=10;rawValue4/=10;rawValue5/=10;rawValue6/=10;rawValue7/=10;rawValue8/=10;
  pulseVolts1=(rawValue1*5)/1023;
  pulseVolts2=(rawValue2*5)/1023;
  pulseVolts3=(rawValue3*5)/1023;
  pulseVolts4=(rawValue4*5)/1023;
  pulseVolts5=(rawValue5*5)/1023;
  pulseVolts6=(rawValue6*5)/1023;
  pulseVolts7=(rawValue7*5)/1023;
  pulseVolts8=(rawValue8*5)/1023;
   
  if(pulseVolts1>0.05)
  {
    if(pulseFlag1)
    {
      pulseFlag1=0;
      secCont1++;
    }
  }
  if(pulseVolts1<0.01)
      pulseFlag1=1;

  if(pulseVolts2>0.05)
  {
    if(pulseFlag2)
    {
      pulseFlag2=0;
      secCont2++;
    }
  }
  if(pulseVolts2<0.01)
      pulseFlag2=1;

  if(pulseVolts3>0.05)
  {
    if(pulseFlag3)
    {
      pulseFlag3=0;
      secCont3++;
    }
  }
  if(pulseVolts3<0.01)
      pulseFlag3=1;

  if(pulseVolts4>0.05)
  {
    if(pulseFlag4)
    {
      pulseFlag4=0;
      secCont4++;
    }
  }
  if(pulseVolts4<0.01)
      pulseFlag4=1;

  if(pulseVolts5>0.05)
  {
    if(pulseFlag5)
    {
      pulseFlag5=0;
      secCont5++;
    }
  }
  if(pulseVolts5<0.01)
      pulseFlag5=1;

  if(pulseVolts6>0.05)
  {
    if(pulseFlag6)
    {
      pulseFlag6=0;
      secCont6++;
    }
  }
  if(pulseVolts6<0.01)
      pulseFlag6=1;

  if(pulseVolts7>0.05)
  {
    if(pulseFlag7)
    {
      pulseFlag7=0;
      secCont7++;
    }
  }
  if(pulseVolts7<0.01)
      pulseFlag7=1;

  if(pulseVolts8>0.05)
  {
    if(pulseFlag8)
    {
      pulseFlag8=0;
      secCont8++;
    }
  }
  if(pulseVolts8<0.01)
      pulseFlag8=1;
  
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
