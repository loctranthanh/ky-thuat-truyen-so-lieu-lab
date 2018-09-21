#define LED             16
#define BUTTON          0
#define DELAY_TIME      10
#define TIME_OPEN_DOOR  (3000 / DELAY_TIME)

enum state_t {
  OPEN_DOOR = 0,
  CLOSE_DOOR,
};

state_t state;
unsigned long count;
bool counting_enable;
bool sensor_state;

void open_door() {
  digitalWrite(LED, LOW);
}

void close_door() {
  digitalWrite(LED, HIGH);
}

void setup() {
  pinMode(LED, OUTPUT);  
  close_door();
  pinMode(BUTTON, INPUT);
  state = CLOSE_DOOR;
  sensor_state = false;
  counting_enable = false;
  count = 0;
}

void loop() {
  sensor_state = (digitalRead(BUTTON) == 0) ? true : false;
  switch (state) {
    case CLOSE_DOOR:
      if (sensor_state) {
        open_door();
        state = OPEN_DOOR;
        count = 0;
        counting_enable = true;
      } else {
        close_door();
        counting_enable = false;
      }
      break;
    case OPEN_DOOR:
      if (sensor_state) {
        count = 0;
        break;
      }
      if (count > TIME_OPEN_DOOR) {
        state = CLOSE_DOOR;
      }
      break;
  }
  if (counting_enable) {
    count++;
  }
  delay(DELAY_TIME);
}
