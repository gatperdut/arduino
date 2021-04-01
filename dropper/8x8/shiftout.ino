void shiftOutRow(byte value) {
  shiftOut(RD, SHCP_R, MSBFIRST, value & B11111111); 

  digitalWrite(STCP_R, LOW);
  digitalWrite(STCP_R, HIGH);
  digitalWrite(STCP_R, LOW);
}

void shiftOutCol(byte value) {
  shiftOut(CD, SHCP_C, MSBFIRST, value & B11111111); 

  digitalWrite(STCP_C, LOW);
  digitalWrite(STCP_C, HIGH);
  digitalWrite(STCP_C, LOW);
}
