const char BITS_V[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
const char BITS_H[] = { 31, 33, 35, 37, 39, 41, 43, 45, 47 };

#define CLOCK 2

#define CLOCKV 3

#define HDRAW 50
#define VDRAW 51

#define HSYNC 52
#define VSYNC 53

void setup() {
  for (int i = 0; i < 9; i++) {
    pinMode(BITS_H[i], INPUT);
  }

  for (int i = 0; i < 10; i++) {
    pinMode(BITS_V[i], INPUT);
  }

  pinMode(CLOCK, INPUT);

  pinMode(HDRAW, INPUT);
  pinMode(VDRAW, INPUT);
  
  pinMode(HSYNC, INPUT);
  pinMode(VSYNC, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

  Serial.begin(57600);
}


String strval(int value) {
  return value ? "TRUE" : "FALSE";
}

unsigned int hcounter = 0;
unsigned int vcounter = 0;

void onClock() {
  hcounter = 0;
  vcounter = 0;
  for (int i = 8; i >= 0; i--) {
    int bit = digitalRead(BITS_H[i]) ? 1 : 0;
    hcounter = (hcounter << 1) + bit;
  }


  for (int i = 9; i >= 0; i--) {
    int bit = digitalRead(BITS_V[i]) ? 1 : 0;
    vcounter = (vcounter << 1) + bit;
  }

  int hdraw = digitalRead(HDRAW);
  int vdraw = digitalRead(VDRAW);

  int hsync = digitalRead(HSYNC);
  int vsync = digitalRead(VSYNC);

  Serial.print(hcounter);
  Serial.print(" ");
  Serial.print(vcounter);
  Serial.print(", ");
  
  Serial.print("DRAW=");
  Serial.print(strval(hdraw && vdraw));
  Serial.print (" (H=" + strval(hdraw) + ", V=" + strval(vdraw) + ")");
  Serial.print(", ");

  Serial.print(" HSYNC=" + strval(hsync));
  Serial.print(" VSYNC=" + strval(vsync));
 
  Serial.println();
}

void loop() {

}
