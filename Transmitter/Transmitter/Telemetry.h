#ifndef RC_TELEMETRY
#define RC_TELEMETRY

#include "Lcd.h"
#include "FlightControl.h"

int telemetryPower = 23;
int telemetryRightFlap = 11;
int telemetryLeftFlap = -5;

void drawTelemetry1() {
  showIntScreen("T basic", USER_CONTROL.thrust, USER_CONTROL.horizontal, USER_CONTROL.vertical, FLIGHT_CONTROL_ACK.val4);
}

#endif