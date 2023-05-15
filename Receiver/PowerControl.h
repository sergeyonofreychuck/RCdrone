#ifndef RC_POWER_CONTROL
#define RC_POWER_CONTROL

updateBatteryState() {
  int powerVal = analogRead(A7);
  int percentage = map(powerVal, 714 ,1000, 0, 100);
  Serial.print("power: "); 
  Serial.println(powerVal); 
  Serial.println(percentage); 
  ACK_FLIGHT_CONTROL.val4 = percentage;
}

#endif