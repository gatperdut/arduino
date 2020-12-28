#include "header.h"

AccelStepper* stepper = new AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
//  setup_acceleration();
  setup_continuous();
  //setup_control();
}

void loop() {
//  loop_acceleration();
  loop_continuous();
  //loop_control();
}
