void setupWire() {
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

int orientation() {
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

//  Serial.print(" ");
//  Serial.print(X);
//  Serial.print(" ");
//  Serial.println(Y);

  int result = -1;

  if (minusOne(X)) {
    result = 1;
  }
  else if (plusOne(X)) {
    result = 5;
  }
  else if (minusOne(Y)) {
    result = 7;
  }
  else if (plusOne(Y)) {
    result = 3;
  }
  else if (minusHalf(X) && minusHalf(Y)) {
    result = 0;
  }
  else if (minusHalf(X) && plusHalf(Y)) {
    result = 2;
  }
  else if (plusHalf(X) && minusHalf(Y)) {
    result = 6;
  }
  else if (plusHalf(X) && plusHalf(Y)) {
    result = 4;
  }

  Serial.println(result);

  return result;
}
