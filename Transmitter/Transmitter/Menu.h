#ifndef RC_MENU
#define RC_MENU

void setupMenu();
void addMenuItem(struct menuItem *item, int id, int parent, String name, int type);
void redrowMenu();
void drawScreen();

void buttonPresed(int button);
void navigate (int button);
void buttonPressedEditMode (int button);

menuItem* getById(int id);
menuItem* findPrev(menuItem *item);
menuItem* findNext(menuItem *item);
menuItem* findFirstChild(menuItem *item);
int getActiveScreen();

#include "Settings.h"
#include "UserInput.h"
#include "Lcd.h"
#include "Telemetry.h"

//Settings
//--Setup Analogs           #Group
//----Set Zeros             #Action; 500, 500 
//----Set Right Limit       #Action; 0
//----Set Left Limit        #Action; 1023
//----Set Top Limit         #Action; 0
//----Set Bottom Limit      #Action; 1023
//----Set Thrust Min        #Action; 0
//----Set Thrust Max        #Action; 1023
//--Setup RC                #Group
//----Scales                #Group
//------Right Scale         #Item 1-100; 10; 100
//------Left Scale          #Item 1-100; 10; 100 
//------Top Scale           #Item 1-100; 10; 100
//------Bottom Scale        #Item 1-100; 10; 100
//------Thrust Scale        #Item 1-100; 5; 100
//----Shifts                #Group
//------Right Shift         #Item -100-100; 1; 0
//------Left Shift          #Item -100-100; 1; 0
//----Limits                #Group
//------Right Top Limit     #Item 1-100; 5; 100
//------Right Bottom Limit  #Item 1-100; 5; 100
//------Left Top Limit      #Item 1-100; 5; 100
//------Lefft Bottom Limit  #Item 1-100; 5; 100
//----Clicks to stop        #Item 1-2;   1; 1
//--Reset To Default        #Action
//Telemetry                 #Group
//--T Basic                 #Screen
//

const int ITEM_TYPE_MENU_GROUP = 0;
const int ITEM_TYPE_MENU_SETTING = 1;
const int ITEM_TYPE_SCREEN = 2;
const int ITEM_TYPE_ACTION = 3;

const int ACTION_MENU_SET_ZEROS = 1;
const int ACTION_MENU_SET_RIGHT_LIMIT = 2;
const int ACTION_MENU_SET_LEFT_LIMIT = 3;
const int ACTION_MENU_SET_TOP_LIMIT = 4;
const int ACTION_MENU_SET_BOTTOM_LIMIT = 5;
const int ACTION_MENU_SET_THRUST_MIN = 6;
const int ACTION_MENU_SET_THRUST_MAX = 7;

const int ITEM_MENU_RIGHT_SCALE = 8;
const int ITEM_MENU_LEFT_SCALE = 9;
const int ITEM_MENU_TOP_SCALE = 10;
const int ITEM_MENU_BOTTOM_SCALE = 11;
const int ITEM_MENU_THRUST_SCALE = 12;
const int ITEM_MENU_RIGHT_SHIFT = 13;
const int ITEM_MENU_LEFT_SHIFT = 14;
const int ITEM_MENU_RIGHT_TOP_LIMIT = 15;
const int ITEM_MENU_RIGHT_BOTTOM_LIMIT = 16;
const int ITEM_MENU_LEFT_TOP_LIMIT = 17;
const int ITEM_MENU_LEFT_BOTTOM_LIMIT = 18;
const int ITEM_MENU_CLICKS_TO_STOP = 20;

const int ACTION_MENU_DEFAULTS = 19;

const int GROUP_MENU_SETTINGS = 101;
const int GROUP_MENU_SETUP_ANALOGS = 102;
const int GROUP_MENU_SETUP_RC = 103;
const int GROUP_MENU_TELEMETRY = 104;
const int GROUP_MENU_SETUP_SCALES = 105;
const int GROUP_MENU_SETUP_SHIFTS = 106;
const int GROUP_MENU_SETUP_LIMITS = 107;

const int SCREEN_TELEMENTRY_1 = 201;
const int SCREEN_TELEMENTRY_2 = 202;


struct menuItem {
  int id;
  int parent;
  String name;
  int type;
};

menuItem menuItems[29];
const int MENU_SIZE = 29;

menuItem *activeMenuItem;
bool edit = false;
float currentSettingValue;

void setupMenu() {
  setupButtonsCallback(buttonPresed);

  addMenuItem(&menuItems[0], GROUP_MENU_SETTINGS, 0, "Settings", ITEM_TYPE_MENU_GROUP);

  addMenuItem(&menuItems[1], GROUP_MENU_SETUP_ANALOGS, GROUP_MENU_SETTINGS, "Setup Analogs", ITEM_TYPE_MENU_GROUP);

  addMenuItem(&menuItems[2], ACTION_MENU_SET_ZEROS, GROUP_MENU_SETUP_ANALOGS, "Set Zeros", ITEM_TYPE_ACTION);
  addMenuItem(&menuItems[3], ACTION_MENU_SET_RIGHT_LIMIT, GROUP_MENU_SETUP_ANALOGS, "Set Right Lim", ITEM_TYPE_ACTION);
  addMenuItem(&menuItems[4], ACTION_MENU_SET_LEFT_LIMIT, GROUP_MENU_SETUP_ANALOGS, "Set Left Lim", ITEM_TYPE_ACTION);
  addMenuItem(&menuItems[5], ACTION_MENU_SET_TOP_LIMIT, GROUP_MENU_SETUP_ANALOGS, "Set Top Lim", ITEM_TYPE_ACTION);
  addMenuItem(&menuItems[6], ACTION_MENU_SET_BOTTOM_LIMIT, GROUP_MENU_SETUP_ANALOGS, "Set Bottom Lim", ITEM_TYPE_ACTION);
  addMenuItem(&menuItems[7], ACTION_MENU_SET_THRUST_MIN, GROUP_MENU_SETUP_ANALOGS, "Set Thrust Min", ITEM_TYPE_ACTION);
  addMenuItem(&menuItems[8], ACTION_MENU_SET_THRUST_MAX, GROUP_MENU_SETUP_ANALOGS, "Set Thrust Max", ITEM_TYPE_ACTION);

  addMenuItem(&menuItems[9], GROUP_MENU_SETUP_RC, GROUP_MENU_SETTINGS, "Setup RC", ITEM_TYPE_MENU_GROUP);

  addMenuItem(&menuItems[28], ITEM_MENU_CLICKS_TO_STOP, GROUP_MENU_SETUP_RC, "Stop Clicks", ITEM_TYPE_MENU_SETTING);

  addMenuItem(&menuItems[9], GROUP_MENU_SETUP_RC, GROUP_MENU_SETTINGS, "Setup RC", ITEM_TYPE_MENU_GROUP);

  addMenuItem(&menuItems[24], GROUP_MENU_SETUP_SCALES, GROUP_MENU_SETUP_RC, "Scales", ITEM_TYPE_MENU_GROUP);

  addMenuItem(&menuItems[10], ITEM_MENU_RIGHT_SCALE, GROUP_MENU_SETUP_SCALES, "R Scale", ITEM_TYPE_MENU_SETTING);
  addMenuItem(&menuItems[11], ITEM_MENU_LEFT_SCALE, GROUP_MENU_SETUP_SCALES, "L Scale", ITEM_TYPE_MENU_SETTING);
  addMenuItem(&menuItems[12], ITEM_MENU_TOP_SCALE, GROUP_MENU_SETUP_SCALES, "T Scale", ITEM_TYPE_MENU_SETTING);
  addMenuItem(&menuItems[13], ITEM_MENU_BOTTOM_SCALE, GROUP_MENU_SETUP_SCALES, "B Scale", ITEM_TYPE_MENU_SETTING);
  addMenuItem(&menuItems[14], ITEM_MENU_THRUST_SCALE, GROUP_MENU_SETUP_SCALES, "Th Scale", ITEM_TYPE_MENU_SETTING);

  addMenuItem(&menuItems[25], GROUP_MENU_SETUP_SHIFTS, GROUP_MENU_SETUP_RC, "Shifts", ITEM_TYPE_MENU_GROUP);

  addMenuItem(&menuItems[15], ITEM_MENU_RIGHT_SHIFT, GROUP_MENU_SETUP_SHIFTS, "R Shift", ITEM_TYPE_MENU_SETTING);
  addMenuItem(&menuItems[16], ITEM_MENU_LEFT_SHIFT, GROUP_MENU_SETUP_SHIFTS, "L Shift", ITEM_TYPE_MENU_SETTING);

  addMenuItem(&menuItems[26], GROUP_MENU_SETUP_LIMITS, GROUP_MENU_SETUP_RC, "Limits", ITEM_TYPE_MENU_GROUP);

  addMenuItem(&menuItems[17], ITEM_MENU_RIGHT_TOP_LIMIT, GROUP_MENU_SETUP_LIMITS, "R T Limit", ITEM_TYPE_MENU_SETTING);
  addMenuItem(&menuItems[18], ITEM_MENU_RIGHT_BOTTOM_LIMIT, GROUP_MENU_SETUP_LIMITS, "R B Limit", ITEM_TYPE_MENU_SETTING);
  addMenuItem(&menuItems[19], ITEM_MENU_LEFT_TOP_LIMIT, GROUP_MENU_SETUP_LIMITS, "L T Limit", ITEM_TYPE_MENU_SETTING);
  addMenuItem(&menuItems[20], ITEM_MENU_LEFT_BOTTOM_LIMIT, GROUP_MENU_SETUP_LIMITS, "L B Limit", ITEM_TYPE_MENU_SETTING);

  addMenuItem(&menuItems[21], GROUP_MENU_TELEMETRY, 0, "Telemetry", ITEM_TYPE_MENU_GROUP);
  addMenuItem(&menuItems[22], SCREEN_TELEMENTRY_1, GROUP_MENU_TELEMETRY, "T Basic", ITEM_TYPE_SCREEN);
  addMenuItem(&menuItems[27], SCREEN_TELEMENTRY_2, GROUP_MENU_TELEMETRY, "RC", ITEM_TYPE_SCREEN);

  addMenuItem(&menuItems[23], ACTION_MENU_DEFAULTS, GROUP_MENU_SETTINGS, "Set Detaults", ITEM_TYPE_ACTION);

  activeMenuItem = getById(GROUP_MENU_SETTINGS);
  redrowMenu();
}

void addMenuItem(struct menuItem *item, int id, int parent, String name, int type) {
  item->id = id;
  item->parent = parent;
  item->name = name;
  item->type = type;
}

void redrowMenu() {
  Serial.println("redrowMenu");
  Serial.println(activeMenuItem->type);
  Serial.println(activeMenuItem->id);

  if (activeMenuItem->type == ITEM_TYPE_MENU_SETTING) {
    RcSetting *setting = getSetting(activeMenuItem->id);
    showIntSettingsItem(activeMenuItem->name, currentSettingValue, setting->min, setting->max, edit);
  } else if (activeMenuItem->type == ITEM_TYPE_MENU_GROUP) {
    showGroupItem(activeMenuItem->name);
  } else if (activeMenuItem->type == ITEM_TYPE_ACTION) {
    switch (activeMenuItem->id) {
      case ACTION_MENU_SET_ZEROS: {
        float currentHorizont = getSettingValue(SETTING_HORIZONTAL_ZERO);
        float currentVertical = getSettingValue(SETTING_VERTICAL_ZERO);
        showTwoFloatItem(activeMenuItem->name, currentHorizont, currentVertical, edit);
        break;
      }
      case ACTION_MENU_SET_RIGHT_LIMIT: {
        float rightLimit = getSettingValue(SETTING_RIGHT_CONTROL_LIMIT);
        showSingleFloatItem(activeMenuItem->name, rightLimit, edit);
        break;
      }
      case ACTION_MENU_SET_LEFT_LIMIT: {
        float leftLimit = getSettingValue(SETTING_LEFT_CONTROL_LIMIT);
        showSingleFloatItem(activeMenuItem->name, leftLimit, edit);
        break;
      }
      case ACTION_MENU_SET_TOP_LIMIT: {
        float topLimit = getSettingValue(SETTING_TOP_CONTROL_LIMIT);
        showSingleFloatItem(activeMenuItem->name, topLimit, edit);
        break;
      }
      case ACTION_MENU_SET_BOTTOM_LIMIT: {
        float bottomLimit = getSettingValue(SETTING_BOTTOM_CONTROL_LIMIT);
        showSingleFloatItem(activeMenuItem->name, bottomLimit, edit);
        break;
      }
      case ACTION_MENU_SET_THRUST_MIN: {
      float thrustMin = getSettingValue(SETTING_THRUST_MIN);
        showSingleFloatItem(activeMenuItem->name, thrustMin, edit);
        break;
      }
      case ACTION_MENU_SET_THRUST_MAX: {
        float thrustMax = getSettingValue(SETTING_THRUST_MAX);
        showSingleFloatItem(activeMenuItem->name, thrustMax, edit);
        break;
      }
      case ACTION_MENU_DEFAULTS: { 
        showEditItem(activeMenuItem->name, edit);
        break;
      }
    }
  }
}

void buttonPressedEditModeItem (int button) {
  if (activeMenuItem->type != ITEM_TYPE_MENU_SETTING) {
    Serial.print(F("ERROR: edit not settings or action"));   
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

void buttonPressedEditModeAction(int button) {
  if (activeMenuItem->type != ITEM_TYPE_ACTION) {
    Serial.print(F("ERROR: edit not settings or action"));   
    Serial.println(activeMenuItem->id); 
    return;
  }
  if (button == UP) {
    edit = false;
  } else if (button == CENTER) {
    switch (activeMenuItem->id) {
      case ACTION_MENU_SET_ZEROS: { 
        actionSetZeros();
        break;
      }
      case ACTION_MENU_SET_RIGHT_LIMIT: {
        actionSetRightLimit();
        break;
      }
      case ACTION_MENU_SET_LEFT_LIMIT: {
        actionSetLeftLimit();
        break;
      }
      case ACTION_MENU_SET_TOP_LIMIT: {
        actionSetTopLimit();
        break;
      }
      case ACTION_MENU_SET_BOTTOM_LIMIT: {
        actionSetBottomLimit();
        break;     
      }
      case ACTION_MENU_SET_THRUST_MIN: {
        actionSetThrustMin();
        break;
      }
      case ACTION_MENU_SET_THRUST_MAX: {
        actionSetThrustMax();
        break;     
      }
    }
    edit = false;
  } else if (button == RESET) {
    if (activeMenuItem->id == ACTION_MENU_DEFAULTS) {
        initDefaults();
        readSettings();    
    }
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
  if (activeMenuItem->type != ITEM_TYPE_MENU_GROUP) {
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
  if (activeMenuItem->type == ITEM_TYPE_SCREEN){  
    //Serial.print(F("drawScreen: "));
    if (activeMenuItem->id == SCREEN_TELEMENTRY_1) {
      drawTelemetry1();
    } else if (activeMenuItem->id == SCREEN_TELEMENTRY_2) {
      drawTelemetry2();
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
    if (activeMenuItem->type == ITEM_TYPE_MENU_SETTING || activeMenuItem->type == ITEM_TYPE_ACTION) {
      edit = true; 
    } else if (activeMenuItem->type == ITEM_TYPE_MENU_GROUP) {
      activeMenuItem = findFirstChild(activeMenuItem);
    }
  }
  if (activeMenuItem->type == ITEM_TYPE_SCREEN){
    drawScreen();
  } else if (activeMenuItem->type == ITEM_TYPE_MENU_SETTING) {
    currentSettingValue = getSettingValue(activeMenuItem->id); 
  }
}

void buttonPresed(int button) {
  Serial.print(F("Button pressed: "));
  Serial.println(button);

  if (edit) {
    if (activeMenuItem->type == ITEM_TYPE_MENU_SETTING) {
      buttonPressedEditModeItem(button);
    } else if (activeMenuItem->type == ITEM_TYPE_ACTION) {
      buttonPressedEditModeAction(button);
    }
  } else {
    navigate(button);
  }
  redrowMenu();
}

int getActiveScreen() {
  if (activeMenuItem->type == ITEM_TYPE_SCREEN) {
    return activeMenuItem->id;
  }
  return -1;
}

#endif