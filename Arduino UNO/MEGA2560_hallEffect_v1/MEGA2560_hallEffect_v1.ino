const int AnalogPin = A0;
const float GAUSS_PER_STEP = 2.57;  // Sensor outputs approx 1.9mV / Gauss.  
float gaussValue = 0.0;                                    // ADC step is about 4.89mV / Step for 5V operation. 

float rawValue = 0.0;
float voltdiv;
float zeroLevel = 535;           // Adjust value as needed to get zero rawValue output with no magnetic field.
float pulseVolts;
int pulseCount=0;
char pulseFlag;
//===============================================================================
//  Initialization
//===============================================================================
void setup() 
{ 
  pinMode (AnalogPin, INPUT);
  Serial.begin(115200);         // Set comm speed for debug window messages
}

//===============================================================================
//  Main
//===============================================================================
void loop() 
{
  
   // Output normalized to '0' with no field present
//rawValue = analogRead(AnalogPin);
//  Serial.print ("Reading Raw: ");
//  Serial.println (rawValue);
//  delay(100);

  for(int i=0;i<=10;i++)
  {
    rawValue = rawValue+analogRead(AnalogPin)-zeroLevel; 
  }
    rawValue=rawValue/10;
  Serial.print ("Reading Raw: ");
  Serial.println (rawValue);
  delay(500);
//    voltdiv=5/1023;
//      Serial.print ("voltdiv : ");
//  Serial.println (voltdiv);
    pulseVolts=(rawValue*5)/1023;
  Serial.print ("pulseVolts : ");
  Serial.println (pulseVolts);
  delay(500);
  if(pulseVolts>0.05){
    if(pulseFlag){
      pulseFlag=0;
      pulseCount++;
      Serial.println();
      Serial.print ("pulseCount : ");
      Serial.println (pulseCount);
      Serial.println();
    }
  }
    delay(10);
    if(pulseVolts<0.01)
    pulseFlag=1;
  }
//  if(pulseVolts>prePulse)
//  {
//  prePulse=pulseVolts;
//  }
//  if(pulseVolts>0.05 && prePulse){ //
//    pulseCount++;
//    Serial.println();
//    Serial.print ("pulseCount : ");
//    Serial.println (pulseCount);
//    Serial.println();
//    Serial.print ("prePulse : ");
//    Serial.println (prePulse);
//    prePulse=0;
//  }
// Reading positive relative to the South Pole, the North Pole negative
//  gaussValue = rawValue * GAUSS_PER_STEP;
//  Serial.print ("Reading in Gauss: ");
//  Serial.println (gaussValue);
  //  delay (3000);
