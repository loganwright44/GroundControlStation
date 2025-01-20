#ifndef RADIO_H
#define RADIO_H

#include "Arduino.h"
#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"

#include "messages.h"

class CommHandler {
public:
  CommHandler(uint8_t ce, uint8_t csn);
  ~CommHandler() { delete _radio; };

  void initialize(byte srcAddress[6] = "00001", byte destAddress[6] = "00002");
  bool sendPacket(command_t& command);
  bool sendPacket(message_t& _message);
  uint8_t isAvailable();
  void readPacket(void* buf, uint8_t len);

private:
  RF24* _radio;
};

#endif
