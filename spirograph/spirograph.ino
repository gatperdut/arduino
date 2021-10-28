#include <AccelStepper.h>

#define motor1Pin1 7 // IN1 on the ULN2003 driver
#define motor1Pin2 8 // IN2
#define motor1Pin3 9 // IN3
#define motor1Pin4 10 // IN4

#define motor2Pin1 3 // IN1 on the ULN2003 driver
#define motor2Pin2 4 // IN2
#define motor2Pin3 5 // IN3
#define motor2Pin4 6 // IN4

#define MotorInterfaceType 8

AccelStepper stepper1 = AccelStepper(MotorInterfaceType, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);

AccelStepper stepper2 = AccelStepper(MotorInterfaceType, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);

void setup() {
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  stepper1.setSpeed(100);
  stepper2.setSpeed(1000);
}

void loop() {
  stepper1.runSpeed();
  stepper2.runSpeed();
}
