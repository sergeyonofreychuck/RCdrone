#include "Radio.h"
#include "FlightControl.h"
#include "FlightHardware.h"
#include "PowerControl.h"
#include "LedManager.h"
#include "Gyro.h"

// 8 - red LED
// 7 - green LED
// 10, 4 - RADIO CSN and CE pins
// 9, 6 servos
// 5 motor
// A7 battery input

int loopCounter = 0;

uint32_t LoopTimer4ms;
uint32_t LoopTimer10ms;
uint32_t LoopTimer1000ms;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup");

  setupLeds();

  initFlightControl();
  constructFlightDirControl();
  setupServos();
  updateServos();
  updateMotor();

  setupRadio();

  updateBatteryState();
  setupGyro();
}

void loop() {

  if (micros() - LoopTimer4ms > 4000) {
    LoopTimer4ms = micros();
    loop_4ms();
  }

  if (micros() - LoopTimer10ms > 10000) {
    LoopTimer10ms = micros();
    loop_10ms();
  }

  if (micros() - LoopTimer1000ms > 1000000) {
    LoopTimer1000ms = micros();
    loop_1000ms();
  }
}  

void loop_4ms() {
  readGyro();
}

void loop_10ms() {
  if (receiveRadio()) {
    constructFlightDirControl();
  }
  updateServos();
  updateMotor();
  updateLeds();
}

void loop_1000ms() {
  updateBatteryState();
  writeRadio();
}

void loop_10000ms() {
}
