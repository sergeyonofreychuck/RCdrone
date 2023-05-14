#ifndef RC_RADIO
#define RC_RADIO


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "FlightControl.h"

const uint64_t pipeIn = 0xE8E8F0F0E1LL;     //Remember that this code is the same as in the transmitter
RF24 radio(10, 4);  //CSN and CE pins

int prevId = 0;

int prev = 0;
unsigned long last_update = 0;
unsigned long last_Time = 0;

void setupRadio()
{ 
  //Once again, begin and radio configuration
  radio.begin();
  radio.setDataRate(RF24_250KBPS);  
  radio.enableAckPayload();
  radio.openWritingPipe(pipeIn);  
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

//We create the function that will read the data each certain time
void update_the_data()
{
  //Serial.println(radio.available());
  while ( radio.available() ) {
    radio.read(&RECEIVED_FLIGHT_CONTROL, sizeof(FlightControl));

    ACK_FLIGHT_CONTROL.id = RECEIVED_FLIGHT_CONTROL.id;

    radio.writeAckPayload(1, &ACK_FLIGHT_CONTROL, sizeof(FlightControl));
  }
}

void communicateWithTransmitter()
{
  //Serial.println("communicateWithTransmitter");

  update_the_data();

  if (prevId != RECEIVED_FLIGHT_CONTROL.id) {
    prevId = RECEIVED_FLIGHT_CONTROL.id;
    last_update = millis();
    // Serial.println("Received: ");
    // printFlightControl(&RECEIVED_FLIGHT_CONTROL);
    // Serial.println("Acc: ");
    // printFlightControl(&ACK_FLIGHT_CONTROL);
    digitalWrite(7,HIGH);
  }

  if (millis() - last_update > 100) {
    digitalWrite(7,LOW);    
  }
  
  if (millis() - last_update > 2000) {
    digitalWrite(8,HIGH);
  } else {
    digitalWrite(8,LOW);
  }
}

#endif