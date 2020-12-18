#ifndef stepper_header_h
#define stepper_header_h

#include <AccelStepper.h>

#define motorPin1  8      // IN1 on the ULN2003 driver
#define motorPin2  9      // IN2
#define motorPin3  10     // IN3
#define motorPin4  11     // IN4

#define MotorInterfaceType 8

extern AccelStepper* stepper;

#endif
