#include "Radio.h"
#include "FlightControl.h"
#include "FlightHardware.h"
#include "PowerControl.h"

// 8 - red LED
// 7 - green LED
// 10, 4 - RADIO CSN and CE pins
// 9, 6 servos
// 5 motor
// A7 motor

int loopCounter = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup");

  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delay(1000);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);

  initFlightControl();
  constructFlightDirControl();
  updateServos();
  updateMotor();

  setupRadio();
  setupServos();

  updateBatteryState();
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

void loop_10ms() {
  communicateWithTransmitter();
  constructFlightDirControl();
  updateServos();
  updateMotor();
}

void loop_20ms() {
}

void loop_100ms() {
  updateBatteryState();
}

void loop_500ms() {
  updateBatteryState();
}

void loop_1000ms() {
}
