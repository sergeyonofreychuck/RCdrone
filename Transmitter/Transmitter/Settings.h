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

RcSetting settings[22];
const int SETTINGS_SIZE = 22;
int addSettingCounter = 0;

const int SETTING_HORIZONTAL_ZERO = 0;
const int SETTING_VERTICAL_ZERO = 1;
const int SETTING_RIGHT_CONTROL_LIMIT = 2;
const int SETTING_LEFT_CONTROL_LIMIT = 3;
const int SETTING_TOP_CONTROL_LIMIT = 4;
const int SETTING_BOTTOM_CONTROL_LIMIT = 5;
const int SETTING_THRUST_MIN = 6;
const int SETTING_THRUST_MAX = 7;

const int SETTING_RIGHT_SCALE = 8;
const int SETTING_LEFT_SCALE = 9;
const int SETTING_TOP_SCALE = 10;
const int SETTING_BOTTOM_SCALE = 11;
const int SETTING_THRUST_SCALE = 12;
const int SETTING_TURN_SCALE = 13;
const int SETTING_TURN_OPS_SCALE = 14;

const int SETTING_RIGHT_SHIFT = 15;
const int SETTING_LEFT_SHIFT = 16;

const int SETTING_RIGHT_TOP_LIMIT = 17;
const int SETTING_RIGHT_BOTTOM_LIMIT = 18;
const int SETTING_LEFT_TOP_LIMIT = 19;
const int SETTING_LEFT_BOTTOM_LIMIT = 20;
const int SETTING_CLICKS_TO_STOP = 21;

void createSetting(int id, float min, float max, float step, float defaultValue){
  RcSetting *s = settings + addSettingCounter;
  addSettingCounter++;
  s->id = id;
  s->addr = id*4;
  s->min = min;
  s->max = max;
  s->step = step;  
  s->defaultValue = defaultValue;
}

void initSettings() {
  createSetting(SETTING_HORIZONTAL_ZERO, 0, 1023, 1, 511);
  createSetting(SETTING_VERTICAL_ZERO, 0, 1023, 1, 511);
  createSetting(SETTING_RIGHT_CONTROL_LIMIT, 0, 1023, 1, 0);
  createSetting(SETTING_LEFT_CONTROL_LIMIT, 0, 1023, 1, 1023);
  createSetting(SETTING_TOP_CONTROL_LIMIT, 0, 1023, 1, 1023);
  createSetting(SETTING_BOTTOM_CONTROL_LIMIT, 0, 1023, 1, 0);
  createSetting(SETTING_THRUST_MIN, 0, 1023, 1, 0);
  createSetting(SETTING_THRUST_MAX, 0, 1023, 1, 1023);

  createSetting(SETTING_RIGHT_SCALE, 0, 100, 10, 100);
  createSetting(SETTING_LEFT_SCALE, 0, 100, 10, 100);
  createSetting(SETTING_TOP_SCALE, 0, 100, 10, 100);
  createSetting(SETTING_BOTTOM_SCALE, 0, 100, 10, 100);
  createSetting(SETTING_THRUST_SCALE, 0, 100, 5, 100);
  createSetting(SETTING_TURN_SCALE, -100, 100, 10, 100);
  createSetting(SETTING_TURN_OPS_SCALE, -100, 100, 10, 0);

  createSetting(SETTING_RIGHT_SHIFT, -100, 100, 2, 0);
  createSetting(SETTING_LEFT_SHIFT, -100, 100, 2, 0);

  createSetting(SETTING_RIGHT_TOP_LIMIT, 0, 100, 10, 100);
  createSetting(SETTING_RIGHT_BOTTOM_LIMIT, 0, 100, 10, 100);
  createSetting(SETTING_LEFT_TOP_LIMIT, 0, 100, 10, 100);
  createSetting(SETTING_LEFT_BOTTOM_LIMIT, 0, 100, 10, 100);

  createSetting(SETTING_CLICKS_TO_STOP, 1, 2, 1, 2); 
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
  //Serial.print("getSetting ");
  //Serial.println(id);
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
  // Serial.print("getSettingValue ");
  // Serial.println(setting->value);
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
  updateSetting(SETTING_HORIZONTAL_ZERO, RC_ANALOGS.y);  
  updateSetting(SETTING_VERTICAL_ZERO, RC_ANALOGS.z);  
}

void actionSetRightLimit() {
  updateSetting(SETTING_RIGHT_CONTROL_LIMIT, RC_ANALOGS.y);  
}

void actionSetLeftLimit() {
  updateSetting(SETTING_LEFT_CONTROL_LIMIT, RC_ANALOGS.y); 
}

void actionSetTopLimit() {
  updateSetting(SETTING_TOP_CONTROL_LIMIT, RC_ANALOGS.z); 
}

void actionSetBottomLimit() {
  updateSetting(SETTING_BOTTOM_CONTROL_LIMIT, RC_ANALOGS.z); 
}

void actionSetThrustMin() {
  updateSetting(SETTING_THRUST_MIN, RC_ANALOGS.t); 
}

void actionSetThrustMax() {
  updateSetting(SETTING_THRUST_MAX, RC_ANALOGS.t); 
}

void actionSetDefaults() {
  initDefaults(); 
}

#endif