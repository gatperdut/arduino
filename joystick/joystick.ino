/*
  Joystick axes calibration
  Reads a press of the calibrated joystick and displays information
  in the default Serial.
  https://github.com/YuriiSalimov/AxisJoystick
  Created by Yurii Salimov, January, 2019.
  Released into the public domain.
*/

#include <Joystick.h>
#include <AxisJoystick.h>
#include <XYReplacerJoystick.h>

#define VRX_PIN A1
#define VRY_PIN A2
#define SW_PIN  5
#define LOW_RANGE 0
#define HIGH_RANGE 1023
#define RANGE_DIVITION 10

Joystick* joystic;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  joystic = new AxisJoystick(SW_PIN, VRX_PIN, VRY_PIN);
  joystic->calibrate(LOW_RANGE, HIGH_RANGE, RANGE_DIVITION);
}

// the loop function runs over and over again forever
void loop() {

  Serial.println(String(joystic->readVRx()) + " " + String(joystic->readVRy()));
//  bool found = false;
//  if (joystic->isUp()) {
//    Serial.print("UP");
//    Serial.print("(" + String(joystic->readVRy()) + ") ");
//    found = true;
//  }
//  if (joystic->isDown()) {
//    Serial.print("DOWN");
//    Serial.print("(" + String(joystic->readVRy()) + ") ");
//    found = true;
//  }
//  if (joystic->isLeft()) {
//    Serial.print("LEFT");
//    Serial.print("(" + String(joystic->readVRx()) + ") ");
//    found = true;
//  }
//  if (joystic->isRight()) {
//    Serial.print("RIGHT");
//    Serial.print("(" + String(joystic->readVRx()) + ") ");
//    found = true;
//  }
//  if (found) {
//    Serial.println();
//  } else {
//    Serial.println("CENTER");
//  }
  delay(500);
}
