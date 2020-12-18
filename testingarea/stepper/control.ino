#include "header.h"

void setup_control() {
  // Set the maximum steps per second:
  stepper->setMaxSpeed(1000);
}

void loop_control() {
  // Set the current position to 0:
  stepper->setCurrentPosition(0);

  // Run the motor forward at 500 steps/second until the motor reaches 4096 steps (1 revolution):
  while (stepper->currentPosition() != 4096) {
    stepper->setSpeed(500);
    stepper->runSpeed();
  }
  delay(1000);

  // Reset the position to 0:
  stepper->setCurrentPosition(0);

  // Run the motor backwards at 1000 steps/second until the motor reaches -4096 steps (1 revolution):
  while (stepper->currentPosition() != -4096) {
    stepper->setSpeed(-1000);
    stepper->runSpeed();
  }

  delay(1000);

  // Reset the position to 0:
  stepper->setCurrentPosition(0);
  // Run the motor forward at 1000 steps/second until the motor reaches 8192 steps (2 revolutions):
  while (stepper->currentPosition() != 8192) {
    stepper->setSpeed(1000);
    stepper->runSpeed();
  }

  delay(3000);
}
