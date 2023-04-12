#ifndef RC_TELEMETRY
#define RC_TELEMETRY

#include "Lcd.h"

int telemetryPower = 23;
int telemetryRightFlap = 11;
int telemetryLeftFlap = -5;

void drawTelemetry1() {
  showIntScreen("T basic", telemetryPower, telemetryRightFlap, telemetryLeftFlap);
}

#endif