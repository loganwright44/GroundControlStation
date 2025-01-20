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
  
}
