#include "ESP8266WiFi.h"
char choice[10];
char pass[50];
char ssid[50];
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");

  ////////////////////
  Serial.println("scan start");
  
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.print("Enter your choice: ");
  while (Serial.available() == 0) {
    // wait
  }
  
  Serial.readBytesUntil(10, choice, 10);
  Serial.println(choice);
  
  int myChoice=atoi(choice);
  for(int i=0;i<n;++i){
      if(myChoice==i){
          Serial.println("Your choice: " + WiFi.SSID(i-1));
          int myLength=WiFi.SSID(i-1).length();
          WiFi.SSID(i-1).toCharArray(ssid,myLength+1);
        }
    }
  Serial.println("Enter the password: ");
  while (Serial.available() == 0) {
    // wait
  }
  Serial.readBytesUntil(10, pass, 50);

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
