#include <VarSpeedServo.h> 
 
VarSpeedServo myservo;

const int servoPin = 9;

const int buttonPin = 3;
int buttonState = 0;
int lastButtonState = 0;

int angles[] = { 0, 45, 90, 135, 180, 135, 90, 45 };
int angle = -1;

void setup() {
  myservo.attach(servoPin);

  move();

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
} 


void move() {
  angle = (angle + 1) % 8;
  //Serial.println(angles[angle]);
  myservo.write(angles[angle], 30);
  myservo.wait();
}
void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      move();
    }
    lastButtonState = buttonState;
  }
  delay(25);
}
