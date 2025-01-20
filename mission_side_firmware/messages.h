#ifndef MESSAGES_H
#define MESSAGES_H

#include "Arduino.h"

// Types of messages that either the pad or ground control can issue
typedef enum {
  DEFAULT_TYPE = 0,
  METADATA,
  SYSTEM_ERROR,
  SYSTEM_COMMAND,
} message;

// A few options for command messages
typedef enum {
  STATUS_REQUEST = 0,
  SET_TIMER,
  COUNTDOWN,
  ABORT,
  RESET,
  ENGAGE_HOLDDOWNS,
  DISENGAGE_HOLDDOWNS
} command;

typedef struct {
  message message_id;
  uint8_t value;
} message_t;

typedef struct {
  command command_id;
  uint8_t value;
} command_t;

#endif
