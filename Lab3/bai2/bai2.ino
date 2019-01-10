#include <M5Stack.h>
HardwareSerial mySerial(2);
int _timeout;
String _buffer;
String number = "+84326577774";

int uart_read_bytes(char *recv_buffer, int timeout)
{
  int ret = 0;
  unsigned long t = millis();
  char rec[100];
  while (1) {
    if (mySerial.available()) {
      char c_read = mySerial.read();
      if (c_read == 0)
        continue;
      ret++;
      rec[ret] = c_read;
    }
    if (millis() - t > timeout) {
      break;
    }
  }
  memcpy(recv_buffer, rec, ret);
  return ret;
}

static bool _at_and_get_response(const char *cmd, char *out, int timeout, int retry)
{
  char recv_buffer[100];
  do {
    Serial.print("Write cmd: ");
    Serial.println(cmd);
    mySerial.println(cmd);
    int len = uart_read_bytes(recv_buffer, timeout);
    if (len > 0) {
      recv_buffer[len] = 0;
      Serial.print("Recv: ");
      Serial.println(recv_buffer);
      memcpy(out, recv_buffer, len);
      return true;
    }

    if (retry > 0) {
      retry --;
    }
  } while (retry);
  return false;
}

static bool _at_and_expect(const char *cmd, const char *expect, int timeout, int retry)
{
  int _retry = retry;
  char out[100];
  do {
    if (_at_and_get_response(cmd, out, timeout, 1)) {
      if (strstr(out, expect) != NULL) {
        return true;
      }
    }

    if (retry > 0) {
      retry --;
    }
  } while (retry);
  return false;
}

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
  while (1) {
    if (!_at_and_expect("AT", "OK", 2000, 3)) {
      Serial.println("AT fail");
      continue;
    }
    if (!_at_and_expect("AT+CMGF=1", "OK", 2000, 3)) {
      Serial.println("AT+CMGF=1 fail");
      continue;
    }
    if (!_at_and_expect("AT+CMGS=\"+84326577774\"", ">", 2000, 3)) {
      Serial.println("Set phone number fail");
      continue;
    }
    mySerial.print("Hello, this is ToRight");
    delay(100);
    mySerial.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    break;
  }
}
//void SendMessage()
//{
//  Serial.println ("Check Module");
//  mySerial.println("AT");    //Sets the GSM Module in Text Mode
//  delay(1000);
//  Serial.println ("Sending Message");
//  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
//  delay(1000);
//  Serial.println ("Set SMS Number");
//  mySerial.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
//  delay(1000);
//  String SMS = "Hello";
//  mySerial.println(SMS);
//  delay(100);
//  mySerial.println((char)26);// ASCII code of CTRL+Z
//  delay(1000);
////  mySerial.println("AT+SAPBR=1,1");
////  delay(1000);
////  mySerial.println("AT+HTTPINIT");
////  delay(1000);
////  mySerial.println("AT+HTTPPARA=\"CID\",1");
////  delay(1000);
////  mySerial.println("AT+HTTPPARA=\"URL\",\"http://www.iforce2d.net/test.php\"");
////  delay(1000);
////  mySerial.println("AT+HTTPACTION=0");
////  delay(1000);
////  mySerial.println("AT+HTTPREAD");
////  delay(1000);
////  mySerial.println("AT+HTTPTERM");
////  delay(1000);
//  _buffer = _readSerial();
//  Serial.println (_buffer);
//}
//String _readSerial() {
//  _timeout = 0;
//  while  (!mySerial.available() && _timeout < 12000  )
//  {
//    delay(13);
//    _timeout++;
//  }
//  if (mySerial.available()) {
//    return mySerial.readString();
//  }
//}
