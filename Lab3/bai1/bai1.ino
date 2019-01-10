#include <M5Stack.h>
HardwareSerial mySerial(2);
int _timeout;
String _buffer;
String number = "+84962230200";
void setup() {
//  delay(7000); //delay for 7 seconds to make sure the modules get the signal
  M5.begin();
  Serial.begin(9600);
  Serial.println("Sistem Started...");
  mySerial.begin(9600, SERIAL_8N1, 16, 17);
  delay(1000);
  SendMessage();
  delay(10000);
}
void loop() {
  
}
void SendMessage()
{
  Serial.println ("Check Module");
  mySerial.println("AT");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Sending Message");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  mySerial.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Hello";
  mySerial.println(SMS);
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
//  mySerial.println("AT+SAPBR=1,1");    
//  delay(1000);
//  mySerial.println("AT+HTTPINIT"); 
//  delay(1000);
//  mySerial.println("AT+HTTPPARA=\"CID\",1"); 
//  delay(1000);
//  mySerial.println("AT+HTTPPARA=\"URL\",\"http://www.iforce2d.net/test.php\""); 
//  delay(1000);
//  mySerial.println("AT+HTTPACTION=0");
//  delay(1000);
//  mySerial.println("AT+HTTPREAD");
//  delay(1000);
//  mySerial.println("AT+HTTPTERM");
//  delay(1000);
  _buffer = _readSerial();
  Serial.println (_buffer);
}
String _readSerial() {
  _timeout = 0;
  while  (!mySerial.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (mySerial.available()) {
    return mySerial.readString();
  }
}
