#define LED         16
#define TIME_WAIT   5000

enum state_t {
  INIT = 0,
  NORMAL,
  READ_CHAR_O,
};

state_t state;
unsigned long t_begin = 0;
String in = "";

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void led_on() {
  digitalWrite(LED, LOW);
}

void led_off() {
  digitalWrite(LED, HIGH);
}

void loop() {
  char c = 0;
  if (Serial.available()) {
    c = Serial.read();
  }
  switch (state) {
    case INIT:
      state = NORMAL;
    case NORMAL:
      if (c == 'O') {
        in = "O";
        state = READ_CHAR_O;
        t_begin = millis();
      }
      break;
    case READ_CHAR_O:
      if (millis() - t_begin > TIME_WAIT) {
        state = NORMAL;
        in = "";
      } else if (c != 0) {
        if (c == 'O') {
          t_begin = millis();
          in = 'O';
        } else {
          in += c;
          if (in == "ON") {
            led_on();
            state = NORMAL;
          } else if (in == "OFF") {
            led_off();
            state = NORMAL;
          }
        }
      }
      break;
  }
}
