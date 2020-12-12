#include <SPI.h>
#include "RF24.h"
#include <printf.h>

//define CE_PIN 53 // MEGA
#define CE_PIN 10 // NANO

#define CSN_PIN 7

RF24 myRadio (CE_PIN, CSN_PIN); 
struct package
{
  int id=0;
  float temperature = 0.0;
  char  text[100] ="empty";
};

byte addresses[][6] = {"0"}; 

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
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

  myRadio.printDetails();
  
  Serial.println("RECEIVER Listening...");
}

void loop() {
  if ( myRadio.available()) {
    while (myRadio.available()) {
      myRadio.read(&data, sizeof(data));
    }
    Serial.print("RCVD: ");
    Serial.print(data.id);
    Serial.print(" ");
    Serial.print(data.temperature);
    Serial.print(" ");
    Serial.println(data.text);
  }
}
