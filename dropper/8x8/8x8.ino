#define STCP_R 2
#define STCP_C 7
#define SHCP_R 3
#define SHCP_C 6

#define RD 4
#define CD 5

byte ndrops = 0;
byte drops[64][2];

const byte initialGrid[8][8] = {
  {1,1,1,1,0,0,0,1},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1}
};

byte grid[8][8];

void setupDrops() {
  for (byte row = 0; row < 8; row++) {
    for (byte col = 0; col < 8; col++) {
      if (initialGrid[row][col]) {
        drops[ndrops][0] = 7 - row;
        drops[ndrops][1] = col;
        ndrops++;
      }
    }
  }
}

void updateGrid() {
  for (byte row = 0; row < 8; row++) {
    for (byte col = 0; col < 8; col++) {
      grid[row][col] = 0;
    }
  }

  for (byte i = 0; i < ndrops; i++) {
    grid[drops[i][0]][drops[i][1]] = 1;
  }
}

void updateGravity() {
  for (byte i = 0; i < ndrops; i++) {
    if (drops[i][0] == 0) {
      continue;
    }

    if (grid[drops[i][0] - 1][drops[i][1]]) {
      continue;
    }

    drops[i][0] = drops[i][0] - 1;
  }
}

void trackTime() {
  static const unsigned long REFRESH_INTERVAL = 1000; // ms
  static unsigned long lastRefreshTime = 0;
  
  if(millis() - lastRefreshTime >= REFRESH_INTERVAL) {
    lastRefreshTime += REFRESH_INTERVAL;
    updateGravity();
  }
}


void setup() {
  setupDrops();
  Serial.begin(57600);
  
  pinMode(STCP_R, OUTPUT);
  pinMode(STCP_C, OUTPUT);
  pinMode(SHCP_R, OUTPUT);
  pinMode(SHCP_C, OUTPUT);
  pinMode(RD, OUTPUT);
  pinMode(CD, OUTPUT);
}


void loop() {
  trackTime();
  updateGrid();
  
  for (byte row = 0; row < 8; row++) {
    byte rowB = B00000000;
    byte colB = B00000000;
    shiftOutCol(B11111111);
    for (byte col = 0; col < 8; col++) {
      if (grid[row][col]) {
        rowB = B00000001 << row;
      }
      else {
        colB = colB | (B10000000 >> col);
      }
      
    }
    
    shiftOutRow(rowB);
    shiftOutCol(colB);    
  }
}
