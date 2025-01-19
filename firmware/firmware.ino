#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"

#define CE 9
#define CSN 10
#define INTERVAL_MS_TRANSMISSION 250

RF24 radio(CE, CSN);

const byte gcs_address[6] = "00001";
const byte pad_address[6] = "00002";

typedef enum {
  SET_TIMER = 0,
  COUNTDOWN,
  ABORT,
  RESET,
  ENGAGE_HOLDDOWNS,
  DISENGAGE_HOLDDOWNS
} command_t;

struct header_t {
  command_t type;
  uint8_t buf[64];
};

header_t payload;

void setup() {
  Serial.begin(115200);
  
  radio.begin();
  radio.setAutoAck(true);
  radio.setRetries(1, 15);
  radio.setDataRate(RF24_250KBPS);
  
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(sizeof(payload));
  
  radio.openWritingPipe(pad_address);
  radio.openReadingPipe(0, gcs_address);

  radio.stopListening();
}

void loop() {
  payload.type = ABORT; 
  memcpy(&payload.buf, {0x00}, 1);
  radio.write(&payload, sizeof(payload)); 
  Serial.print("Data1:"); 
  Serial.println(payload.type); 
  Serial.print("Data2:"); 
  Serial.println(payload.buf[0]); 
  Serial.println("Sent"); 
  delay(INTERVAL_MS_TRANSMISSION);
}
