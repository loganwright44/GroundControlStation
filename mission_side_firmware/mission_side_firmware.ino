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
  
  if (commHandler.sendPacket(Command)) {
    Serial.print("Data1:");
    Serial.println(Command.command_id);
    Serial.print("Data2:");
    Serial.println(Command.value);
    Serial.println("Sent");
  } else {
    Serial.println("Failed to receive ack. Packet not delivered.");
  }

  while (commHandler.isAvailable() == 0);
  if (commHandler.isAvailable() > 0) {
    commHandler.readPacket(&Message, sizeof(Message));
    Serial.println("Message received!");
    Serial.print(Message.message_id);
    Serial.print("\t");
    Serial.println(Message.value);
  }

  delay(INTERVAL_MS_TRANSMISSION);
}
