#ifndef RC_RADIO
#define RC_RADIO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver

RF24 radio(48, 53);

void setupRadio() {
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.enableAckPayload();
  radio.openWritingPipe(radio_pipe);  
  radio.openReadingPipe(1, radio_pipe);  // using pipe 1
}

void writeRadioWithAck(FlightControl *payload, FlightControl *ack) {
    
  bool result = radio.write(payload, sizeof(FlightControl));

  //Serial.print("Payload Write ");
  //Serial.println(result);

  if (radio.available()) {  // is there an ACK payload? grab the pipe number that received it
    radio.read(ack, sizeof(FlightControl));
    Serial.print("Ack received ");
    Serial.println(FLIGHT_CONTROL_ACK.id);
    delay(100);
    digitalWrite(37,HIGH);
    delay(100);
    digitalWrite(37,LOW);
  } else {
    Serial.println("Recieved: an empty ACK packet");  // empty ACK packet received
    delay(100);
    digitalWrite(35,HIGH);
    delay(100);
    digitalWrite(35,LOW);
  }
}

struct Data_to_be_sent {
  byte ch1; 
};

Data_to_be_sent sent_data;

void radioTest()
{ 
  Serial.print("radioTest() ");

  sent_data.ch1 = sent_data.ch1+1;

  bool result = radio.write(&sent_data, sizeof(Data_to_be_sent));

  Serial.println(result);

  if (radio.available()) {  // is there an ACK payload? grab the pipe number that received it
        Data_to_be_sent received;
        radio.read(&received, sizeof(received));  // get incoming ACK payload
        Serial.print(F(" Recieved "));
        Serial.print(radio.getDynamicPayloadSize());  // print incoming payload size
        Serial.print(F(" bytes"));
        Serial.print(F(": "));
        Serial.println(received.ch1);    // print incoming message

        delay(100);
        digitalWrite(37,HIGH);
        delay(100);
        digitalWrite(37,LOW);
  } else {
    Serial.println(F(" Recieved: an empty ACK packet"));  // empty ACK packet received

    delay(100);
    digitalWrite(35,HIGH);
    delay(100);
    digitalWrite(35,LOW);
  }
}

#endif
