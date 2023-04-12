#include "Settings.h"
#include "Menu.h"
#include "Lcd.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  initSettings();
  initDefaults();
  readSettings();

  initScreen();  

  setupUserInput();
  setupMenu();
}

void loop() {
  readUserInput();
  delay(50);
}  
