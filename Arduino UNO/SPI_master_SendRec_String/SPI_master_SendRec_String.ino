#include <SPI.h>
 
void setup() {
  Serial.begin(115200);
   digitalWrite(SS, HIGH); // disable Slave Select
   SPI.begin();
   SPI.setClockDivider(SPI_CLOCK_DIV4);//divide the clock by 4
}
 
void loop() {
   char c;
   //Serial.print("");
   digitalWrite(SS, LOW); // enable Slave Select
   for (const char * p = "Temperature\r" ; c = *p; p++) 
   {
      SPI.transfer(c);
      delay(10);
   }
   Serial.println();
   //digitalWrite(SS, HIGH); // disable Slave Select
   delay(2000);
  
    char buf [20];

  // enable Slave Select
   // digitalWrite(SS, LOW);    

   for (int pos = 0; pos < sizeof (buf) - 1; pos++)
    {
    delay (10);
    buf [pos] = SPI.transfer (0);
    }

  digitalWrite(SS, HIGH);

  Serial.print ("Received : ");
  Serial.println (buf);

  delay (1000);  // 1 second delay 
}
