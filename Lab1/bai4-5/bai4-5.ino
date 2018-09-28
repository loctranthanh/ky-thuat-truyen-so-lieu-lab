#define LED 16
#define TIME_LED_ON 30
#define TIME_LED_OFF 50

enum state_t {
  INIT = 0,
  LED_ON,
  LED_OFF,
};

state_t state;
unsigned long count = 0;

void setup() {
  pinMode(LED, OUTPUT);  
  state = INIT;
}

void led_on() {
  digitalWrite(LED, LOW);
}

void led_off() {
  digitalWrite(LED, HIGH);
}

void loop() {
  switch (state) {
    case INIT:
      led_off();
      state = LED_OFF;
      break;
    case LED_OFF:
      if (count >= TIME_LED_OFF) {
        state = LED_ON;
        led_on();
        count = 0;
      }
      break;
    case LED_ON:
      if (count >= TIME_LED_ON) {
        state = LED_OFF;
        led_off();
        count = 0;
      }
      break;
  }
  count++;
  delay(10);
}
