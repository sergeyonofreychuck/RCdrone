#include <EEPROM.h>

static int TEST_1 = 1;
static int TEST_2 = 2;

struct setting {
  int id;
  int addr;
  float value;
  float min;
  float max;
  float step;
  float defaultValue;
};

setting settings[2];

void createSetting(struct setting *s, int id, float min, float max, float step, float defaultValue){
  s->id = id;
  s->addr = id*10;
  s->min = min;
  s->max = max;
  s->step = step;  
  s->defaultValue = defaultValue;
}

void initSettings() {
  createSetting(&settings[0], TEST_1, 0, 2, 0.1, 1);
  createSetting(&settings[1], TEST_2, -1, 2, 0.2, 0.6);
}

void initDefaults() {
  for (int i = 0; i < 2; i++) {
    setting *s = &settings[i];
    EEPROM.put(s->addr, s->defaultValue);
  }  
}

void readSettings() {
  for (int i = 0; i < 2; i++) {
    setting *s = &settings[i];
    float f = 0.00f;
    EEPROM.get(s->addr, f);
    s->value = f;
  }
}
