#ifndef RC_RADIO
#define RC_RADIO

#include <SPI.h>
#include <LoRa.h>

int readInt();
void onReceive(int packetSize);
unsigned long last_radio_update = 0;

#include "FlightControl.h"
#include "LedManager.h"

byte localAddress = 0xB2;     // address of this device
byte destination = 0xB1;      // destination to send to

void setupRadio()
{ 
  LoRa.setPins(4, 10, 2);// set CS, reset, IRQ pin

  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
  }

  // LoRa.onReceive(onReceive);
  // LoRa.receive();
}

void writeRadio() {
  updateAckFlightControl();
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(ACK_FLIGHT_CONTROL.id);    // add message ID
  LoRa.write(sizeof(FlightControl));    // add payload length
  LoRa.write(ACK_FLIGHT_CONTROL.id);    // add payload
  LoRa.write(ACK_FLIGHT_CONTROL.type);  
  LoRa.write(ACK_FLIGHT_CONTROL.val1);  
  LoRa.write(ACK_FLIGHT_CONTROL.val2);  
  LoRa.write(ACK_FLIGHT_CONTROL.val3);  
  LoRa.write(ACK_FLIGHT_CONTROL.val4);  
  LoRa.write(ACK_FLIGHT_CONTROL.checksum);  
  LoRa.endPacket(); 
  LoRa.receive();  
}

int receiveRadio(){ 
  int packetSize = LoRa.parsePacket();
  onReceive(packetSize);
  return packetSize;
}

int readInt() {
  if (!LoRa.available()){
    return -1;
  }  
  return (signed char) LoRa.read();
}

void onReceive(int packetSize) {
  //Serial.println("On Receive");
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  if (recipient != localAddress) {
    Serial.println("This message is not for me.");
    showError();
    return; 
  }

  if (incomingLength != sizeof(FlightControl)) {  
    Serial.println("error: message length does not match length");
    showError();
    return;                             
  }

  int id = readInt();
  int type = readInt();
  int val1 = readInt();
  int val2 = readInt();
  int val3 = readInt();
  int val4 = readInt(); 
  int checksum = readInt(); 
  
  char calcChecksum = id + type + val1 + val2 + val3 + val4;
  if (calcChecksum != checksum) {
    Serial.println("wrong checksum");
    showError();
    return;      
  }

  RECEIVED_FLIGHT_CONTROL.id = id;
  RECEIVED_FLIGHT_CONTROL.type = type;
  RECEIVED_FLIGHT_CONTROL.val1 = val1;
  RECEIVED_FLIGHT_CONTROL.val2 = val2;
  RECEIVED_FLIGHT_CONTROL.val3 = val3;
  RECEIVED_FLIGHT_CONTROL.val4 = val4; 
  RECEIVED_FLIGHT_CONTROL.checksum = checksum; 

  //printFlightControl(&RECEIVED_FLIGHT_CONTROL);

  last_radio_update = millis();
}

#endif