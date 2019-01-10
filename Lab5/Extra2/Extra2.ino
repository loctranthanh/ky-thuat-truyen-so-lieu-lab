#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define ssid "P436"
#define password "436.436.436.123456"

#define mqtt_server "m15.cloudmqtt.com" /
#define mqtt_topic_pub "demo"   
#define mqtt_topic_sub "demo"
#define mqtt_user "tnsotidt"    
#define mqtt_pwd "U2maRry45asS"

const uint16_t mqtt_port = 14286; 
#define ledPin LED_BUILTIN
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); 
  client.setCallback(callback);
  pinMode(ledPin, OUTPUT);
}
// Hàm kết nối wifi
void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    char receivedChar = (char)payload[i];
    Serial.print(receivedChar);
    if (receivedChar == '1')
      digitalWrite(ledPin, HIGH);
    if (receivedChar == '0')
      digitalWrite(ledPin, LOW);
  }
  Serial.println();
}

void reconnect() {
  // Chờ tới khi kết nối
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client",mqtt_user, mqtt_pwd)) {
      Serial.println("connected");
      client.publish(mqtt_topic_pub, "ESP_reconnected");
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
