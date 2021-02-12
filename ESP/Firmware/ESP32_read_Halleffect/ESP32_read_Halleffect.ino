const int AnalogPin = 13;
const float GAUSS_PER_STEP = 2.57;  // Sensor outputs approx 1.9mV / Gauss.  
                                    // ADC step is about 4.89mV / Step for 5V operation. 
float rawValue = 0.0;               // Raw ADC Reading
float gaussValue = 0.0;
float zeroLevel = 1990.0;// Adjust value as needed to get zero rawValue output with no magnetic field.
float pulseVolts,prePulse=0;
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
//  Serial.print ("Reading Raw: ");
//  Serial.println (rawValue);
  for(int i=0;i<=10;i++)
  {
    rawValue = rawValue+analogRead(AnalogPin)-zeroLevel; 
  }
    rawValue=rawValue/10;
    pulseVolts=rawValue*(3.3/4096);
//  Serial.print ("pulseVolts : ");
//  Serial.println (pulseVolts);
//  delay(100);
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
