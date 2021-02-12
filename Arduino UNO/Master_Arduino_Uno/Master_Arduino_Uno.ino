#include <SPI.h>
 char c;
 //#define SS 10
  unsigned long temptime;
  unsigned long humtime;
  unsigned long presstime;
  unsigned long gasstime;
  unsigned long sendtime;
  int tempflag=0;
  int humflag=0;
  int gassflag=0;
  int pressflag=0;
  int sendflag=0;
  const char * p ;
  char buf [200];
  int pos;
 
void setup (void)
{
  Serial.begin (115200);
  Serial.println ("Starting");
  digitalWrite(SS, HIGH);  // ensure SS stays high for now
  SPI.begin ();
  SPI.setClockDivider(SPI_CLOCK_DIV8);

}  // end of setup

void loop ()
{
  if(tempflag==0){
  temptime = millis();
  tempflag=1;
  }
  if(millis()-temptime > 5000){
    tempflag=0;
    p = "Temperature\r";
    char c;
   //Serial.print("");
   digitalWrite(SS, LOW); // enable Slave Select
   for (p ; c = *p; p++) 
   {
      SPI.transfer(c);
      delay(10);
   }
   
    
  pos=0;
  sendtime=millis();
  while(millis()-sendtime < 3000){
  
    delay (100);
    buf [pos++] = SPI.transfer (0);
    
    }
  
  digitalWrite(SS, HIGH);
  String Datarec=String(buf);
  Serial.print("Temperature : "); Serial.println(Datarec);
  memset(buf, 0, sizeof buf);
 }

   if(humflag==0){
  humtime = millis();
  humflag=1;
  }
  if(millis()-humtime > 10000){
    humflag=0;
    p = "Humidity\r";
    char c;
   //Serial.print("");
   digitalWrite(SS, LOW); // enable Slave Select
   for (p ; c = *p; p++) 
   {
      SPI.transfer(c);
      delay(10);
   }
   
  pos=0;
  sendtime=millis();
  while(millis()-sendtime < 3000){
    delay(100);
    buf [pos++] = SPI.transfer (0);
    }

  digitalWrite(SS, HIGH);
  String Datarec=String(buf);
  Serial.print("Humidity : "); Serial.println(Datarec);
  memset(buf, 0, sizeof buf);
    
 }

    if(pressflag==0){
  presstime = millis();
  pressflag=1;
  }
  if(millis()-presstime > 20000){
    pressflag=0;
    p = "Pressure\r";
     char c;
   //Serial.print("");
   digitalWrite(SS, LOW); // enable Slave Select
   for (p ; c = *p; p++) 
   {
      SPI.transfer(c);
      delay(10);
   }
   
  pos=0;
  sendtime=millis();
  while(millis()-sendtime < 3000){
    delay(100);
    buf [pos++] = SPI.transfer (0);
    }

  digitalWrite(SS, HIGH);
  String Datarec=String(buf);
  Serial.print("Pressure : "); Serial.println(Datarec);
  memset(buf, 0, sizeof buf);
    
 }

   if(gassflag==0){
  gasstime = millis();
  gassflag=1;
  }
  if(millis()-gasstime > 30000){
    gassflag=0;
    p = "Gass\r";
     char c;
   //Serial.print("");
   digitalWrite(SS, LOW); // enable Slave Select
   for (p ; c = *p; p++) 
   {
      SPI.transfer(c);
      delay(10);
   }
   
  pos=0;
  sendtime=millis();
  while(millis()-sendtime < 3000){
    delay(100);
    buf [pos++] = SPI.transfer (0);
    }

  digitalWrite(SS, HIGH);
  String Datarec=String(buf);
  Serial.print("Gass : "); Serial.println(Datarec);
  memset(buf, 0, sizeof buf);
    
 }
  
//  if(Datarec[0]="T"){
//    //Datarec[0]="";
//    Serial.print("Temperature : "); Serial.println(Datarec);
//    Datarec="";
//  }
//    if(Datarec[0]="H"){
//   // Datarec[0]="";
//    Serial.print("Humidity : "); Serial.println(Datarec);
//    Datarec="";
//  }
//    if(Datarec[0]="P"){
//    //Datarec[0]="";
//    Serial.print("Pressure : "); Serial.println(Datarec);
//    Datarec="";
//  }
//   if(Datarec[0]="G"){
//    //Datarec[0]="";
//    Serial.print("Gass : "); Serial.println(Datarec);
//    Datarec="";
//  }







  
//  if(tempflag==0){
//  temptime = millis();
//  tempflag=1;
//  }
//  if(millis()-temptime > 1000){
//    tempflag=0;
//  //  Serial.println("Receiving temp value every sec");
//   digitalWrite(SS, LOW); // enable Slave Select
//   for (const char * p = "Temperature\r" ; c = *p; p++) 
//   {
//    delayMicroseconds (15);
//      SPI.transfer(c);
//   }
//
//  char newdata=SPI.transfer(0);
//      // initiate transmission
//  for (int pos = 0; pos< 20; pos++)
//    {
//    //Serial.print("spi 0 buf temp : "); Serial.println (buf);
//    delayMicroseconds (15);
//    buf [pos] = SPI.transfer (0);
//
//    }
//    SPI.transfer(1);
//  //buf [sizeof (buf) - 1] = 0;  // ensure terminating null
//    Serial.print ("Received : ");
//    Serial.println (newdata);
//   digitalWrite(SS, HIGH); // disable Slave Select
//  }
//
//  if(humflag==0){
//  humtime = millis();
//  humflag=1;
//  }
//  if(millis()-humtime > 2000){
//    humflag=0;
//  //   Serial.println("Receiving hum value every 2 sec");
//      digitalWrite(SS, LOW); // enable Slave Select
//   for (const char * p = "Humidity\r" ; c = *p; p++) 
//   {
//      SPI.transfer(c);
//   }
//   digitalWrite(SS, HIGH); // disable Slave Select
//   
//  }
//
//  if(pressflag==0){
//  presstime = millis();
//  pressflag=1;
//  }
//  if(millis()-presstime > 5000){
//    pressflag=0;
//  //  Serial.println("Receiving press value every 5 sec");
//         digitalWrite(SS, LOW); // enable Slave Select
//   for (const char * p = "Pressure\r" ; c = *p; p++) 
//   {
//      SPI.transfer(c);
//   }
//   digitalWrite(SS, HIGH); // disable Slave Select
//   
//
//  }
//
//  if(gassflag==0){
//  gasstime = millis();
//  gassflag=1;
//  }
//  if(millis()-gasstime > 10000){
//    gassflag=0;
// //   Serial.println("Receiving gass value every 10 sec");
//         digitalWrite(SS, LOW); // enable Slave Select
//   for (const char * p = "Gass\r" ; c = *p; p++) 
//   {
//      SPI.transfer(c);
//   }
//   digitalWrite(SS, HIGH); // disable Slave Select
//   
//  }
}








//  // enable Slave Select
//  digitalWrite(SS, LOW);    
//  SPI.transfer (1);   // initiate transmission
//  for (int pos = 0; pos < sizeof (buf) - 1; pos++)
//    {
//    delayMicroseconds (15);
//    buf [pos] = SPI.transfer (0);
//    if (buf [pos] == 0)
//      {
//      break;
//      }
//    }
//
//  buf [sizeof (buf) - 1] = 0;  // ensure terminating null
//
//  // disable Slave Select
//  digitalWrite(SS, HIGH);
//
//  Serial.print ("Received : ");
//  Serial.println (buf);
//  
//    int tempval=random(10);
//    Serial.print("Sending Temperature Value: "); Serial.println(tempval);
//    digitalWrite(SS, LOW);
//    SPI.transfer(2);
//    SPI.transfer(tempval);
//    delay(10);
//    digitalWrite(SS, HIGH);
//  
//
//  delay (1000);  // 1 second delay 
 // end of loop
