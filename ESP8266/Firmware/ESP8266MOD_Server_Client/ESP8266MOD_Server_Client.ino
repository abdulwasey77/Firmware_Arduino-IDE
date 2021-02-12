#include <SoftwareSerial.h>
#define RX 10
#define TX 11
String ssid_Sta = "I-Tech-Router";        //  SSID Station
String password_Sta = "0512303189T";      //  PASSWORD Station

String ssid_AP = "ESP8266Mod";        //  SSID Station
String password_AP = "espconnect";      //  PASSWORD Station

String API = "GDKZYY76S4G4HLQX";          //  API Key
String HOST = "api.thingspeak.com";       //  Host where to post data
String PORT = "80";                       //  Server port
int countTrueCommand;
int countTimeCommand; 
int flag=0;
boolean found = false;

SoftwareSerial esp8266(RX,TX); 
 String ConfigFlashParam="";
 String ConfigParam="";
 int incomingByte = 0;
  const char* ssid_STA = "";
const char* password_STA = "";
String ssid;
String password;
String CoustomerID;
String CountryCode;
String TimeZone;
int posHead;
int posH;
int posi;

void setup() 
{

 Serial.begin(9600);
  esp8266.begin(9600);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=2",5,"OK");
  sendCommand("AT+CWSAP=\""+ssid_AP+"\",\""+password_AP+"\",1,4",20,"OK");  //ApMode
  sendCommand("AT+CWLIF",5,"OK");
  sendCommand("AT+CIPAP?",5,"OK");
  sendCommand("AT+CIPMUX=1",5,"OK");
  sendCommand("AT+CIPSERVER=1,80",5,"OK");
   
}
 
void loop() 
{
//  if(esp8266.find(":"))//ok
//    {
//         if ( esp8266.available() )   {  Serial.write( esp8266.read() );  }
//          }
// listen for communication from the ESP8266 and then write it to the serial monitor
    if ( esp8266.available() )   {
      char readhi[]="Hi";
//incomingByte = esp8266.read(); // read the incoming byte:
ConfigParam= esp8266.readString();
      posHead = ConfigParam.indexOf(':');
      posH = ConfigParam.indexOf('H');
      posi = ConfigParam.indexOf('i');

if(posHead+1==posH && posH+1==posi)
    {
  String getData="hello";
 sendCommand("AT+CIPSTART=0,\"TCP\",\"192.168.4.1\",\"80\"",15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()),4,">");
 esp8266.println(getData);delay(1000);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
    }
//Serial.print("Data Read From Client: "); Serial.println(ConfigParam);
//CheckingSsidPass();
    }
   // Serial.print("data:    "); Serial.println(dataFC);
//    if(Serial.available() && flag==1){
//Serial.print("Stringdata: "); Serial.print(dataFC);
// flag=0;
//    }
    // listen for user input and send it to the ESP8266
//    if ( Serial.available() )       {  esp8266.write( Serial.read() );  }
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("PASS");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }

 void CheckingSsidPass(){
    //if(ConfigFlashParam[ConfigFlashParam.length()=='*'])
    //if (ConfigFlashParam.startsWith("$") && ConfigFlashParam.endsWith("*") ) {
      int posHeader = ConfigParam.indexOf('$');
      int posTail = ConfigParam.indexOf('*');
     
        //Serial.println(ConfigFlashParam);
        int posComma1 = ConfigFlashParam.indexOf(',',posHeader+1);
        int posComma2 = ConfigFlashParam.indexOf(',' , posComma1 + 1);
        int posComma3 = ConfigFlashParam.indexOf(',' , posComma2 + 1);
        int posComma4 = ConfigFlashParam.indexOf(',' , posComma3 + 1);

        //string strA = strB.substring(to,from);
        ssid = ConfigFlashParam.substring((posComma1),posHeader+1);
        password = ConfigFlashParam.substring((posComma2),posComma1+1);
        CoustomerID = ConfigFlashParam.substring((posComma3),posComma2+1);
        CountryCode = ConfigFlashParam.substring((posComma4),posComma3+1);
        TimeZone = ConfigFlashParam.substring((posTail),posComma4+1);     
       
      
       //length of password string
        
        ssid_STA = ssid.c_str();                   
        password_STA = password.c_str();
        Serial.print("SSID STA : ");
        Serial.println(ssid_STA);
        Serial.print("Password STA : ");
        Serial.println(password_STA); 
        Serial.print("CoustomerID : ");
        Serial.println(CoustomerID);
        Serial.print("CountryCode : ");
        Serial.println(CountryCode);        
        Serial.print("TimeZone : ");
        Serial.println(TimeZone);

  
}
