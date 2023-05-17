#ifndef RC_RADIO
#define RC_RADIO

#include <SPI.h>
#include <LoRa.h>

void onReceive(int packetSize);
void receiveFailed();
void receiveSuccess();
int readInt();

byte localAddress = 0xB1;     // address of this device
byte destination = 0xB2;      // destination to send to

unsigned long last_radio_received = 0;

void setupRadio() {
  LoRa.setPins(53, 48, 18);// set CS, reset, IRQ pin

  Serial.println("LoRa Transmiter");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
  }

  LoRa.onReceive(onReceive);
  LoRa.receive();
}

void writeRadio() {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(FLIGHT_CONTROL_STRUCT.id); // add message ID
  LoRa.write(sizeof(FlightControl));    // add payload length
  LoRa.write(FLIGHT_CONTROL_STRUCT.id); // add payload
  LoRa.write(FLIGHT_CONTROL_STRUCT.type);  
  LoRa.write(FLIGHT_CONTROL_STRUCT.val1);  
  LoRa.write(FLIGHT_CONTROL_STRUCT.val2);  
  LoRa.write(FLIGHT_CONTROL_STRUCT.val3);  
  LoRa.write(FLIGHT_CONTROL_STRUCT.val4);  
  LoRa.endPacket(); 

  if (millis() - last_radio_received > 3000) {
    receiveFailed();  
  }   

  LoRa.receive(); 
}

int readInt() {
  if (!LoRa.available()){
    return -1;
  }  
  return LoRa.read();
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  if (recipient != localAddress) {
    Serial.println("This message is not for me.");
    receiveFailed();
    return; 
  }

  if (incomingLength != sizeof(FlightControl)) {  
    Serial.println("error: message length does not match length");
    receiveFailed();
    return;                             
  }

  FLIGHT_CONTROL_ACK.id = readInt();
  FLIGHT_CONTROL_ACK.type = readInt();
  FLIGHT_CONTROL_ACK.val1 = readInt();
  FLIGHT_CONTROL_ACK.val2 = readInt();
  FLIGHT_CONTROL_ACK.val3 = readInt();
  FLIGHT_CONTROL_ACK.val4 = readInt(); 

  //printFlightControl(&FLIGHT_CONTROL_ACK);
  last_radio_received = millis();
  receiveSuccess();
}

void receiveFailed(){
  digitalWrite(37,LOW);
  digitalWrite(35,HIGH);
}

void receiveSuccess(){
  last_radio_received = millis();
  digitalWrite(37,HIGH);
  digitalWrite(35,LOW);
}

#endif
