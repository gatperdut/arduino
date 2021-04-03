#include <Wire.h>
int ADXL345 = 0x53;
float X, Y, Z;

#define STCP_R 2
#define STCP_C 7
#define SHCP_R 3
#define SHCP_C 6

#define RD 4
#define CD 5

int ndrops = 0;
int drops[64][2];

int currentorient = -1;

const int path45[][2] = { {0, 7}, {0, 6}, {1, 7}, {0, 5}, {1, 6}, {2, 7}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {0, 3}, {1, 4}, {2, 5}, {3, 6}, {4, 7}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}, {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6}, {2, 0}, {3, 1}, {4, 2}, {5, 3}, {6, 4}, {7, 5}, {3, 0}, {4, 1}, {5, 2}, {6, 3}, {7, 4}, {4, 0}, {5, 1}, {6, 2}, {7, 3}, {5, 0}, {6, 1}, {7, 2}, {6, 0}, {7, 1}, {7, 0} };

const int initialGrid[8][8] = {
  {1,0,1,1,1,0,1,1},
  {0,0,0,1,0,1,1,1},
  {0,1,0,1,1,1,0,0},
  {1,1,1,1,1,1,0,1},
  {0,0,0,1,1,0,0,0},
  {0,1,0,1,0,1,0,0},
  {0,0,1,0,0,0,0,0},
  {1,0,0,0,0,0,0,1}
};

int grid[8][8];

void setupDrops() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (initialGrid[row][col]) {
        drops[ndrops][0] = 7 - row;
        drops[ndrops][1] = col;
        ndrops++;
      }
    }
  }
}

int findDropIndex(int row, int col) {
  for (int i = 0; i < ndrops; i++) {
    if (drops[i][0] == row && drops[i][1] == col) {
      return i;
    }
  }
  return -1;
}

void updateGrid() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      grid[row][col] = 0;
    }
  }

  for (int i = 0; i < ndrops; i++) {
    grid[drops[i][0]][drops[i][1]] = 1;
  }
}

void trackTime() {
  static const unsigned long REFRESH_INTERVAL = 1000; // ms
  static unsigned long lastRefreshTime = 0;
  
  if(millis() - lastRefreshTime >= REFRESH_INTERVAL) {
    lastRefreshTime += REFRESH_INTERVAL;
    currentorient = orientation();

    if (currentorient == 1) {
      updateGravity0();
    }
    else if (currentorient == 0) {
      updateGravity45();
    }
  }
}

void setup() {
  randomSeed(analogRead(0));
  setupWire();
  
  setupDrops();
  updateGrid();
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
  
  for (int row = 0; row < 8; row++) {
    int rowB = B00000000;
    int colB = B00000000;
    shiftOutCol(B11111111);
    for (int col = 0; col < 8; col++) {
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
