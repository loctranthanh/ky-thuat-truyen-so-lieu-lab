#define LED 16
#define TIME_LED_ON 30
#define TIME_LED_OFF 50

enum state_t {
  LED_ON = 0,
  LED_OFF,
};

state_t state;
unsigned long count = 0;

void setup() {
  pinMode(LED, OUTPUT);  
  digitalWrite(LED, HIGH);
  state = LED_OFF;
}

void loop() {
  switch (state) {
    case LED_OFF:
      if (count >= TIME_LED_OFF) {
        state = LED_ON;
        digitalWrite(LED, LOW);
        count = 0;
      }
      break;
    case LED_ON:
      if (count >= TIME_LED_ON) {
        state = LED_OFF;
        digitalWrite(LED, HIGH);
        count = 0;
      }
      break;
  }
  count++;
  delay(10);
}
