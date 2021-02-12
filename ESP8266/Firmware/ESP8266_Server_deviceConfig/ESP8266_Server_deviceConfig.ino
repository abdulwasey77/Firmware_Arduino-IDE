#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define MAX_CLIENTS 50
#define MAX_LINE_LENGTH 50
char *ssid = "ESP8266_server";             
char *pass = "server1234";
int nc=-1;
char *ssidSTA = "I-Tech-Router";             
char *passSTA = "0512303189T"; 
IPAddress local_IP(192, 168, 10, 50);
IPAddress gateway(192, 168, 10, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiClient *clients[MAX_CLIENTS] = { NULL };
char inputs[MAX_CLIENTS][MAX_LINE_LENGTH] = { 0 };

String macNode_1="24:6F:28:81:1D:B0";
String macNode_2="30:AE:A4:9C:EC:10";
String macNode_3="50:02:91:79:AD:DD";

String loginUsr;
String loginPwd;

String node_1;
String node_2; 
String node_3;
String node_1value;
String node_2value; 
String node_3value;
String maccheck;
String value;
String datacheck; 
String html;
String htmlpage;
int checkflag=0;

            
ESP8266WebServer Webserver(80); 
WiFiServer server(8080);                  
void setup() {
  Serial.begin(115200);                 
  WiFi.mode(WIFI_AP);
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid, pass);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

//
//  if (!WiFi.config(local_IP, gateway, subnet)) {
//  Serial.println("STA Failed to configure");
//  }
//  Serial.print("connecting to...");
//  Serial.println(ssidSTA);
//  WiFi.begin(ssidSTA,passSTA);
//
//  while(WiFi.status() != WL_CONNECTED){
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
  
  Webserver.on("/", handle_OnConnect);
  Webserver.on("/get",logincheck);
  Webserver.on("/get",textbox);
  Webserver.onNotFound(handle_NotFound);
  Webserver.begin();
  server.begin();
  Webserver.send(200, "text/html", loginPage());
}

void loop () {
  Webserver.handleClient();
  if(loginUsr=="admin"&&loginPwd=="password"&&checkflag==0){
  checkflag=1;
  loginUsr="";
  loginPwd="";
  Serial.println("in check");
  Webserver.on("/", handle_OnConnect);
  Webserver.send(200, "text/html", HtmlString()); 
  } 
  WiFiClient newClient = server.available();
  if (newClient)
  {
    Serial.println("new client");
    nc++;
    if (nc <= 50)
    {
      if (NULL == clients[nc])
      {
        clients[nc] = new WiFiClient(newClient);
        delay(1000);
      }
    }
  }
  getdata();
}
void datasend(String macaddr,String data){
String StoChar= macaddr;
StoChar += ',';
StoChar += data;
StoChar += '*';
char sendto[200];
StoChar.toCharArray(sendto,StoChar.length());
 for (int i = 0 ; i <= nc ; i++)
  {
    clients[i]->write(sendto);
    delay(10);
  }
  delay(500);            
}

void getdata(){
  for (int i = 0 ; i <= nc ; i++){
  if(clients[i]->available()>0)
  {
  value = clients[i]->readStringUntil('\n');   
  Serial.print("value : "); Serial.println(value);
  int comma = value.indexOf(',');
  maccheck = value.substring(comma,0);
  if(maccheck==macNode_1)
  {
    maccheck="";
    int star =value.indexOf('*');
    node_1 = value.substring(star,comma+1);    
  }
  else if(maccheck==macNode_2)
  {
    maccheck="";
    int star =value.indexOf('*');
    node_2 = value.substring(star,comma+1);
    
  }
   else if(maccheck==macNode_3)
  {
    maccheck="";
    int star =value.indexOf('*');
    node_3 = value.substring(star,comma+1);
      
    } 
    Webserver.send(200, "text/html", HtmlString());
  }
}
}
void logincheck()
{
    loginUsr = Webserver.arg("usr");
    loginPwd = Webserver.arg("pwd");
//    Serial.print("loginUsr: "); Serial.println(loginUsr);
//    Serial.print("loginPwd: "); Serial.println(loginPwd);
}
void textbox()
{
    node_1value =Webserver.arg("Node1");
    node_2value =Webserver.arg("Node2");
    node_3value =Webserver.arg("Node3");
    if(node_1value!=""){
  datasend(macNode_1,node_1value);
    }
        if(node_2value!=""){
      datasend(macNode_2,node_2value);
    }
        if(node_3value!=""){
      datasend(macNode_3,node_3value);
    }
    Webserver.send(200, "text/html", HtmlString());
}
void handle_OnConnect()
{
  
  if(checkflag==1){
    Webserver.send(200, "text/html", HtmlString());
  }else{
    Webserver.send(200, "text/html", loginPage());
  }
}


void handle_NotFound() {
  Webserver.send(404, "text/plain", "Not found");
}

String HtmlString(){
  html = "<!DOCTYPE html> <html> <head><meta http-equiv=\"refresh\" content=\"10\">  <style> table, th, td { border: 1px solid black; border-collapse: collapse; } th, td { padding: 5px; text-align: center; } #t01 th { background-color: black; color: white; } #t01 td { background-color: Red; color: white; } </style> </head> <body>\n";
  html += "<table style=\"width:100%\"> <table id=\"t01\"> <caption><h2>Device Table</h2></caption> <tr> <th>Device Name</th> <th>Status</th> <th>Input</th> </tr> <tr>\n";
  html += "<td>Node_1</td>\n";
  html += "<td>\n";
  html += node_1;
  html += "</td>\n"; 
  html += "<form action=\"/get\"> <td> <input type=\"text\" name=\"Node1\">\n";
  html += "<input type=\"submit\" value=\"Submit\"></td> </form> \n";
  html += "</tr> <tr> <td>Node_2</td>\n";
  html += "<td>\n";
  html += node_2;
  html += "</td>\n";
  html += "<form action=\"/get\"> <td> <input type=\"text\" name=\"Node2\">\n";
  html += "<input type=\"submit\" value=\"Submit\"></td> </form> \n";
  html += "</tr> <tr> <td>Node_3</td>\n";
  html += "<td>\n";
  html += node_3;
  html += "</td>\n";
  html += "<form action=\"/get\"> <td> <input type=\"text\" name=\"Node3\">\n";
  html += "<input type=\"submit\" value=\"Submit\"></td> </form> \n";
  html += "</tr> </table> </body> </html>";
  return html;
  
}
String loginPage(){
htmlpage = "<!DOCTYPE html> <html> <head> <style> h1 {text-align: center;} div.a { text-align: center; } </style> </head> <body> <h1>Login Form</h1> <div class=\"a\">\n";
htmlpage += "<form action=\"/get\">\n";
htmlpage += "<label for=\"usr\">Username:</label> <input type=\"text\" id=\"usr\" name=\"usr\"><br><br>\n";
htmlpage += "<label for=\"pwd\">Password:</label> <input type=\"text\" id=\"pwd\" name=\"pwd\"><br><br>\n";
htmlpage += "<input type=\"submit\" value=\"Submit\">\n";
htmlpage += "</form> </body> </html>";
return htmlpage;
}
