#include <SPI.h>
#include "RF24.h"
#include <printf.h>

//#define CE_PIN 53 // MEGA
#define CE_PIN 10 // NANO
#define CSN_PIN 7

#define PIN_COUNT    4
#define LOWEST_PIN   3
#define FORWARD_PIN  3
#define BACKWARD_PIN 4
#define LEFT_PIN     5
#define RIGHT_PIN    6
#define HIGHEST_PIN  6

RF24 myRadio (CE_PIN, CSN_PIN);
byte addresses[][6] = {"0"};

struct package {
  int count = 0;
  char text[100] = "JUNK";
};
typedef struct package Package;
Package data;

int buttonState[] = { 0, 0, 0, 0 };
int lastButtonState[] = { 0, 0, 0, 0 };

const char commands[][100] = { "FORWARD", "BACKWARD", "LEFT", "RIGHT" };

void setupSerial() {
  Serial.begin(9600);
  while(!Serial);
}

void setupButton() {
  pinMode(FORWARD_PIN, INPUT);
  pinMode(BACKWARD_PIN, INPUT);
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
}

void setupRadio() {
  printf_begin();

  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate(RF24_1MBPS); // RF24_250KBPS only for NRF24L01+
  myRadio.openWritingPipe( addresses[0]);

  myRadio.printDetails();
}

void setup() {
  setupSerial();

  setupButton();

  setupRadio();

  Serial.println("Remote Control Ready...");
} 


void notify(int pin) {
  data.count++;
  strcpy(data.text, commands[pin]);
  myRadio.write(&data, sizeof(data));
  Serial.print("Sent: ");
  Serial.print(data.text);
  Serial.print(" ");
  Serial.println(data.count);
}

void loop() {
  for (int pin = 0; pin < PIN_COUNT; pin++) {    
    buttonState[pin] = digitalRead(pin + LOWEST_PIN);
    if (buttonState[pin] != lastButtonState[pin]) {
      if (buttonState[pin] == LOW) {
        notify(pin);
      }
      lastButtonState[pin] = buttonState[pin];
    } 
  }
  delay(50);
}
