
int ITEM_MENU_GROUP = 0;
int ITEM_MENU_SETTING = 1;
int ITEM_TELEMETRY = 2;


void addMenuItem(int id, int parent, String name, int type);


void setupMenu() {
  setupButtonsCallback(buttonPresed);
}

void buttonPresed(int button) {
  Serial.print(F("Button pressed: "));
  Serial.println(button);
}