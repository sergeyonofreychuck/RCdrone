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

RcSetting settings[3];

const int SETTING_TEST_1 = 1;
const int SETTING_TEST_2 = 2;
const int SETTING_TEST_3 = 3;

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
  createSetting(&settings[2], SETTING_TEST_3, 1, 5, 0.5, 2);
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

RcSetting* getSetting(int id) {
  Serial.print("getSetting ");
  Serial.println(id);
  for (int i = 0; i < 3; i++) {
    RcSetting *current = &settings[i];
    if (current->id == id) {
      return current;
    }        
  }
  return &settings[0];
}

float getSettingValue(int id) {
  RcSetting *setting = getSetting(id);
  Serial.print("getSettingValue ");
  Serial.println(setting->value);
  return setting->value;
}

#endif