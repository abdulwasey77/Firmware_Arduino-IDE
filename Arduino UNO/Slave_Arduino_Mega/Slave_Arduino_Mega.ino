#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme; // I2C
byte c;
int pos;
char buffIN [50];
char buffOUT [20];
volatile byte indx;
String DataString;
char sendbuff[20];
void setup (void)
{
  Serial.begin(115200);
  Serial.println("Serial Started");
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= bit(SPE);

  // turn on interrupts
  SPCR |= bit(SPIE);
  indx = 0;
   SPI.attachInterrupt();
    if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
}  // end of setup

ISR (SPI_STC_vect) // SPI interrupt routine 
{ 
   c = SPDR;// read byte from SPI Data Register
   if(c!=0)
   {
      buffIN [indx++] = c;
      delay(10);
      if (c == '\r')
      { 
      DataString=String(buffIN);
      memset(buffIN, 0, sizeof buffIN);
      indx=0;
      }

    pos=0;
   }
   else{   

       if(DataString=="Temperature\r")
       {
        Serial.print("data String : "); Serial.println(DataString);
        float tempval=bme.temperature;
        String datat;
        datat = String(tempval);
        
        datat.toCharArray(sendbuff,datat.length());
          Serial.print("data Send : "); Serial.println (sendbuff); 
          datat="";
          DataString="";      
      }
             if(DataString=="Humidity\r")
       {
        Serial.print("data String : "); Serial.println(DataString);
        float humval=bme.humidity;
        String datat ;
        datat = String(humval);
        
        datat.toCharArray(sendbuff,datat.length());
          Serial.print("data Send : "); Serial.println (sendbuff); 
            DataString="";      
      }
             if(DataString=="Pressure\r")
       {
        Serial.print("data String : "); Serial.println(DataString);
        float pressval=bme.pressure/100.0;
        String datat;
        datat = String(pressval);
        
        datat.toCharArray(sendbuff,datat.length());
          Serial.print("data Send : "); Serial.println (sendbuff); 
            DataString="";      
      }
             if(DataString=="Gass\r")
       {
        Serial.print("data String : "); Serial.println(DataString);
        float tempval=bme.gas_resistance / 1000.0;
        String datat;
        datat = String(tempval);   
        datat.toCharArray(sendbuff,datat.length());
          Serial.print("data Send : "); Serial.println (sendbuff); 
            DataString="";      
      }
      SPDR = sendbuff [pos++];
      delay(10);
  }
  
}

void loop (void) {
  
}
//  if (! bme.performReading()) {
//    Serial.println("Failed to perform reading :(");
//    return;
//  }
//   if (process) {
//      process = false; //reset the process
//    //  Serial.println (buff);
//      String recv;
//      for(int k=0; k<20; k++){
//      recv += buff[k];
//      }//print the array on serial monitor
//     //Serial.print("recv : "); Serial.println (recv);
//      if(recv=="Temperature\r"){
//        float tempval=bme.temperature;
//        String t = String(tempval);
//        for(int i=0;i<sizeof(t)-1;i++){
//            buf[i]=t[i];
//            
//          }
//          Serial.print("buf temp : "); Serial.println (buf);
//           
//           c = SPDR;
//           Serial.print("c : "); Serial.println (c);
//           pos = 0;
//           while (c == 0)  // starting new sequence?
//             {
//              Serial.print("while buf temp : "); Serial.println (buf);
//           c = SPDR;
//           SPDR = buf [pos++];   // send first byte
//              }
//            
//      //  Serial.print("temp : "); Serial.println (t);
//       // Serial.print("Temp : "); Serial.println (tempval);
//      }
//
//      
//          if(recv=="Humidity\r"){
//            float humval=bme.humidity;
//            String h = String(humval);
////          for(int i=0;i<sizeof(h)-1;i++){
////            buf[i]=h[i];
////            
////          }
////          Serial.print("buf : "); Serial.println (buf);
////           
////           c = SPDR;
////           pos = 0;
////           while (c == 0)  // starting new sequence?
////             {
////           c = SPDR;
////           SPDR = buf [pos++];   // send first byte
////              }
////            
////        Serial.print("Hum : "); Serial.println (h);
//      }
//          if(recv=="Pressure\r"){
//            float pressval=bme.pressure/100.0;
//            String p = String(pressval);
//       // Serial.print("Press : "); Serial.println (p);
//      }
//          if(recv=="Gass\r"){
//            float gassval=bme.gas_resistance / 1000.0;
//            String g = String(gassval);
//       // Serial.print("Gass : "); Serial.println (g);
//      }
//      indx= 0; //reset button to zero
//      memset(buff, 0, sizeof buff);
//
//   }
//}
//
////    if(buff=="Temperature"){
////      SPDR = h;
////    }
////    if(buff=="Humidity"){
////      SPDR = t;
////    }
//
//    
