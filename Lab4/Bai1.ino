#include <SoftwareSerial.h>
 
#define TX_PIN      0 //D3
#define RX_PIN      4 //D2
#define LED LED_BUILTIN
SoftwareSerial bluetooth(RX_PIN, TX_PIN);
int baudRate[] = {300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
 
void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
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
  if (bluetooth.available()) {
    char data_received;
      data_received = bluetooth.read();  
      if (data_received == '1')
      {
       digitalWrite(LED, LOW);
       bluetooth.write("LED turned ON\n");        
      }
      else if (data_received == '2')
      {
       digitalWrite(LED, HIGH);
       bluetooth.write("LED turned OFF\n");
      }
      else
      {
       bluetooth.write("Select either 1 or 2");
      }
    }
  }
