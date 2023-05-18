#ifndef RC_LED_MANAGER
#define RC_LED_MANAGER

#include "Radio.h"
#include "FlightHardware.h"

void setupLeds(){
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delay(1000);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}

void updateLeds() {
  if (millis() - last_radio_update < 100 || imergencyStop) {
    digitalWrite(7,HIGH);   
    digitalWrite(8,LOW); 
  } else if (millis() - last_radio_update > 100 && !imergencyStop){
    digitalWrite(7,LOW);    
  }

  if (millis() - last_radio_update > 3000) {
    FLIGHT_DIR_CONTROL.stop = 1;
    digitalWrite(8,HIGH);
  } else {
    digitalWrite(8,LOW);
  }
}

void showError(){
  digitalWrite(8,HIGH);  
  digitalWrite(7,LOW); 
}

#endif