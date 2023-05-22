#ifndef RC_MENU
#define RC_MENU

struct menuItem {
  int id;
  int parent;
  String name;
  int type;
  int settingId;
};


void setupMenu();
void addMenuItem(int id, int parent, String name, int type, int settingId = -1);
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
//------Turn Scale          #Item -100-100; 10; 100 scale of turn 
//------Turn Oposite Scale  #Item -100-100; 10; 0 scale of oposite turn
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

const int GROUP_MENU_SETTINGS = 0;

const int GROUP_MENU_SETUP_ANALOGS = 1;

const int ACTION_MENU_SET_ZEROS = 2;
const int ACTION_MENU_SET_RIGHT_LIMIT = 3;
const int ACTION_MENU_SET_LEFT_LIMIT = 4;
const int ACTION_MENU_SET_TOP_LIMIT = 5;
const int ACTION_MENU_SET_BOTTOM_LIMIT = 6;
const int ACTION_MENU_SET_THRUST_MIN = 7;
const int ACTION_MENU_SET_THRUST_MAX = 8;

const int GROUP_MENU_SETUP_RC = 9;

const int GROUP_MENU_SETUP_SCALES = 10;

const int ITEM_MENU_RIGHT_SCALE = 11;
const int ITEM_MENU_LEFT_SCALE = 12;
const int ITEM_MENU_TOP_SCALE = 13;
const int ITEM_MENU_BOTTOM_SCALE = 14;
const int ITEM_MENU_THRUST_SCALE = 15;
const int ITEM_MENU_TURN_SCALE = 16;
const int ITEM_MENU_TURN_OPS_SCALE = 17;

const int GROUP_MENU_SETUP_SHIFTS = 18;

const int ITEM_MENU_RIGHT_SHIFT = 19;
const int ITEM_MENU_LEFT_SHIFT = 20;

const int GROUP_MENU_SETUP_LIMITS = 21;

const int ITEM_MENU_RIGHT_TOP_LIMIT = 22;
const int ITEM_MENU_RIGHT_BOTTOM_LIMIT = 23;
const int ITEM_MENU_LEFT_TOP_LIMIT = 24;
const int ITEM_MENU_LEFT_BOTTOM_LIMIT = 25;

const int ITEM_MENU_CLICKS_TO_STOP = 26;
const int ACTION_MENU_DEFAULTS = 27;

const int GROUP_MENU_TELEMETRY = 28;

const int SCREEN_TELEMENTRY_1 = 29;
const int SCREEN_TELEMENTRY_2 = 30;

menuItem menuItems[31];
const int MENU_SIZE = 31;
int addMenuCounter = 0;

menuItem *activeMenuItem;
bool edit = false;
float currentSettingValue;

void setupMenu() {
  Serial.println("setupMenu");  

  setupButtonsCallback(buttonPresed);

  addMenuItem(GROUP_MENU_SETTINGS, -1, "Settings", ITEM_TYPE_MENU_GROUP);

  addMenuItem(GROUP_MENU_SETUP_ANALOGS, GROUP_MENU_SETTINGS, "Setup Analogs", ITEM_TYPE_MENU_GROUP);

  addMenuItem(ACTION_MENU_SET_ZEROS, GROUP_MENU_SETUP_ANALOGS, "Set Zeros", ITEM_TYPE_ACTION);
  addMenuItem(ACTION_MENU_SET_RIGHT_LIMIT, GROUP_MENU_SETUP_ANALOGS, "Set Right Lim", ITEM_TYPE_ACTION);
  addMenuItem(ACTION_MENU_SET_LEFT_LIMIT, GROUP_MENU_SETUP_ANALOGS, "Set Left Lim", ITEM_TYPE_ACTION);
  addMenuItem(ACTION_MENU_SET_TOP_LIMIT, GROUP_MENU_SETUP_ANALOGS, "Set Top Lim", ITEM_TYPE_ACTION);
  addMenuItem(ACTION_MENU_SET_BOTTOM_LIMIT, GROUP_MENU_SETUP_ANALOGS, "Set Bottom Lim", ITEM_TYPE_ACTION);
  addMenuItem(ACTION_MENU_SET_THRUST_MIN, GROUP_MENU_SETUP_ANALOGS, "Set Thrust Min", ITEM_TYPE_ACTION);
  addMenuItem(ACTION_MENU_SET_THRUST_MAX, GROUP_MENU_SETUP_ANALOGS, "Set Thrust Max", ITEM_TYPE_ACTION);

  addMenuItem(GROUP_MENU_SETUP_RC, GROUP_MENU_SETTINGS, "Setup RC", ITEM_TYPE_MENU_GROUP);

  addMenuItem(GROUP_MENU_SETUP_SCALES, GROUP_MENU_SETUP_RC, "Scales", ITEM_TYPE_MENU_GROUP);

  addMenuItem(ITEM_MENU_RIGHT_SCALE, GROUP_MENU_SETUP_SCALES, "R Scale", ITEM_TYPE_MENU_SETTING, SETTING_RIGHT_SCALE);
  addMenuItem(ITEM_MENU_LEFT_SCALE, GROUP_MENU_SETUP_SCALES, "L Scale", ITEM_TYPE_MENU_SETTING, SETTING_LEFT_SCALE);
  addMenuItem(ITEM_MENU_TOP_SCALE, GROUP_MENU_SETUP_SCALES, "T Scale", ITEM_TYPE_MENU_SETTING, SETTING_TOP_SCALE);
  addMenuItem(ITEM_MENU_BOTTOM_SCALE, GROUP_MENU_SETUP_SCALES, "B Scale", ITEM_TYPE_MENU_SETTING, SETTING_BOTTOM_SCALE);
  addMenuItem(ITEM_MENU_THRUST_SCALE, GROUP_MENU_SETUP_SCALES, "Th Scale", ITEM_TYPE_MENU_SETTING, SETTING_THRUST_SCALE);
  addMenuItem(ITEM_MENU_TURN_SCALE, GROUP_MENU_SETUP_SCALES, "Turn Scale", ITEM_TYPE_MENU_SETTING, SETTING_TURN_SCALE);
  addMenuItem(ITEM_MENU_TURN_OPS_SCALE, GROUP_MENU_SETUP_SCALES, "Turn O Scale", ITEM_TYPE_MENU_SETTING, SETTING_TURN_OPS_SCALE);

  addMenuItem(GROUP_MENU_SETUP_SHIFTS, GROUP_MENU_SETUP_RC, "Shifts", ITEM_TYPE_MENU_GROUP);

  addMenuItem(ITEM_MENU_RIGHT_SHIFT, GROUP_MENU_SETUP_SHIFTS, "R Shift", ITEM_TYPE_MENU_SETTING, SETTING_RIGHT_SHIFT);
  addMenuItem(ITEM_MENU_LEFT_SHIFT, GROUP_MENU_SETUP_SHIFTS, "L Shift", ITEM_TYPE_MENU_SETTING, SETTING_LEFT_SHIFT);

  addMenuItem(GROUP_MENU_SETUP_LIMITS, GROUP_MENU_SETUP_RC, "Limits", ITEM_TYPE_MENU_GROUP);

  addMenuItem(ITEM_MENU_RIGHT_TOP_LIMIT, GROUP_MENU_SETUP_LIMITS, "R T Limit", ITEM_TYPE_MENU_SETTING, SETTING_RIGHT_TOP_LIMIT);
  addMenuItem(ITEM_MENU_RIGHT_BOTTOM_LIMIT, GROUP_MENU_SETUP_LIMITS, "R B Limit", ITEM_TYPE_MENU_SETTING, SETTING_RIGHT_BOTTOM_LIMIT);
  addMenuItem(ITEM_MENU_LEFT_TOP_LIMIT, GROUP_MENU_SETUP_LIMITS, "L T Limit", ITEM_TYPE_MENU_SETTING, SETTING_LEFT_TOP_LIMIT);
  addMenuItem(ITEM_MENU_LEFT_BOTTOM_LIMIT, GROUP_MENU_SETUP_LIMITS, "L B Limit", ITEM_TYPE_MENU_SETTING, SETTING_LEFT_BOTTOM_LIMIT);

  addMenuItem(ITEM_MENU_CLICKS_TO_STOP, GROUP_MENU_SETUP_RC, "Stop Clicks", ITEM_TYPE_MENU_SETTING, SETTING_CLICKS_TO_STOP);

  addMenuItem(GROUP_MENU_TELEMETRY, -1, "Telemetry", ITEM_TYPE_MENU_GROUP);
  addMenuItem(SCREEN_TELEMENTRY_1, GROUP_MENU_TELEMETRY, "T Basic", ITEM_TYPE_SCREEN);
  addMenuItem(SCREEN_TELEMENTRY_2, GROUP_MENU_TELEMETRY, "RC", ITEM_TYPE_SCREEN);

  addMenuItem(ACTION_MENU_DEFAULTS, GROUP_MENU_SETTINGS, "Set Detaults", ITEM_TYPE_ACTION);
  activeMenuItem = getById(GROUP_MENU_SETTINGS);
  redrowMenu();
}

void addMenuItem(int id, int parent, String name, int type, int settingId = -1) {
  // Serial.println("ADD MENU ITEM ");

  menuItem *item = menuItems + addMenuCounter;
  addMenuCounter++;
  item->id = id;
  item->parent = parent;
  item->name = name;
  item->type = type;
  item->settingId = settingId;

  if (addMenuCounter == 1) {
    return;
  } 
}

void redrowMenu() {
  // Serial.println("redrowMenu");
  // Serial.println(activeMenuItem->type);
  // Serial.println(activeMenuItem->id);

  if (activeMenuItem->type == ITEM_TYPE_MENU_SETTING) {
    RcSetting *setting = getSetting(activeMenuItem->settingId);
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

  RcSetting *setting = getSetting(activeMenuItem->settingId);
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
    if (parentId != -1) {
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
    currentSettingValue = getSettingValue(activeMenuItem->settingId); 
  }
}

void buttonPresed(int button) {
  //Serial.print(F("Button pressed: "));
  //Serial.println(button);

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