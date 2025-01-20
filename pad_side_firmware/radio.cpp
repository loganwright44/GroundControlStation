#include "radio.h"

CommHandler::CommHandler(uint8_t ce, uint8_t csn) {
  _radio = new RF24(ce, csn);
}

void CommHandler::initialize(byte srcAddress[6] = "00001", byte destAddress[6] = "00002") {
  _radio->begin();
  _radio->setAutoAck(false);
  //_radio->setRetries(1, 15);
  _radio->setDataRate(RF24_250KBPS);
  
  _radio->setPALevel(RF24_PA_LOW);
  _radio->setPayloadSize(5);
  
  _radio->openWritingPipe(destAddress);
  _radio->openReadingPipe(0, srcAddress);

  // Radios mostly listen to avoid missing communications from the other
  _radio->startListening();
}

bool CommHandler::sendPacket(command_t& _command) {
  _radio->stopListening();
  if (_radio->write(&_command, sizeof(_command))) {
    _radio->startListening();
    return true;
  } else {
    _radio->startListening();
    return false;
  }
}

bool CommHandler::sendPacket(message_t& _message) {
  _radio->stopListening();
  if (_radio->write(&_message, sizeof(_message))) {
    _radio->startListening();
    return true;
  } else {
    _radio->startListening();
    return false;
  }
}

uint8_t CommHandler::isAvailable() {
  return _radio->available();
}

void CommHandler::readPacket(void* buf, uint8_t len) {
  _radio->read(&buf, len);
}
