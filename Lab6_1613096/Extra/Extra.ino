#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "html.h" //My HTML
#include <string.h>

#define LED LED_BUILTIN  //On board LED

String payload;
String strDate,strH,strM,strSec,strTime,temp;
const char* ssid = "P436";
const char* password = "436.436.436.123456";

ESP8266WebServer server(80); //Server on port 80

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void handleTime(){
  HTTPClient http;
 http.begin("http://www.iforce2d.net/test.php");  
 int httpCode = http.GET(); 
 String payload;
 if (httpCode > 0) {
    payload = http.getString();  
    Serial.println(payload);                  
 }
 http.end();
}
void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate");
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(LED,LOW); //LED ON
  ledState = "ON"; //Feedback parameter
 }
 else
 {
  digitalWrite(LED,HIGH); //LED OFF
  ledState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", ledState); //Send web page
}

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  pinMode(LED,OUTPUT); 
  
  // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      
  server.on("/setLED", handleLED);
  //server.on("/readADC", handleADC);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}


void loop(void){
 server.handleClient();       
 HTTPClient http;
 http.begin("http://www.iforce2d.net/test.php");  
 int httpCode = http.GET(); 
 if (httpCode > 0) {
    payload = http.getString();  
    Serial.println(payload);                 
 }
 http.end();   //Close connection
 
 strDate=payload.substring(13,24);
 strH=payload.substring(25,26);
 strM=payload.substring(27,28);
 temp=payload.substring(26,32);
 strSec=payload.substring(30,32);
 
 if(strH.toInt()<=57){
 int strInt=strH.toInt()+7;
 strH=String(strHinNew);
 strTime=strH+temp;
 }
 else{
  int strInt=strH.toInt()+7;
 strH=String(strHinNew);
 strTime=strH+":"+temp;
 }

 server.on("/timeVN",[](){
    server.send(200,"text/plane",strTime);
  });
}
