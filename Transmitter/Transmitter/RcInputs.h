#ifndef RC_INPUTTS
#define RC_INPUTTS

struct RcAnalogs {
  int y;
  int z;
  int t;
  int leftClick;
  int rightClick;
};

RcAnalogs RC_ANALOGS;

void readRcControls() {
  RC_ANALOGS.y = analogRead(A3);
  RC_ANALOGS.z = analogRead(A5);
  RC_ANALOGS.t = analogRead(A1);
  RC_ANALOGS.leftClick = !digitalRead(4);
  RC_ANALOGS.rightClick = !digitalRead(5);
  // Serial.println("Read Analogs ");
  // Serial.println(RC_ANALOGS.leftClick);
  // Serial.println(RC_ANALOGS.rightClick);
}

#endif