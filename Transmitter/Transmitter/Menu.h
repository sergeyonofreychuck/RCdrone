#ifndef RC_MENU
#define RC_MENU

#include "Settings.h"
#include "UserInput.h"
#include "Lcd.h"

static int ITEM_MENU_GROUP = 0;
static int ITEM_MENU_SETTING = 1;
static int ITEM_TELEMETRY = 2;

static int ITEM_MENU_TEST_1 = 1;
static int ITEM_MENU_TEST_2 = 2;
static int ITEM_MENU_TEST_3 = 3;

struct menuItem {
  int id;
  int parent;
  String name;
  int type;
};

menuItem menuItems[3];
const int MENU_SIZE = 3;

menuItem *activeItem;
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
  if (activeItem->type == ITEM_MENU_SETTING) {
    RcSetting *setting = getSetting(activeItem->id);
    showSettingsItem(activeItem->name, currentSettingValue, setting->min, setting->max, edit);
  } 
}

void buttonPressedEditMode (int button) {
  if (activeItem->type != ITEM_MENU_SETTING) {
    Serial.print(F("ERROR: edit not settings "));   
    Serial.println(activeItem->id); 
    return;
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

void navigate (int button) {
  if (edit) {
    Serial.print(F("ERROR: navigation in edit mode")); 
    return;
  }

  if (button == LEFT) {
    int parentId = activeItem->parent;
    if (parentId != 0) {
      activeItem = getById(parentId);
    }
  } else if (button == UP) {
    activeItem = findPrev(activeItem);    
  } else if (button == DOWN) {
    activeItem = findNext(activeItem);    
  }
  if (activeItem->type == ITEM_MENU_SETTING) {
    currentSettingValue = getSettingValue(activeItem->id); 
  }
}

void buttonPresed(int button) {
  Serial.print(F("Button pressed: "));
  Serial.println(button);
  if (edit) {
    buttonPressedEditMode (button);
  } else {
    navigate(button);
  }
  redrowMenu();
}

void setupMenu() {
  setupButtonsCallback(buttonPresed);
  addMenuItem(&menuItems[0], ITEM_MENU_TEST_1, 0, "item_1", ITEM_MENU_SETTING);
  addMenuItem(&menuItems[1], ITEM_MENU_TEST_2, 0, "item_2", ITEM_MENU_SETTING);
  addMenuItem(&menuItems[2], ITEM_MENU_TEST_3, 0, "item_3", ITEM_MENU_SETTING);

  activeItem = &menuItems[1];
  currentSettingValue = getSettingValue(activeItem->id);
  redrowMenu();
}

#endif