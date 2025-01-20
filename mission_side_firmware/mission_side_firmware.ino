#include "radio.h"

#define CE 9
#define CSN 10
#define INTERVAL_MS_TRANSMISSION 50

CommHandler commHandler(CE, CSN);

const byte gcs_address[6] = "00001";
const byte pad_address[6] = "00002";

message_t Message;
command_t Command;

void setup() {
  Serial.begin(115200);
  commHandler.initialize(gcs_address, pad_address);
}

void loop() {
  Command.command_id = ENGAGE_HOLDDOWNS;
  Command.value = 0;
  
  while (!commHandler.sendPacket(Command)) {
    delay(10);
  }

  Serial.println("Sent!");
}
