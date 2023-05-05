#include "Settings.h"
#include "Menu.h"
#include "Lcd.h"
#include "Telemetry.h"
#include "RcInputs.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  initSettings();
  //initDefaults();
  readSettings();

  initScreen();  

  setupUserInput();
  setupMenu();
}

void loop() {
  readUserInput();
  readRcControls();
  delay(50);
  // Serial.print(F("yControl: "));
  // Serial.println(thrustControl);
  // Serial.println(yControl);
  // Serial.println(zControl);
  // Serial.println(rightClick);
  // Serial.println(leftClick);
}  
