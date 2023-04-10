
struct button {
  int pin;
  int state = 0;
};

int RIGHT = 0;
int LEFT = 1;
int UP = 2;
int DOWN = 3;
int CENTER = 4;
int SET = 5;
int RESET = 6;

int RIGHT_PIN = 24;
int LEFT_PIN = 26;
int UP_PIN = 29;
int DOWN_PIN = 27;
int CENTER_PIN = 25;
int SET_PIN = 22;
int RESET_PIN = 23;

button buttons[7];

void setupUserInput() {
  buttons[RIGHT].pin = RIGHT_PIN;
  buttons[LEFT].pin = LEFT_PIN;
  buttons[UP].pin = UP_PIN;
  buttons[DOWN].pin = DOWN_PIN;
  buttons[CENTER].pin = CENTER_PIN;
  buttons[SET].pin = SET_PIN;
  buttons[RESET].pin = RESET_PIN;
}

void tst(int newValue) {

}

void readButton(struct button *btn, int newValue) {
  if (btn->state != newValue) {
    Serial.print(F("Value changed: "));
    Serial.println(newValue);
  }
  btn->state = newValue;
}

void readUserInput() {
  for (int i = 0; i < 7; i++) {
    readButton(&buttons[i], !digitalRead(buttons[i].pin));
  }
}

