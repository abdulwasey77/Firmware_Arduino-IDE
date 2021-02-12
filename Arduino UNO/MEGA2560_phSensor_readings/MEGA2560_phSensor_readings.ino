#include <Arduino.h>
int pHSense = A0;
int samples = 20;
float adc_resolution = 1023.0;
float analogvol;

void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.println("cimpleo pH Sense");
}

float ph(float voltage){
  return 7 + ((2.5 - voltage) / 0.18);
}

void loop(){
  int measurings=0;
  for (int i = 0; i < samples; i++)
  {
    measurings += analogRead(pHSense);
    delay(1);
  }
    analogvol=measurings/samples;
    analogvol=(analogvol*5)/1023;
    Serial.print("analog voltage = "); Serial.println(analogvol);
    float voltage = 5 / adc_resolution * measurings/samples;
    Serial.print("pH= ");
    Serial.println(ph(voltage));
    delay(3000);
}
