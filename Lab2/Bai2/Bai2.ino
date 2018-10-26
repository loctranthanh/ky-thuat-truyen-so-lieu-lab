#define LED 16

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'O') {
      digitalWrite(LED, LOW);
    } else if (c == 'F') {
      digitalWrite(LED, HIGH);
    }
  }
}
