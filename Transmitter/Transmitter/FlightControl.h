#ifndef FLIGHT_CONTROL
#define FLIGHT_CONTROL

float applyLimit(float value, int minLimit, int maxLimit);
float mapValue(float value, int min, int max, int scale);
void readUserControl();

const int FLIGHT_CONTROL_TYPE_DIRECTION = 0;

struct FlightControl {
  int id;
  int type;
  int val1;
  int val2;
  int val3;
  int val4;
  int checksum;
};

struct FlightDirControl {
  int r;
  int l;
  int t;
  int stop;
};

struct UserControl {
  float horizontal;
  float vertical;
  float thrust;
};

FlightDirControl FLIGHT_DIR_CONTROL;
FlightControl FLIGHT_CONTROL_STRUCT;
FlightControl FLIGHT_CONTROL_ACK;
UserControl USER_CONTROL;

void constructDirControl() {
  FLIGHT_CONTROL_STRUCT.id++;
  FLIGHT_CONTROL_STRUCT.type = FLIGHT_CONTROL_TYPE_DIRECTION;
  FLIGHT_CONTROL_STRUCT.val1 = FLIGHT_DIR_CONTROL.r;
  FLIGHT_CONTROL_STRUCT.val2 = FLIGHT_DIR_CONTROL.l;
  FLIGHT_CONTROL_STRUCT.val3 = FLIGHT_DIR_CONTROL.t;
  FLIGHT_CONTROL_STRUCT.val4 = FLIGHT_DIR_CONTROL.stop;
  FLIGHT_CONTROL_STRUCT.checksum = 
    FLIGHT_CONTROL_STRUCT.id +
    FLIGHT_CONTROL_STRUCT.type + 
    FLIGHT_CONTROL_STRUCT.val1 +
    FLIGHT_CONTROL_STRUCT.val2 +
    FLIGHT_CONTROL_STRUCT.val3 +
    FLIGHT_CONTROL_STRUCT.val4;
}

void readUserControl() {
  // Serial.println("============");
  // Serial.println("readUserControl");
  // Serial.println(RC_ANALOGS.y);
  // Serial.println(RC_ANALOGS.z);
  // Serial.println(RC_ANALOGS.t);
  float incl = 0;
  float thrust = 0;

  if (RC_ANALOGS.y < getSettingValue(SETTING_HORIZONTAL_ZERO)) {
    //Serial.println("==right");
    USER_CONTROL.horizontal = map(
      RC_ANALOGS.y, 
      getSettingValue(SETTING_HORIZONTAL_ZERO), 
      getSettingValue(SETTING_RIGHT_CONTROL_LIMIT), 
      0, 
      100);
  } else {
    //Serial.println("==left");
    USER_CONTROL.horizontal = map(
      RC_ANALOGS.y, 
      getSettingValue(SETTING_HORIZONTAL_ZERO), 
      getSettingValue(SETTING_LEFT_CONTROL_LIMIT), 
      0, 
      100)*-1;
  }  

  // Serial.println("-horizontal");
  // Serial.println(USER_CONTROL.horizontal);


  if (RC_ANALOGS.z > getSettingValue(SETTING_VERTICAL_ZERO)) {
    // Serial.println("==top");
    USER_CONTROL.vertical = map(
      RC_ANALOGS.z, 
      getSettingValue(SETTING_VERTICAL_ZERO), 
      getSettingValue(SETTING_TOP_CONTROL_LIMIT), 
      0, 
      100);
  } else {
    // Serial.println("==bottom");
    USER_CONTROL.vertical = map(
      RC_ANALOGS.z, 
      getSettingValue(SETTING_VERTICAL_ZERO), 
      getSettingValue(SETTING_BOTTOM_CONTROL_LIMIT), 
      0, 
      100)*-1;
  }

  // Serial.println("--vertical");
  // Serial.println(USER_CONTROL.vertical);

  USER_CONTROL.thrust = map(
    RC_ANALOGS.t, 
    getSettingValue(SETTING_THRUST_MIN), 
    getSettingValue(SETTING_THRUST_MAX), 
    0, 
    100);

  // Serial.println("--thrust");
  // Serial.println(USER_CONTROL.thrust);
}

void readDirControl() {
  readUserControl();
  // Serial.print("readDirControl  ");
  // Serial.print(USER_CONTROL.horizontal);
  // Serial.print("  ");
  // Serial.print(USER_CONTROL.vertical);
  // Serial.print("  ");
  // Serial.println(USER_CONTROL.thrust);

  float r = 0;
  float l = 0;
  float incl = 0;

  if (USER_CONTROL.horizontal > 0) { //right
    incl = USER_CONTROL.horizontal * getSettingValue(SETTING_RIGHT_SCALE) / 100;
    r += incl*getSettingValue(SETTING_TURN_SCALE)/100;
    l += incl*getSettingValue(SETTING_TURN_OPS_SCALE)/100;
  } else { // left
    incl = USER_CONTROL.horizontal * getSettingValue(SETTING_LEFT_SCALE) / 100;
    l += -1* incl*getSettingValue(SETTING_TURN_SCALE)/100;
    r += -1* incl*getSettingValue(SETTING_TURN_OPS_SCALE)/100;
  }

  // Serial.println("-horizontal");
  // Serial.println(r);
  // Serial.println(l);

  if (USER_CONTROL.vertical > 0) { //top
    incl = USER_CONTROL.vertical * getSettingValue(SETTING_TOP_SCALE) / 100;
  } else {
    incl = USER_CONTROL.vertical * getSettingValue(SETTING_BOTTOM_SCALE) / 100;
  }
  r += incl;
  l += incl;
  // Serial.println("--vertical");
  // Serial.println(r);
  // Serial.println(l);

  r += getSettingValue(SETTING_RIGHT_SHIFT);
  l += getSettingValue(SETTING_LEFT_SHIFT);

  // Serial.println("==shift");
  // Serial.println(r);
  // Serial.println(l);

  r = applyLimit(r, -1*getSettingValue(SETTING_RIGHT_BOTTOM_LIMIT), getSettingValue(SETTING_RIGHT_TOP_LIMIT));
  l = applyLimit(l, -1*getSettingValue(SETTING_LEFT_BOTTOM_LIMIT), getSettingValue(SETTING_LEFT_TOP_LIMIT));

  // Serial.println("==lim");
  // Serial.println(r);
  // Serial.println(l);

  FLIGHT_DIR_CONTROL.r = r;
  FLIGHT_DIR_CONTROL.l = l;
  FLIGHT_DIR_CONTROL.t = USER_CONTROL.thrust * getSettingValue(SETTING_THRUST_SCALE) / 100;

  // Serial.println(FLIGHT_DIR_CONTROL.t);

  if (getSettingValue(SETTING_CLICKS_TO_STOP) == 1) {
    FLIGHT_DIR_CONTROL.stop = RC_ANALOGS.leftClick || RC_ANALOGS.rightClick;  
  } else {
    FLIGHT_DIR_CONTROL.stop = RC_ANALOGS.leftClick && RC_ANALOGS.rightClick;  
  }

  // Serial.println(FLIGHT_DIR_CONTROL.stop);

}

float applyLimit(float value, int minLimit, int maxLimit) {
  if (value < minLimit) {
    return minLimit;
  }
  if (value > maxLimit) {
    return maxLimit;
  }

  return value;
}

void printFlightControl(FlightControl *flightControl) {
  Serial.print("FlightControl id:");
  Serial.print(flightControl->id);
  Serial.print(" type:"); 
  Serial.print(flightControl->type);
  Serial.print(" val1:"); 
  Serial.print(flightControl->val1);
  Serial.print(" val2:"); 
  Serial.print(flightControl->val2);
  Serial.print(" val3:"); 
  Serial.print(flightControl->val3);
  Serial.print(" val4:"); 
  Serial.println(flightControl->val4);
}

#endif