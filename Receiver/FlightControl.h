#ifndef RC_FLIGHT_CONTROL
#define RC_FLIGHT_CONTROL

const int FLIGHT_CONTROL_TYPE_DIRECTION = 0;

struct FlightControl {
  int id;
  int type;
  int val1;
  int val2;
  int val3;
  int val4;
  int checksum;
};

struct FlightDirControl {
  int r;
  int l;
  int t;
  int stop;
};

FlightControl RECEIVED_FLIGHT_CONTROL;

FlightControl ACK_FLIGHT_CONTROL;

FlightDirControl FLIGHT_DIR_CONTROL;

void initFlightControl() {
  RECEIVED_FLIGHT_CONTROL.id = 0;
  RECEIVED_FLIGHT_CONTROL.type = 0;
  RECEIVED_FLIGHT_CONTROL.val1 = 0;
  RECEIVED_FLIGHT_CONTROL.val2 = 0;
  RECEIVED_FLIGHT_CONTROL.val3 = 0;
  RECEIVED_FLIGHT_CONTROL.val4 = 0;
  RECEIVED_FLIGHT_CONTROL.checksum = 0;
}

void updateAckFlightControl() {
  ACK_FLIGHT_CONTROL.checksum = 
    ACK_FLIGHT_CONTROL.id +
    ACK_FLIGHT_CONTROL.type + 
    ACK_FLIGHT_CONTROL.val1 +
    ACK_FLIGHT_CONTROL.val2 +
    ACK_FLIGHT_CONTROL.val3 +
    ACK_FLIGHT_CONTROL.val4;
}

void constructFlightDirControl() {
  if (RECEIVED_FLIGHT_CONTROL.type == FLIGHT_CONTROL_TYPE_DIRECTION) {
    FLIGHT_DIR_CONTROL.r = RECEIVED_FLIGHT_CONTROL.val1;
    FLIGHT_DIR_CONTROL.l = RECEIVED_FLIGHT_CONTROL.val2;
    FLIGHT_DIR_CONTROL.t = RECEIVED_FLIGHT_CONTROL.val3;
    FLIGHT_DIR_CONTROL.stop = RECEIVED_FLIGHT_CONTROL.val4;
  }
}

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