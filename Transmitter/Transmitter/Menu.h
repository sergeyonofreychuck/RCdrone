#ifndef RC_MENU
#define RC_MENU

#include "Settings.h"
#include "UserInput.h"
#include "Lcd.h"
#include "Telemetry.h"

static int ITEM_MENU_GROUP = 0;
static int ITEM_MENU_SETTING = 1;
static int ITEM_SCREEN = 2;

static int ITEM_MENU_TEST_1 = 1;
static int ITEM_MENU_TEST_2 = 2;
static int ITEM_MENU_TEST_3 = 3;
static int GROUP_MENU_SETTINGS = 101;
static int GROUP_MENU_TELEMETRY = 102;
static int SCREEN_TELEMENTRY_1 = 201;


struct menuItem {
  int id;
  int parent;
  String name;
  int type;
};

menuItem menuItems[6];
const int MENU_SIZE = 6;

menuItem *activeMenuItem;
bool edit = false;
float currentSettingValue;

void addMenuItem(struct menuItem *item, int id, int parent, String name, int type) {
  item->id = id;
  item->parent = parent;
  item->name = name;
  item->type = type;
}

void redrowSetting() {

}

void redrowMenu() {
  Serial.println("redrowMenu");
  if (activeMenuItem->type == ITEM_MENU_SETTING) {
    RcSetting *setting = getSetting(activeMenuItem->id);
    showSettingsItem(activeMenuItem->name, currentSettingValue, setting->min, setting->max, edit);
  } else if (activeMenuItem->type == ITEM_MENU_GROUP) {
    showGroupItem(activeMenuItem->name);
  }
}

void buttonPressedEditMode (int button) {
  if (activeMenuItem->type != ITEM_MENU_SETTING) {
    Serial.print(F("ERROR: edit not settings "));   
    Serial.println(activeMenuItem->id); 
    return;
  }

  RcSetting *setting = getSetting(activeMenuItem->id);
  float step = setting->step;

  if (button == LEFT) {
    float min = setting->min;
    currentSettingValue = currentSettingValue - step;
    if (currentSettingValue < min) {
      currentSettingValue = min;
    } 
  } else if (button == RIGHT){
    float max = setting->max;
    currentSettingValue = currentSettingValue + step;
    if (currentSettingValue > max) {
      currentSettingValue = max;
    }    
  } else if (button == CENTER) {
    updateSetting(setting->id, currentSettingValue);
    edit = false;
  } else if (button == UP) {
    currentSettingValue = setting->value;
    edit = false;
  }
}

menuItem* getById(int id) {
  for (int i=0; i < MENU_SIZE; i++) {
    if (menuItems[i].id == id) {
      return &menuItems[i];      
    }    
  }
}

menuItem* findPrev(menuItem *item) {
  bool found = false;
  for (int i=MENU_SIZE-1; i >=0 ; i--) {
    menuItem *current = &menuItems[i];      
    if(current->parent != item->parent) {
      continue;
    }     
    if (current->id == item->id) {
      found = true;   
    } else if (found) {
      return current;
    }  
  }  
  return item;
}

menuItem* findNext(menuItem *item) {
  bool found = false;
  for (int i=0; i < MENU_SIZE ; i++) {
    menuItem *current = &menuItems[i];   
    if(current->parent != item->parent) {
      continue;
    }     
    if (current->id == item->id) {
      found = true;   
    } else if (found) {
      return current;
    }  
  }  
  return item;
}

menuItem* findFirstChild(menuItem *item) {
  if (activeMenuItem->type != ITEM_MENU_GROUP) {
    Serial.print(F("ERROR: finding child of not group "));   
    Serial.println(item->id); 
    return;
  }
  for (int i=0; i < MENU_SIZE ; i++) {
    menuItem *current = &menuItems[i];   
    if(current->parent == item->id) {
      return current;
    }     
  } 
  return item;
}

void drawScreen() {
  Serial.print(F("drawScreen: "));
  if (activeMenuItem->type == ITEM_SCREEN){  
    if (activeMenuItem->id == SCREEN_TELEMENTRY_1) {
      drawTelemetry1();
    }
  } 
}

void navigate (int button) {
  if (edit) {
    Serial.print(F("ERROR: navigation in edit mode")); 
    return;
  }

  if (button == LEFT) {
    int parentId = activeMenuItem->parent;
    if (parentId != 0) {
      activeMenuItem = getById(parentId);
    }
  } else if (button == UP) {
    activeMenuItem = findPrev(activeMenuItem);    
  } else if (button == DOWN) {
    activeMenuItem = findNext(activeMenuItem);    
  } else if (button == CENTER) {
    if (activeMenuItem->type == ITEM_MENU_SETTING) {
      edit = true; 
    } else if (activeMenuItem->type == ITEM_MENU_GROUP) {
      activeMenuItem = findFirstChild(activeMenuItem);
    }
  }
  if (activeMenuItem->type == ITEM_SCREEN){
    drawScreen();
  } else if (activeMenuItem->type == ITEM_MENU_SETTING) {
    currentSettingValue = getSettingValue(activeMenuItem->id); 
  }
}

void buttonPresed(int button) {
  Serial.print(F("Button pressed: "));
  Serial.println(button);
  if (edit) {
    buttonPressedEditMode(button);
  } else {
    navigate(button);
  }
  redrowMenu();
}

void setupMenu() {
  setupButtonsCallback(buttonPresed);
  addMenuItem(&menuItems[0], ITEM_MENU_TEST_1, GROUP_MENU_SETTINGS, "item_1", ITEM_MENU_SETTING);
  addMenuItem(&menuItems[1], ITEM_MENU_TEST_2, GROUP_MENU_SETTINGS, "item_2", ITEM_MENU_SETTING);
  addMenuItem(&menuItems[2], ITEM_MENU_TEST_3, GROUP_MENU_SETTINGS, "item_3", ITEM_MENU_SETTING);
  addMenuItem(&menuItems[3], GROUP_MENU_SETTINGS, 0, "settings", ITEM_MENU_GROUP);
  addMenuItem(&menuItems[4], GROUP_MENU_TELEMETRY, 0, "telemetry", ITEM_MENU_GROUP);
  addMenuItem(&menuItems[5], SCREEN_TELEMENTRY_1, GROUP_MENU_TELEMETRY, "T basic", ITEM_SCREEN);

  activeMenuItem = getById(GROUP_MENU_SETTINGS);
  redrowMenu();
}

int getActiveScreen() {
  if (activeMenuItem->type == ITEM_SCREEN) {
    return activeMenuItem->id;
  }
  return -1;
}

void runMenu() {

}

#endif