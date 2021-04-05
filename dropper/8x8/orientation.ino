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
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  X = ( Wire.read()| Wire.read() << 8);
  X = X/256;
  Y = ( Wire.read()| Wire.read() << 8);
  Y = Y/256;
  Z = ( Wire.read()| Wire.read() << 8);
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
