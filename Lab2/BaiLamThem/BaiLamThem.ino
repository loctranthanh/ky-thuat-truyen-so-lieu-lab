#include <string.h>
#define NUMBER_KEY_CHECK  4
#define LED               16
#define DELAY_PER_LOOP    10
#define TIMEOUT           1000 / DELAY_PER_LOOP

enum state_t {
  INIT = 0,
  RECEIVE_CHAR,
  APPEND_CHAR,
  CHECK_CMD,
};

char cmd[4];
char c_read;
state_t state;
bool has_new_char = false;
int counting;

void led_on()
{
  digitalWrite(LED, LOW);
}

void led_off()
{
  digitalWrite(LED, HIGH);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  state = INIT;
  led_on();
  delay(1000);
  led_off();
}

// the loop function runs over and over again forever
void loop() {
  switch (state) {
    case INIT:
      memset(cmd, 0, 4);
      counting = -1;
      state = RECEIVE_CHAR;
      break;
    case RECEIVE_CHAR: 
      if (Serial.available()) {
        c_read = Serial.read();
        counting = 0;
        state = APPEND_CHAR;
        break;
      }
      if (counting >= 0) {
        counting++;
      }
      if (counting > TIMEOUT) {
        Serial.println("Timeout");
        state = INIT;
      }
      break;
    case APPEND_CHAR:
      if (c_read == '#') {
        state = CHECK_CMD;
      } else {
        for (int i = 0; i < NUMBER_KEY_CHECK - 1; i++) {
          cmd[i] = cmd[i+1];
        }
        cmd[NUMBER_KEY_CHECK - 1] = c_read; 
        state = RECEIVE_CHAR;
      }
      break;
    case CHECK_CMD:
      Serial.print("check command ");
      Serial.println(cmd);
      if (strcmp(cmd, "OPEN") == 0) {
        led_on();
      } else {
        led_off();
      }
      state = INIT;
      break;
  }
  delay(DELAY_PER_LOOP);
}
