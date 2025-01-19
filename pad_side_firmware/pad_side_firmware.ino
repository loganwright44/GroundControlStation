#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"

#include "peripherals.h"

#define CE 9
#define CSN 10
#define INTERVAL_MS_SIGNAL_LOST 2000
#define INTERVAL_MS_SIGNAL_RETRY 250

RF24 radio(CE, CSN);
HolddownController holddownController(4);

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

unsigned long lastSignalMillis = 0;

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.setAutoAck(true);
  radio.setRetries(1, 15);
  radio.setDataRate(RF24_250KBPS);
  
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(sizeof(payload));

  radio.openWritingPipe(gcs_address);
  radio.openReadingPipe(0, pad_address);
  
  radio.startListening();
}

void loop() {
  unsigned long currentMillis = millis();

  if (radio.available() > 0) {
    radio.read(&payload, sizeof(payload));
    Serial.println("Received");
    Serial.print("Data1: ");
    Serial.println(payload.type);
    Serial.print("Data2: ");
    Serial.println(payload.buf[0]);
    lastSignalMillis = currentMillis;
  } else if (currentMillis - lastSignalMillis > INTERVAL_MS_SIGNAL_LOST) {
    lostConnection();
    lastSignalMillis = currentMillis;
  }
}


void lostConnection() {
  Serial.println("Connection lost!");

  delay(INTERVAL_MS_SIGNAL_RETRY);

  Serial.println("Retrying connection...");
}
