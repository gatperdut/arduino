#ifndef stepper_header_h
#define stepper_header_h

#include <AccelStepper.h>

#define motorPin1  A0      // IN1 on the ULN2003 driver
#define motorPin2  A1     // IN2
#define motorPin3  A2     // IN3
#define motorPin4  A3     // IN4

#define MotorInterfaceType 8

extern AccelStepper* stepper;

#endif
