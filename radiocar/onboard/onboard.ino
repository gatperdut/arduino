#include <VarSpeedServo.h> 
#include <AccelStepper.h>
#include <SPI.h>
#include "RF24.h"
#include <printf.h>

// #######
// Stepper
#define STEPPER_PIN_1 A0 // IN1 on the ULN2003 driver
#define STEPPER_PIN_2 A1
#define STEPPER_PIN_3 A2
#define STEPPER_PIN_4 A3

#define MotorInterfaceType 8

AccelStepper stepper(MotorInterfaceType, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);

int speeds[] = { -1000, -500, 0, 500, 1000 };

int speedIndex = 2;

// #####
// Servo
#define SERVO_PIN 6

VarSpeedServo myservo;

int angles[] = { 51, 64, 77, 90, 103, 116, 129 };
int angleindex = 3;

// #####
// Radio
//#define CE_PIN 53 // MEGA
#define CE_PIN 10 // NANO
#define CSN_PIN 7
RF24 myRadio (CE_PIN, CSN_PIN);
byte addresses[][6] = {"0"};

// #######
// Message
struct package {
  int count = 0;
  char text[100] = "empty";
};
typedef struct package Package;
Package data;

void setupSerial() {
  Serial.begin(9600);
  while(!Serial);
}

void setupStepper() {
  stepper.setMaxSpeed(1000);
}

void setupServo() {
  myservo.attach(SERVO_PIN);
  myservo.write(angles[angleindex], 30);
}

void setupRadio() {
  printf_begin();

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate(RF24_1MBPS); // RF24_250KBPS only for NRF24L01+
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

  myRadio.printDetails();
}

void setup() {
  setupSerial();

  setupStepper();

  setupRadio();

  setupServo();

  Serial.println("On-board Controller Listening...");
} 

void moveServo(int delta) {
  angleindex += delta;
  if (angleindex < 0) {
    angleindex = 0;
  }
  if (angleindex > 6) {
    angleindex = 6;
  }
  Serial.print("Servo angle: ");
  Serial.println(angles[angleindex]);
  myservo.write(angles[angleindex], 30);
  //myservo.wait();
}

void setStepperSpeed(int delta) {
  speedIndex += delta;
  if (speedIndex < 0) {
    speedIndex = 0;
  }
  if (speedIndex > 4) {
    speedIndex = 4;
  }
  Serial.print("Stepper speed: ");
  Serial.println(speeds[speedIndex]);
}

void loop() {
  if (myRadio.available()) {
    while (myRadio.available()) {
      myRadio.read(&data, sizeof(data));
    }
    Serial.print("Received: ");
    Serial.print(data.text);
    Serial.print(" ");
    Serial.println(data.count);
    
    if (!strcmp(data.text, "LEFT")) {
      moveServo(-1);
    }
    if (!strcmp(data.text, "RIGHT")) {
      moveServo(+1);
    }
    if (!strcmp(data.text, "FORWARD")) {
      setStepperSpeed(+1);
    }
    if (!strcmp(data.text, "BACKWARD")) {
      setStepperSpeed(-1);
    }
  }
  stepper.setSpeed(speeds[speedIndex]);
  stepper.runSpeed();
}
