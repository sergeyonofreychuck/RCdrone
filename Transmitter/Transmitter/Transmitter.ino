#include "Settings.h"
#include "Menu.h"
#include "Lcd.h"
#include "Telemetry.h"
#include "RcInputs.h"
#include "FlightControl.h"
#include "Radio.h"

int loopCounter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");

  pinMode(35,OUTPUT);

  initSettings();
  //initDefaults();
  readSettings();

  initScreen();  

  setupUserInput();
  setupMenu();

  setupRadio();

  loopCounter = 0;
}

void loop() {
  readUserInput();
  readRcControls();
  delay(50);

  loopCounter++;

  if (loopCounter%40 == 0) {
    readDirControl();
    drawScreen();
  }

  radioTest();

  // Serial.print(F("yControl: "));
  // Serial.println(thrustControl);
  // Serial.println(yControl);
  // Serial.println(zControl);
  // Serial.println(rightClick);
  // Serial.println(leftClick);
}  
