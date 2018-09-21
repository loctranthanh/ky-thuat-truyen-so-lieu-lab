#define LED 16

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, LOW);
  delay(3000);
  digitalWrite(LED, HIGH);
  delay(1000);
}
