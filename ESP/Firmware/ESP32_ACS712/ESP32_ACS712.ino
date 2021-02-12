#define currentPin1  33
#define currentPin2  34
#define triacPin1  21
#define triacPin2  22


float sensitivity = 100;
float adcValueread1= 0;
float adcValueread2= 0;
float adcValue1= 0;
float offsetVoltage1 = 2250;
float adcVoltage1 = 0;
float currentValue1 = 0;
float adcValue2= 0;
float offsetVoltage2 = 2250;
float adcVoltage2 = 0;
float currentValue2 = 0;
float oldadcvalue1=0;
float oldadcvalue2=0;
int count1=0;
int count2=0;
float check1;
float check2;
 
void setup() 
{
//  pinMode(currentPin1,INPUT);
//  pinMode(currentPin2,INPUT);
  pinMode(triacPin1,OUTPUT);
  pinMode(triacPin2,OUTPUT);
  Serial.begin(115200);
  digitalWrite(triacPin1,HIGH);
  digitalWrite(triacPin2,HIGH);
  delay(2000);
}
 
void loop()
{
  long sec=millis();
  while(millis() - sec < 100){  
  adcValueread1 = analogRead(currentPin1)-2750;
  adcValueread2 = analogRead(currentPin2)-2750;
  if(adcValueread1<0){
    adcValueread1 *= -1;
  }
  if(adcValueread2<0){
   adcValueread2 *= -1;
  }
  if(adcValueread1>oldadcvalue1){
    oldadcvalue1=adcValueread1;   
  }
  if(adcValueread2>oldadcvalue2){
    oldadcvalue2=adcValueread2;   
  }
  }
  check1=oldadcvalue1;
  check1=(1-(check1/1000))*check1;
  
  check2=oldadcvalue2;
  check2=(1-(check2/1000))*check2;
  
    sec=millis();
    while(millis() - sec < 900){ 
  adcValueread1 = analogRead(currentPin1)-2750;
  adcValueread2 = analogRead(currentPin2)-2750;
  
  if(adcValueread1<0){
  adcValueread1 *= -1;
  }
  if(adcValueread2<0){
  adcValueread2 *= -1;
  }
  if(adcValueread1>check1){
    oldadcvalue1=adcValueread1+oldadcvalue1;
    count1++;
  }
  if(adcValueread2>check2){
    oldadcvalue2=adcValueread2+oldadcvalue2;
    count2++;
  }
  }
  
  oldadcvalue1=oldadcvalue1/count1;
    count1=0;
  adcValue1=oldadcvalue1+2750;
  oldadcvalue1=0;

  oldadcvalue2=oldadcvalue2/count2;
    count2=0;
  adcValue2=oldadcvalue2+2750;
  oldadcvalue2=0;

  adcVoltage1 = (adcValue1 / 4096.0) * 3300;
  currentValue1 = ((adcVoltage1 - offsetVoltage1) / sensitivity);  
  
  adcVoltage2 = (adcValue2 / 4096.0) * 3300;
  currentValue2 = ((adcVoltage2 - offsetVoltage2) / sensitivity);
  
  if(currentValue1<0.20)
  currentValue1=0.0;
  if(currentValue2<0.20)
  currentValue2=0.0;
  
  Serial.print("Raw Sensor Value 1 = " ); Serial.println(adcValue1);
  Serial.print("Sensor Voltage 1 = " ); Serial.println(adcVoltage1);
  Serial.print("Sensor current 1 = " ); Serial.println(currentValue1);
  Serial.println();
  Serial.print("Raw Sensor Value 2 = " ); Serial.println(adcValue2);
  Serial.print("Sensor Voltage 2 = " ); Serial.println(adcVoltage2);
  Serial.print("Sensor current 2 = " ); Serial.println(currentValue2);
  Serial.println();
 delay(2500);
}
