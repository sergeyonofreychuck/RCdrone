#include "Settings.h"
#include "Menu.h"
#include "Lcd.h"
#include "Telemetry.h"
#include "RcInputs.h"
#include "FlightControl.h"

int loopCounter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  initSettings();
  //initDefaults();
  readSettings();

  initScreen();  

  setupUserInput();
  setupMenu();

  loopCounter = 0;
}

void loop() {
  readUserInput();
  readRcControls();
  delay(50);

  loopCounter++;

  if (loopCounter%20 == 0) {
    readDirControl();
  }

  // Serial.print(F("yControl: "));
  // Serial.println(thrustControl);
  // Serial.println(yControl);
  // Serial.println(zControl);
  // Serial.println(rightClick);
  // Serial.println(leftClick);
}  
