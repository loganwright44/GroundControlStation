#include "peripherals.h"

HolddownController::HolddownController(uint8_t numClamps) {
  _numClamps = numClamps;

  _pwm.begin();
  _pwm.setOscillatorFrequency(27000000);
  _pwm.setPWMFreq(SERVO_FREQ);

  delay(10);
}

void HolddownController::lock() {
  // Engages all servos in the holddown simultaneously
  _angle = map(180, 0, 180, SERVO_MIN, SERVO_MAX); // Set angle to 180 degrees
  _pwm.setPWM(0, 0, _angle);
  _pwm.setPWM(1, 0, _angle);
  _pwm.setPWM(2, 0, _angle);
  _pwm.setPWM(3, 0, _angle);
}

void HolddownController::unlock() {
  // Disengages all servos in the holddown simultaneously
  _angle = map(0, 0, 180, SERVO_MIN, SERVO_MAX); // Set angle to 0 degrees
  _pwm.setPWM(0, 0, _angle);
  _pwm.setPWM(1, 0, _angle);
  _pwm.setPWM(2, 0, _angle);
  _pwm.setPWM(3, 0, _angle);
}
