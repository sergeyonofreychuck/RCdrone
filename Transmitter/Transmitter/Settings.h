#include <EEPROM.h>
#include "RcInputs.h"
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

RcSetting settings[15];
const int SETTINGS_SIZE = 15;

const int SETTING_HORIZONTAL_ZERO = 51;
const int SETTING_VERTICAL_ZERO = 52;
const int SETTING_RIGHT_LIMIT = 2;
const int SETTING_LEFT_LIMIT = 3;
const int SETTING_TOP_LIMIT = 4;
const int SETTING_BOTTOM_LIMIT = 5;
const int SETTING_THRUST_MIN = 6;
const int SETTING_THRUST_MAX = 7;

const int SETTING_RIGHT_SCALE = 8;
const int SETTING_LEFT_SCALE = 9;
const int SETTING_TOP_SCALE = 10;
const int SETTING_BOTTOM_SCALE = 11;
const int SETTING_THRUST_SCALE = 12;
const int SETTING_RIGHT_START = 13;
const int SETTING_LEFT_START = 14;

void createSetting(struct RcSetting *s, int id, float min, float max, float step, float defaultValue){
  s->id = id;
  s->addr = id*4;
  s->min = min;
  s->max = max;
  s->step = step;  
  s->defaultValue = defaultValue;
}

void initSettings() {
  createSetting(&settings[0], SETTING_HORIZONTAL_ZERO, 0, 1023, 1, 511);
  createSetting(&settings[1], SETTING_VERTICAL_ZERO, 0, 1023, 1, 511);
  createSetting(&settings[2], SETTING_RIGHT_LIMIT, 0, 1023, 1, 1023);
  createSetting(&settings[3], SETTING_LEFT_LIMIT, 0, 1023, 1, 0);
  createSetting(&settings[4], SETTING_TOP_LIMIT, 0, 1023, 1, 0);
  createSetting(&settings[5], SETTING_BOTTOM_LIMIT, 0, 1023, 1, 1023);
  createSetting(&settings[6], SETTING_THRUST_MIN, 0, 1023, 1, 0);
  createSetting(&settings[7], SETTING_THRUST_MAX, 0, 1023, 1, 1023);
  createSetting(&settings[8], SETTING_RIGHT_SCALE, 0, 100, 10, 100);
  createSetting(&settings[9], SETTING_LEFT_SCALE, 0, 100, 10, 100);
  createSetting(&settings[10], SETTING_TOP_SCALE, 0, 100, 10, 100);
  createSetting(&settings[11], SETTING_BOTTOM_SCALE, 0, 100, 10, 100);
  createSetting(&settings[12], SETTING_THRUST_SCALE, 0, 100, 5, 100);
  createSetting(&settings[13], SETTING_RIGHT_START, 0, 100, 1, 50);
  createSetting(&settings[14], SETTING_LEFT_START, 0, 100, 1, 50);
}

void initDefaults() {
  for (int i = 0; i < SETTINGS_SIZE; i++) {
    RcSetting *s = &settings[i];
    EEPROM.put(s->addr, s->defaultValue);
  }  
}

void readSettings() {
  for (int i = 0; i < SETTINGS_SIZE; i++) {
    RcSetting *s = &settings[i];
    float f = 0.00f;
    EEPROM.get(s->addr, f);
    s->value = f;
  }
}

RcSetting* getSetting(int id) {
  Serial.print("getSetting ");
  Serial.println(id);
  for (int i = 0; i < SETTINGS_SIZE; i++) {
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

void updateSetting(int id, float value) {
  RcSetting *s = getSetting(id);
  if (value < s->min || value > s->max) {
      Serial.print("ERROR: updating value not in range");
      Serial.println(id);
      Serial.println(value);
  }
  EEPROM.put(s->addr, value);
  readSettings();
}

void actionSetZeros() {
  updateSetting(SETTING_HORIZONTAL_ZERO, inputsYControl);  
  updateSetting(SETTING_VERTICAL_ZERO, inputsZControl);  
}

void actionSetRightLimit() {
  updateSetting(SETTING_RIGHT_LIMIT, inputsYControl);  
}

void actionSetLeftLimit() {
  updateSetting(SETTING_LEFT_LIMIT, inputsYControl); 
}

void actionSetTopLimit() {
  updateSetting(SETTING_TOP_LIMIT, inputsZControl); 
}

void actionSetBottomLimit() {
  updateSetting(SETTING_BOTTOM_LIMIT, inputsZControl); 
}

void actionSetThrustMin() {
  updateSetting(SETTING_THRUST_MIN, inputsThrustControl); 
}

void actionSetThrustMax() {
  updateSetting(SETTING_THRUST_MAX, inputsThrustControl); 
}

void actionSetDefaults() {
  initDefaults(); 
}

#endif