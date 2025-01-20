#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"

#define SERVO_FREQ 50
#define SERVO_MIN 150
#define SERVO_MAX 600

class HolddownController {
public:
  HolddownController(uint8_t numClamps);
  ~HolddownController() { delete _pwm; };

  void initialize();
  void lock();
  void unlock();
  
private:
  uint8_t _numClamps;
  uint16_t _angle = 0;
  Adafruit_PWMServoDriver* _pwm;
};

#endif
