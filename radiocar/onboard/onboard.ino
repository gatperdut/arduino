#include <VarSpeedServo.h> 
#include <SPI.h>
#include "RF24.h"
#include <printf.h>

//#define CE_PIN 53 // MEGA
#define CE_PIN 10 // NANO
#define CSN_PIN 7

#define SERVO_PIN 9

VarSpeedServo myservo;

RF24 myRadio (CE_PIN, CSN_PIN);
byte addresses[][6] = {"0"};

struct package {
  int count = 0;
  char text[100] = "empty";
};
typedef struct package Package;
Package data;

int angles[] = { 90, 135, 180, 135, 90, 45, 0, 45 };
int angle = -1;

void setupSerial() {
  Serial.begin(9600);
  while(!Serial);
}

void setupServo() {
  myservo.attach(SERVO_PIN);
  move();
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

  setupRadio();

  setupServo();

  Serial.println("Car Controller Listening...");
} 

void move() {
  angle = (angle + 1) % 8;
  Serial.print("Move to ");
  Serial.println(angles[angle]);
  myservo.write(angles[angle], 30);
  //myservo.wait();
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
    
    //if (data.text == "LEFT") {
      move();
    //}
  }
}
