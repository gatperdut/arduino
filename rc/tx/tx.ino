#include <SPI.h>
#include "RF24.h"
#include <printf.h>

#define CE_PIN 53 // MEGA
//#define CE_PIN 10 // NANO

#define CSN_PIN 7

RF24 myRadio (CE_PIN, CSN_PIN);

byte addresses[][6] = {"0"};

struct package {
  int id = 1;
  float temperature = 18.3;
  char text[100] = "Text to be transmitted";
};


typedef struct package Package;
Package data;

void setup() {
  Serial.begin(9600);
  while(!Serial);

  printf_begin();
  
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate(RF24_1MBPS); // RF24_250KBPS only for NRF24L01+
  myRadio.openWritingPipe( addresses[0]);

  myRadio.printDetails();

  delay(1000);
}

void loop() {
  myRadio.write(&data, sizeof(data)); 

  Serial.print("SENT: ");
  Serial.print(data.id);
  Serial.print(" ");
  Serial.print(data.temperature);
  Serial.print(" ");
  Serial.println(data.text);

  data.id = data.id + 1;
  data.temperature = data.temperature + 0.1;
  delay(1000);
}
