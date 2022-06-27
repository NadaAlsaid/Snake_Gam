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




















//#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
//#include <Servo.h>
//Servo myservo;
///* Put your SSID & Password */
//const char* ssid = "teams";  // Enter SSID here
//const char* password = "123456789";  //Enter Password here
//
//ESP8266WebServer server(80);
//
//uint8_t Garage1pin = D5;
//bool Easy = HIGH;
//bool Middle = HIGH;
//bool Hard = HIGH;
//uint8_t LED2pin = D1;
//
//uint8_t LED3pin = D2;
//void setup() {
//  Serial.begin(115200);
//  pinMode(Garage1pin, OUTPUT);
//  pinMode(LED2pin, OUTPUT);
//  pinMode(LED3pin, OUTPUT);
//  myservo.attach(D4);
//  myservo.write(0);
//
//  WiFi.softAP(ssid, password);
//
//  IPAddress IP = WiFi.softAPIP();
//  Serial.print("AP IP address: ");
//  Serial.println(IP);
//
//  // Print ESP8266 Local IP Address
//  Serial.println(WiFi.localIP());
//  delay(100);
//  
//  server.on("/", handle_OnConnect);
//  server.on("/Garage1on", handle_Garage1on);
//  server.on("/Garage1off", handle_Garage1off);
//    server.on("/led2on", handle_led2on);
//  server.on("/led2off", handle_led2off);
//    server.on("/led3on", handle_led3on);
//  server.on("/led3off", handle_led3off);
//  server.onNotFound(handle_NotFound);
//  
//  server.begin();
//  Serial.println("HTTP server started");
//}
//void loop() {
//  server.handleClient();
//  if(Easy){
//   digitalWrite(Garage1pin, LOW);
//   myservo.write(0);
//  }
//  else
//  {
//    digitalWrite(Garage1pin, HIGH);
//    myservo.write(180);
//  }
//  
//
//
//  if(Middle){
//   digitalWrite(LED2pin, LOW);
//  }
//  else
//  {
//    digitalWrite(LED2pin, HIGH);
//  }
//  
//
//  if(LED3status){
//   digitalWrite(LED3pin, LOW);
//  }
//  else
//  {
//    digitalWrite(LED3pin, HIGH);
//  }
//  
//}
//
//void handle_OnConnect() {
//  Easy = HIGH;
//   Middle = HIGH;
//    LED3status = HIGH;
//  Serial.println("GPIO7 Status: OFF");
//  server.send(200, "text/html", SendHTML(Easy ,Middle , LED3status )); 
// 
//}
//
//void handle_Garage1on() {
//  Easy = LOW;
//  Serial.println("GPIO7 Status: ON");
//  server.send(200, "text/html", SendHTML(true , false , false)); 
//}
//
//void handle_Garage1off() {
//  Easy = HIGH;
//  Serial.println("GPIO7 Status: OFF");
//  server.send(200, "text/html", SendHTML(false , false , false)); 
//}
//
//void handle_led2on() {
//  LED2status = LOW;
//  Serial.println("GPIO7 Status: ON");
//  server.send(200, "text/html", SendHTML( false ,true , false)); 
//}
//
//void handle_led2off() {
//  LED2status = HIGH;
//  Serial.println("GPIO7 Status: OFF");
//  server.send(200, "text/html", SendHTML(false , false , false)); 
//}
//
//void handle_led3on() {
//  LED3status = LOW;
//  Serial.println("GPIO7 Status: ON");
//  server.send(200, "text/html", SendHTML(false , false , true)); 
//}
//
//void handle_led3off() {
//  LED3status = HIGH;
//  Serial.println("GPIO7 Status: OFF");
//  server.send(200, "text/html", SendHTML(false , false , false)); 
//}
//
//void handle_NotFound(){
//  server.send(404, "text/plain", "Not found");
//}
//
//String SendHTML(uint8_t Garage1stat , uint8_t led2stat , uint8_t led3stat){
//  String ptr = "<!DOCTYPE html> <html>\n";
//  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
//  ptr +="<title>LED Control</title>\n";
//  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
//  ptr +="body{margin-top: 50px;background-color: #bbbdc7 ; background-repeat: no-repeat; background-size: 100% 100%;} h1 {color: #106856;text-shadow: 10px 10px 10px #f8f7f8;margin: 50px auto 30px;} h2 {color: #34495e;margin-bottom: 50px;}\n";
//  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer; border-radius: 0px 10px 0px 10px;}\n";
//  ptr +=".button-on {background-color: #1abc9c;}\n";
//  ptr +=".button-on:active {background-color: #16a085;}\n";
//  ptr +=".button-off {background-color: #34495e;}\n";
//  ptr +=".button-off:active {background-color: #2c3e50;}\n";
//   ptr +=".button-on1 {background-color: #1abc9c;}\n";
//  ptr +=".button-on1:active {background-color: #16a085;}\n";
//  ptr +=".button-off1 {background-color: #34495e;}\n";
//  ptr +=".button-off1:active {background-color: #2c3e50;}\n";
//   ptr +=".button-on2 {background-color: #1abc9c;}\n";
//  ptr +=".button-on2:active {background-color: #16a085;}\n";
//  ptr +=".button-off2 {background-color: #34495e;}\n";
//  ptr +=".button-off2:active {background-color: #2c3e50;}\n";
//  ptr +="p {font-size: 14px;color:rgb(55, 75, 65);margin-bottom: 10px;}\n";
//  ptr +="</style>\n";
//  ptr +="</head>\n";
//  ptr +="<body>\n";
//  ptr +="<h1>Smart Home</h1>\n";
//  ptr +="<h3>Team 3</h3>\n";
//  
//   if(Garage1stat)
//  {ptr +="<p>Easy: Open</p><a class=\"button button-off\" href=\"/Garage close\">Close</a>\n";}
//   else {
//        ptr +="<p>Easy: Close</p><a class=\"button button-on\" href=\"/Garage Open\">Open</a>\n";
//   }
//      if(led2stat){
//  ptr +="<p>LED2 Status: ON</p><a class=\"button button-off1\" href=\"/led2off\">OFF</a>\n";}
//    else {
//
//
//   ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on1\" href=\"/led2on\">ON</a>\n";
//    }
//   if(led3stat){
//  ptr +="<p>LED3 Status: ON</p><a class=\"button button-off2\" href=\"/led3off\">OFF</a>\n";
//  }
//  else {
//  ptr +="<p>LED3 Status: OFF</p><a class=\"button button-on2\" href=\"/led3on\">ON</a>\n";
//  }
//  ptr +="</body>\n";
//  ptr +="</html>\n";
//  return ptr;
//}
