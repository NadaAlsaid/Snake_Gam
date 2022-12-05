#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
/* Put your SSID & Password */
const char* ssid = "snake";  // Enter SSID here
const char* password = "123456789";  //Enter Password here

ESP8266WebServer server(80);

bool Easy = HIGH;
bool Middle = HIGH;
bool Hard = HIGH;


void setup() {
  
  Serial.begin(115200);
  

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/EasyON", handle_Easyon);
  server.on("/EasyOFF", handle_Easyoff);
  server.on("/Middleon", handle_Middleon);
  server.on("/Middleoff", handle_Middleoff);
  server.on("/Hardon", handle_Hardon);
  server.on("/Hardoff", handle_Hardoff);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();

  if(!Middle){
   Serial.println( "1" ) ;
  }
  if(!Hard){
   Serial.println( "2" ) ;
  }
  if (!Easy)
  {
   Serial.println( "0" ) ;
  }
  
  delay(500);
  
}

void handle_OnConnect() {
   Easy = HIGH;
   Middle = HIGH;
   Hard = HIGH;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(Easy ,Middle , Hard )); 
 
}

void handle_Easyon() {
  Easy = LOW;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true , false , false )); 
}

void handle_Easyoff() {
  Easy = HIGH;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false , false , false )); 
}

void handle_Middleon() {
  Middle = LOW;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML( false ,true , false )); 
}

void handle_Middleoff() {
  Middle = HIGH;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false , false , false)); 
}

void handle_Hardon() {
  Hard = LOW;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(false , false , true )); 
}

void handle_Hardoff() {
  Hard = HIGH;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false , false , false )); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t Easy , uint8_t Middle , uint8_t Hard ){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  ptr +="<title>Snake Game</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;background-image:url(home.png) ; background-repeat: no-repeat; background-size: 100% 100%;} h1 {color: #106856;text-shadow: 10px 10px 10px #f8f7f8;margin: 50px auto 30px;} h2 {color: #34495e;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer; border-radius: 0px 10px 0px 10px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +=".button-on1 {background-color: #1abc9c;}\n";
  ptr +=".button-on1:active {background-color: #16a085;}\n";
  ptr +=".button-off1 {background-color: #34495e;}\n";
  ptr +=".button-off1:active {background-color: #2c3e50;}\n";
  ptr +=".button-on2 {background-color: #1abc9c;}\n";
  ptr +=".button-on2:active {background-color: #16a085;}\n";
  ptr +=".button-off2 {background-color: #34495e;}\n";
  ptr +=".button-off2:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color:rgb(55, 75, 65 , 85);margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Snake Game</h1>\n";
  
  if(Easy)
  {
      ptr +="<p>Easy: ON</p><a class=\"button button-off\" href=\"/EasyOFF\">OFF</a>\n";}
   else 
   {
      ptr +="<p>Easy: OFF</p><a class=\"button button-on\" href=\"/EasyON\">ON</a>\n";
   }
  if(Middle)
  {
      ptr +="<p>Middle: ON</p><a class=\"button button-off1\" href=\"/Middleoff\">OFF</a>\n";}
  else 
  {
      ptr +="<p>Middle: OFF</p><a class=\"button button-on1\" href=\"/Middleon\">ON</a>\n";
  }
  if(Hard)
  {
      ptr +="<p>Hard: ON</p><a class=\"button button-off2\" href=\"/Hardoff\">OFF</a>\n";
  }
  else
  {
      ptr +="<p>Hard: OFF</p><a class=\"button button-on2\" href=\"/Hardon\">ON</a>\n";
  }

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
