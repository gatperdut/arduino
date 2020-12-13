#include <SPI.h>
#include "RF24.h"
#include <printf.h>

//#define CE_PIN 53 // MEGA
#define CE_PIN 10 // NANO
#define CSN_PIN 7

#define BUTTON_PIN 3

RF24 myRadio (CE_PIN, CSN_PIN);
byte addresses[][6] = {"0"};

struct package {
  int count = 0;
  char text[100] = "LEFT";
};
typedef struct package Package;
Package data;

int buttonState = 0;
int lastButtonState = 0;

void setupSerial() {
  Serial.begin(9600);
  while(!Serial);
}

void setupButton() {
  pinMode(BUTTON_PIN, INPUT);
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


void notify() {
  data.count++;
  myRadio.write(&data, sizeof(data));
  Serial.print("Sent: ");
  Serial.print(data.text);
  Serial.print(" ");
  Serial.println(data.count);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      notify();
    }
    lastButtonState = buttonState;
  }
  delay(50);
}
