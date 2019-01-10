
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


const char *ssid = "P436";  
const char *password = "436.436.436.123456";


const char *host = "api.thingspeak.com";
String apiKey = "RJRCCMIWU1NEMVFI";  


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);        
  WiFi.begin(ssid, password);  

  Serial.print("Connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client;          
  const int httpPort = 80; 
  
 if(!client.connect(host, httpPort)){
   Serial.println("Connection Failed");
   delay(300);
   return; 
 }
 
  String ADCData;
  int adcvalue=analogRead(A0);  
  ADCData = String(adcvalue);   
  String Link="GET /update?api_key="+apiKey+"&field1="; 
  Link = Link + ADCData;
  Link = Link + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";                
  client.print(Link);
  delay(100);
  
 int timeout=0;
 while((!client.available()) && (timeout < 1000))     
 {
   delay(10); 
   timeout++;
 }

//---------------------------------------------------------------------
 if(timeout < 500)
 {
     while(client.available()){
        Serial.println(client.readString()); 
     }
 }
 else
 {
     Serial.println("Request timeout..");
 }

 delay(5000);
}
