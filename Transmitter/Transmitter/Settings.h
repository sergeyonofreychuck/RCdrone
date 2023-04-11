#include <EEPROM.h>
#ifndef RC_SETTINGS
#define RC_SETTINGS

struct RcSetting {
  int id;
  int addr;
  float value;
  float min;
  float max;
  float step;
  float defaultValue;
};

RcSetting settings[2];

const int SETTING_TEST_1 = 1;
const int SETTING_TEST_2 = 2;

void createSetting(struct RcSetting *s, int id, float min, float max, float step, float defaultValue){
  s->id = id;
  s->addr = id*10;
  s->min = min;
  s->max = max;
  s->step = step;  
  s->defaultValue = defaultValue;
}

void initSettings() {
  createSetting(&settings[0], SETTING_TEST_1, 0, 2, 0.1, 1);
  createSetting(&settings[1], SETTING_TEST_2, -1, 2, 0.2, 0.6);
}

void initDefaults() {
  for (int i = 0; i < 2; i++) {
    RcSetting *s = &settings[i];
    EEPROM.put(s->addr, s->defaultValue);
  }  
}

void readSettings() {
  for (int i = 0; i < 2; i++) {
    RcSetting *s = &settings[i];
    float f = 0.00f;
    EEPROM.get(s->addr, f);
    s->value = f;
  }
}

#endif