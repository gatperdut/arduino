#define STCP_R 2
#define STCP_C 7
#define SHCP_R 3
#define SHCP_C 6

#define RD 4
#define CD 5

const byte grid[][8] = {
  {1,1,1,1,0,0,0,1},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1}
};

bool done = false;

void setup() {
  Serial.begin(57600);
  
  pinMode(STCP_R, OUTPUT);
  pinMode(STCP_C, OUTPUT);
  pinMode(SHCP_R, OUTPUT);
  pinMode(SHCP_C, OUTPUT);
  pinMode(RD, OUTPUT);
  pinMode(CD, OUTPUT);
}

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

void loop() {
//  shiftOutRow(B11111111);
//  shiftOutCol(B00010101);
  for (byte row = 0; row < 8; row++) {
    byte rowB = B00000000;
    byte colB = B00000000;
    shiftOutCol(B11111111);
    for (byte col = 0; col < 8; col++) {
      if (grid[row][col]) {
        rowB = B00000001 << row;
      }
      else {
        colB = colB + (B10000000 >> col);
      }
      
    }
    if (!done) {
      Serial.print("Col:");
      Serial.println(colB, BIN);
      Serial.print("Row:");
      Serial.println(rowB, BIN);
      Serial.println();
    }
    
    shiftOutRow(rowB);
    shiftOutCol(colB);    
  }
  done = true;
}
