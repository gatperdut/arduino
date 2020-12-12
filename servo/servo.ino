#include <VarSpeedServo.h> 
 
VarSpeedServo myservo;
 
void setup() {
  myservo.attach(9);
  
  
  myservo.write(0, 30);
  
  myservo.wait();
  delay(1000);
Serial.begin(9600);
} 
 
void loop() {
    myservo.write(0, 30);
  myservo.wait();
  delay(1000);
    myservo.write(90, 30);
  myservo.wait();
  delay(1000);
  myservo.write(180, 30);
  myservo.wait();
  delay(1000);
  myservo.write(90,30);
  myservo.wait();
  delay(1000);
//  myservo.write(180,30);
//  myservo.wait();
//  delay(1000);

}
