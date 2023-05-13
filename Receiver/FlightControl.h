#ifndef RC_FLIGHT_CONTROL
#define RC_FLIGHT_CONTROL

struct FlightControl {
  int id;
  int type;
  int val1;
  int val2;
  int val3;
  int val4;
};

FlightControl RECEIVED_FLIGHT_CONTROL;

FlightControl ACK_FLIGHT_CONTROL;

void printFlightControl(FlightControl *flightControl) {
  Serial.print("FlightControl id:");
  Serial.print(flightControl->id);
  Serial.print(" type:"); 
  Serial.print(flightControl->type);
  Serial.print(" val1:"); 
  Serial.print(flightControl->val1);
  Serial.print(" val2:"); 
  Serial.print(flightControl->val2);
  Serial.print(" val3:"); 
  Serial.print(flightControl->val3);
  Serial.print(" val4:"); 
  Serial.println(flightControl->val4);
}

#endif