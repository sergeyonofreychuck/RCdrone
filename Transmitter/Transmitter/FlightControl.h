#ifndef FLIGHT_CONTROL
#define FLIGHT_CONTROL

float applyLimit(float value, int minLimit, int maxLimit);
float mapValue(float value, int min, int max, int scale);

struct FlightControl {
  int type;
  int val1;
  int val2;
  int val3;
  int val4;
};

struct DirControl {
  int r;
  int l;
  int t;
};

DirControl DIR_CONTROL;

void readDirControl() {
  Serial.println("readDirControl");
  float r = 0;
  float l = 0;
  float t = 0;
  if (RC_ANALOGS.y > getSettingValue(SETTING_HORIZONTAL_ZERO)) {
    Serial.println("1");
    int incl = mapValue(
      RC_ANALOGS.y,
      getSettingValue(SETTING_HORIZONTAL_ZERO),
      getSettingValue(SETTING_RIGHT_CONTROL_LIMIT),
      getSettingValue(SETTING_RIGHT_SCALE)
    );
    r = -1 * incl;
    l = incl;
  } else {
    Serial.println("2");
    int incl = mapValue(
      RC_ANALOGS.y,
      getSettingValue(SETTING_HORIZONTAL_ZERO),
      getSettingValue(SETTING_LEFT_CONTROL_LIMIT),
      getSettingValue(SETTING_LEFT_SCALE)
    );
    r = incl;
    l = -1 * incl;    
  }

  Serial.println(r);
  Serial.println(l);

  if (RC_ANALOGS.z > getSettingValue(SETTING_VERTICAL_ZERO)) {
    Serial.println("3");
    int incl = mapValue(
      RC_ANALOGS.z,
      getSettingValue(SETTING_VERTICAL_ZERO),
      getSettingValue(SETTING_BOTTOM_CONTROL_LIMIT),
      getSettingValue(SETTING_BOTTOM_SCALE)
    );
    r = r+incl;
    l = l+incl;
  } else {
    Serial.println("4");
    int incl = mapValue(
      RC_ANALOGS.z,
      getSettingValue(SETTING_VERTICAL_ZERO),
      getSettingValue(SETTING_TOP_CONTROL_LIMIT),
      getSettingValue(SETTING_TOP_SCALE)
    );
    r = r-incl;
    l = l-incl;
  }

  Serial.println(r);
  Serial.println(l);

  Serial.println("5");

  r += getSettingValue(SETTING_RIGHT_SHIFT);
  l += getSettingValue(SETTING_LEFT_SHIFT);

  Serial.println(r);
  Serial.println(l);

  t = mapValue(
      RC_ANALOGS.t,
      getSettingValue(SETTING_THRUST_MIN),
      getSettingValue(SETTING_THRUST_MAX),
      getSettingValue(SETTING_THRUST_SCALE)
    );

  Serial.println(t);

  Serial.println("lim");

  r = applyLimit(r, -1*getSettingValue(SETTING_RIGHT_BOTTOM_LIMIT), getSettingValue(SETTING_RIGHT_TOP_LIMIT));
  l = applyLimit(l, -1*getSettingValue(SETTING_LEFT_BOTTOM_LIMIT), getSettingValue(SETTING_LEFT_TOP_LIMIT));

  Serial.println(r);
  Serial.println(l);
  Serial.println(t);

  DIR_CONTROL.r = r;
  DIR_CONTROL.l = l;
  DIR_CONTROL.t = t;
}

float applyLimit(float value, int minLimit, int maxLimit) {
  if (value < minLimit) {
    value = minLimit;
  }
  if (value > maxLimit) {
    value = maxLimit;
  }
}

float mapValue(float value, int min, int max, int scale) {
  return map(value, min, max, 0, 100)*100/scale;
}

#endif