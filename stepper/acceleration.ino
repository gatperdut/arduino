#include "header.h"

void setup_acceleration() {
  // Set the maximum steps per second:
  stepper->setMaxSpeed(1000);
  // Set the maximum acceleration in steps per second^2:
  stepper->setAcceleration(100);
}

void loop_acceleration() {
  // Set target position:
  stepper->moveTo(8192);
  // Run to position with set speed and acceleration:
  stepper->runToPosition();

  delay(1000);

  // Move back to original position:
  stepper->moveTo(0);
  // Run to position with set speed and acceleration:
  stepper->runToPosition();

  delay(1000);
}
