#include "Settings.h"
#include "Menu.h"
#include "Lcd.h"
#include "Telemetry.h"
#include "RcInputs.h"
#include "FlightControl.h"
#include "Radio.h"

//LEDS
// 32 - yellow
// 34 - blue
// 35 - red
// 36 - red
// 37 - green

int loopCounter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");

  pinMode(32,OUTPUT); // yellow LED
  pinMode(34,OUTPUT); // blue LED
  pinMode(35,OUTPUT); // red LED
  pinMode(36,OUTPUT); // red LED
  pinMode(37,OUTPUT); // green LED

  initSettings();
  readSettings();

  initScreen();  

  setupUserInput();
  setupMenu();

  setupRadio();

  loopCounter = 0;
}

void loop() {
  loopCounter++;
  delay(10);

  loop_10ms();

  if (loopCounter%2 == 0) {
    loop_20ms();
  }

  if (loopCounter%10 == 0) {
    loop_100ms();
  }

  if (loopCounter%50 == 0) {
    loop_500ms();
  }

  if (loopCounter%100 == 0) {
    loop_1000ms();
  }
}  

void loop_10ms() {}

void loop_20ms() {
  readUserInput();
  readRcControls();  
  readDirControl();
}

void loop_100ms() {
  constructDirControl();
  writeRadioWithAck(&FLIGHT_CONTROL_STRUCT, &FLIGHT_CONTROL_ACK);
  //radioTest();
}

void loop_500ms() {
  drawScreen();
}

void loop_1000ms() {
}
