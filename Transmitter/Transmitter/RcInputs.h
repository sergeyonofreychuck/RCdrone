#ifndef RC_INPUTTS
#define RC_INPUTTS


int inputsYControl = 0;
int inputsZControl = 0;
int inputsThrustControl = 0;
int inputsLeftClick = 0;
int inputsRightClick = 0;

void readRcControls() {
  inputsRightClick = digitalRead(5);
  inputsLeftClick = digitalRead(4);
  inputsThrustControl = analogRead(A1);
  inputsYControl = analogRead(A3);
  inputsZControl = analogRead(A5);
}

#endif