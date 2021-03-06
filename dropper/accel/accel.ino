#include <Wire.h>  // Wire library - used for I2C communication
int ADXL345 = 0x53; // The ADXL345 sensor I2C address
float X, Y, Z;  // Outputs
void setup() {
  Serial.begin(57600);
  Wire.begin();
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  // Enable measurement
  Wire.write(8);
  Wire.endTransmission();
  delay(10);
}

boolean minusOne(float value) {
  return -1.2 < value && value < -0.8;
}

boolean minusHalf(float value) {
  return -0.8 < value && value < -0.2;
}

boolean zero(float value) {
  return -0.2 < value && value < 0.2;
}

boolean plusHalf(float value) {
  return 0.2 < value && value < 0.8;
}

boolean plusOne(float value) {
  return 0.8 < value && value < 1.2;
}

void orientation() {
  // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X = ( Wire.read()| Wire.read() << 8); // X-axis value
  X = X/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y = ( Wire.read()| Wire.read() << 8); // Y-axis value
  Y = Y/256;
  Z = ( Wire.read()| Wire.read() << 8); // Z-axis value
  Z = Z/256;

  if (minusOne(X)) {
    Serial.println("B");
  }
  else if (plusOne(X)) {
    Serial.print("F");
  }
  else if (minusOne(Y)) {
    Serial.print("H");
  }
  else if (plusOne(Y)) {
    Serial.print("D");
  }
  else if (minusHalf(X) && minusHalf(Y)) {
    Serial.print("A");
  }
  else if (minusHalf(X) && plusHalf(Y)) {
    Serial.print("C");
  }
  else if (plusHalf(X) && minusHalf(Y)) {
    Serial.print("G");
  }
  else if (plusHalf(X) && plusHalf(Y)) {
    Serial.print("E");
  }
  else {
    Serial.print("UNKNOWN");
  }

  Serial.print(" ");
  Serial.print(X);
  Serial.print(" ");
  Serial.println(Y);
}


void loop() {
  static const unsigned long REFRESH_INTERVAL = 1000; // ms
  static unsigned long lastRefreshTime = 0;
  
  if(millis() - lastRefreshTime >= REFRESH_INTERVAL) {
    lastRefreshTime += REFRESH_INTERVAL;
    orientation();
  }
}
