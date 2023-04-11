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

struct menuItem {
  int id;
  int parent;
  String name;
  int type;
};

menuItem menuItems[2];

static int MENU_SETTINGS_MAP[][2] = {
  {ITEM_MENU_TEST_1, SETTING_TEST_1},
  {ITEM_MENU_TEST_2, SETTING_TEST_2},  
};

void addMenuItem(struct menuItem *item, int id, int parent, String name, int type) {
  item->id = id;
  item->parent = parent;
  item->name = name;
  item->type = type;
}

void buttonPresed(int button) {
  Serial.print(F("Button pressed: "));
  Serial.println(button);
}

void showMenuItem(struct menuItem *item) {
  showSettingsItem(item->name, 0.5, -2.5, -12.4, true);
}

void setupMenu() {
  setupButtonsCallback(buttonPresed);
  addMenuItem(&menuItems[0], ITEM_MENU_TEST_1, 0, "item_1", ITEM_MENU_SETTING);
  addMenuItem(&menuItems[1], ITEM_MENU_TEST_2, 0, "item_2", ITEM_MENU_SETTING);

  showMenuItem(&menuItems[0]);
}

#endif