#ifndef RC_TELEMETRY
#define RC_TELEMETRY

#include "Lcd.h"
#include "FlightControl.h"

int telemetryPower = 23;
int telemetryRightFlap = 11;
int telemetryLeftFlap = -5;

void drawTelemetry1() {
  showIntScreen("T basic", DIR_CONTROL.t, DIR_CONTROL.l, DIR_CONTROL.r);
}

#endif