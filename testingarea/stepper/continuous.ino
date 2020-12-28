#include "header.h"

void setup_continuous() {
  // Set the maximum steps per second:
  stepper->setMaxSpeed(1000);
}

void loop_continuous() {
  // Set the speed of the motor in steps per second:
  stepper->setSpeed(1000);
  // Step the motor with constant speed as set by setSpeed():
  stepper->runSpeed();
}
