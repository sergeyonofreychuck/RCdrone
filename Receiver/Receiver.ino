#include "Radio.h"
#include "FlightControl.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup");

  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delay(1000);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);

  setupRadio();
}

void loop()
{
  communicateWithTransmitter();
}