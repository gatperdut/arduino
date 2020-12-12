#include <Servo.h>

int pin = 9;

Servo servo;

long prevt;

int angles[] = { 0, 45, 90, 45 };

//   0 - 2140
//  90 - 1480 - 90
// 180 - 820
#define XLEFT   2500
#define LEFT    2140
#define LCENTER 1810
#define CENTER  1480
#define RCENTER 1150
#define RIGHT    820
#define XRIGHT   500

int usecs[] = { CENTER, LCENTER, LEFT, XLEFT, LEFT, LCENTER, CENTER, RCENTER, RIGHT, XRIGHT, RIGHT, RCENTER };

//int usecs[] = { CENTER };

int i;

void setup() {
  servo.attach(pin, 500, 2500);

  Serial.begin(9600);

  i = 0;

  prevt = millis();
}

void loop() {
//    loop_angles();
  loop_usecs();
}

void loop_angles() {
  int size = sizeof(angles) / sizeof(angles[0]);

  if (millis() - prevt >= 2000) {
    prevt = millis();

    servo.write(angles[i]);
    Serial.println(angles[i]);

    i = (i + 1) % size;
  }
}

void loop_usecs() {
  int size = sizeof(usecs) / sizeof(usecs[0]);

  if (millis() - prevt >= 2000) {
    prevt = millis();

    servo.writeMicroseconds(usecs[i]);
    Serial.println(usecs[i]);

    i = (i + 1) % size;
  }
}
