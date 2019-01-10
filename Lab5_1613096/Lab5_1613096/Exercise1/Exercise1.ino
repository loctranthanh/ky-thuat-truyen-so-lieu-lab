#include <ESP8266WiFi.h>

#define BAUDRATE 9600

char ssid[50];
char pass[50];
String mySsid, myPass;
void setup() {
  Serial.begin(BAUDRATE);
  Serial.println();
  Serial.println("Enter your WiFi credentials.\n");
  Serial.print("SSID: ");
  while (Serial.available() == 0) {
    // wait
  }
  Serial.readBytesUntil(10, ssid, 50);

  Serial.println(ssid);

  Serial.print("PASS: ");
  while (Serial.available() == 0) {
    // wait
  }
  Serial.readBytesUntil(10, pass, 50);
  Serial.println(pass);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

}
