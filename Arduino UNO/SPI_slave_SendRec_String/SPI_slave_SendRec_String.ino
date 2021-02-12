#include <SPI.h>
char buff [50];
byte indx;
char buf [20]="Hello World!";
int pos;
String DataString;
byte c;


void setup (void) {
   Serial.begin (115200);
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
    // turn on SPI in slave mode
    SPCR |= bit(SPE);
    // turn on interrupts
    SPCR |= bit(SPIE);
   indx = 0; // buffer empty
   SPI.attachInterrupt(); // turn on interrupt
}

ISR (SPI_STC_vect) // SPI interrupt routine 
{ 
   c = SPDR;// read byte from SPI Data Register
   if(c!=0)
   {
      buff [indx++] = c;
      if (c == '\r')
      { 
      DataString=String(buff);
      indx=0;
      }
   
   Serial.print("data String : "); Serial.println(DataString);   
  
    pos=0;
   }else if(c==0)
{
  
  SPDR = buf [pos++];
  }
  
}

void loop (void) {
//   if (process) {
//      process = false; //reset the process
//      Serial.println (buff); //print the array on serial monitor
//      indx= 0; //reset button to zero
//      
//   }
}
