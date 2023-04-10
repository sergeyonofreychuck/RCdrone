
struct button {
  int btn;
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

void (*buttonPressed)(int);

void setupUserInput() {
  buttons[RIGHT].pin = RIGHT_PIN;
  buttons[RIGHT].btn = RIGHT;
  buttons[LEFT].pin = LEFT_PIN;
  buttons[LEFT].btn = LEFT;
  buttons[UP].pin = UP_PIN;
  buttons[UP].btn = UP;
  buttons[DOWN].pin = DOWN_PIN;
  buttons[DOWN].btn = DOWN;
  buttons[CENTER].pin = CENTER_PIN;
  buttons[CENTER].btn = CENTER;
  buttons[SET].pin = SET_PIN;
  buttons[SET].btn = SET;
  buttons[RESET].pin = RESET_PIN;
  buttons[RESET].btn = RESET;
}

void readButton(struct button *btn, int newValue) {
  if (btn->state != newValue) {
    if (!newValue) {
      buttonPressed(btn->btn);
    }
  }
  btn->state = newValue;
}

void readUserInput() {
  for (int i = 0; i < 7; i++) {
    readButton(&buttons[i], !digitalRead(buttons[i].pin));
  }
}

void setupButtonsCallback(void (*callback)(int)) {
  buttonPressed = callback;
}

