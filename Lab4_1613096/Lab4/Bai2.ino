#include <SoftwareSerial.h>
#include<String.h>
#define TX_PIN      0
#define RX_PIN      4
#define LED LED_BUILTIN
SoftwareSerial bluetooth(RX_PIN, TX_PIN);
int baudRate[] = {300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
String myStr;
void setup() {
  myStr="";
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.begin(9600);
  while (!Serial) {}
  
  Serial.println("Configuring, please wait...");
  
  for (int i = 0 ; i < 9 ; i++) {
     bluetooth.begin(baudRate[i]);
     String cmd = "AT+BAUD4";
     bluetooth.print(cmd);
     bluetooth.flush();
     delay(100);
  }
  
  bluetooth.begin(9600);
  Serial.println("Config done");
  while (!bluetooth) {}
  Serial.println("Enter AT commands:");
}
 
void loop() {
  while (bluetooth.available()) {
    char temp;
    temp=bluetooth.read();
//    if(temp!='\n'){
      String tempStr=String(temp);  
      myStr=myStr+tempStr;
//    }
    Serial.println(myStr);
  }
  if(myStr=="OFF") {Serial.println("HELLO\n"); myStr="";digitalWrite(LED_BUILTIN,HIGH);}
  else if(myStr=="ON"){Serial.println("HELLO ON\n"); myStr="";digitalWrite(LED_BUILTIN,LOW);}
//      if(myStr=="ON") Serial.println("HELLO\n");
//   if(myStr=="ON"){
//      digitalWrite(LED_BUILTIN,LOW);
//      Serial.println(myStr);
//      myStr="";
//    }
//    else if(myStr=="OFF"){
//      digitalWrite(LED_BUILTIN,HIGH);
//      Serial.println(myStr);
//      myStr="";
//    }
//    else{myStr="";}
}
