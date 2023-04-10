
struct button {
  int btn;
  int pin;
  int state = 0;
};

const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;
const int CENTER = 4;
const int SET = 5;
const int RESET = 6;

button buttons[7];

void (*buttonPressed)(int);

void setupUserInput() {
  buttons[RIGHT].pin = 24;
  buttons[RIGHT].btn = RIGHT;
  buttons[LEFT].pin = 26;
  buttons[LEFT].btn = LEFT;
  buttons[UP].pin = 29;
  buttons[UP].btn = UP;
  buttons[DOWN].pin = 27;
  buttons[DOWN].btn = DOWN;
  buttons[CENTER].pin = 25;
  buttons[CENTER].btn = CENTER;
  buttons[SET].pin = 22;
  buttons[SET].btn = SET;
  buttons[RESET].pin = 23;
  buttons[RESET].btn = RESET;
}

void readButton(struct button *btn, int newValue) {
  if (btn->state != newValue) {
    if (!newValue) {
      buttonPressed(btn->btn);
    }
    btn->state = newValue;
  }
}

void readUserInput() {
  for (int i = 0; i < 7; i++) {
    readButton(&buttons[i], !digitalRead(buttons[i].pin));
  }
}

void setupButtonsCallback(void (*callback)(int)) {
  buttonPressed = callback;
}

