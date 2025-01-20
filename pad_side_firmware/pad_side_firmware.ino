#include "peripherals.h"
#include "radio.h"

#define CE 9
#define CSN 10
#define INTERVAL_MS_SIGNAL_LOST 2000
#define INTERVAL_MS_SIGNAL_RETRY 250

CommHandler commHandler(CE, CSN);
HolddownController holddownController(4);

message_t Message;
command_t Command;

const byte gcs_address[6] = "00001";
const byte pad_address[6] = "00002";

void setup() {
  Serial.begin(115200);
  commHandler.initialize(pad_address, gcs_address);
  holddownController.initialize();
}

void loop() {
  while (commHandler.isAvailable() == 0);
  if (commHandler.isAvailable() > 0) {
    commHandler.readPacket(&Command, sizeof(Command));
    Serial.println("Command received!");
    Serial.print(Command.command_id);
    Serial.print("\t");
    Serial.println(Command.value);
  }

  // Implement logic for message payload
  Message.message_id = DEFAULT_TYPE;
  Message.value = 123;
  
  if (commHandler.sendPacket(Message)) {
    Serial.println("Response sent!");
  } else {
    Serial.println("Could not respond to destination!");
  }
}
