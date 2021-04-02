#define STCP_R 2
#define STCP_C 7
#define SHCP_R 3
#define SHCP_C 6

#define RD 4
#define CD 5

int ndrops = 0;
int drops[64][2];

const int initialGrid[8][8] = {
  {1,0,1,1,1,0,1,0},
  {0,0,0,1,0,1,1,0},
  {0,1,0,1,0,1,0,0},
  {1,0,1,1,1,1,0,1},
  {0,0,0,1,1,0,0,0},
  {0,1,0,1,0,0,0,0},
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

void updateGravity() {
  int side;
  for (int i = 0; i < ndrops; i++) {

    if (drops[i][0] == 0) {
      continue;
    }

    if (grid[drops[i][0] - 1][drops[i][1]]) {
      side = random(2);
      if (side == 0 && drops[i][1] > 0) {
        if (grid[drops[i][0] - 1][drops[i][1] - 1]) {
          if (drops[i][1] - 1 > 0) {
            int emptyfoundAt = 8;
            int i2;
            for (i2 = drops[i][1] - 2; i2 >= 0; i2--) {
              if (!grid[drops[i][0] - 1][i2]) {
                emptyfoundAt = i2;
                break;
              }
            }
            if (emptyfoundAt < 8) {
              for (int i3 = i2 + 1; i3 <= drops[i][1] - 1; i3++) {
                int i4 = findDropIndex(drops[i][0] - 1, i3);
                drops[i4][1]--;
              }
              drops[i][0]--;
              drops[i][1]--;
            }
          }
        } else {
          Serial.println("esquerra");
          drops[i][0]--;
          drops[i][1]--; 
        }
      }
      else if (side == 1 && drops[i][1] < 7) {
        if (grid[drops[i][0] - 1][drops[i][1] + 1]) {
          if (drops[i][1] + 1 < 7) {
            int emptyfoundAt = -1;
            int i2;
            for (i2 = drops[i][1] + 2; i2 < 8; i2++) {
              if (!grid[drops[i][0] - 1][i2]) {
                emptyfoundAt = i2;
                break;
              }
            }
            if (emptyfoundAt > 0) {
              for (int i3 = i2 - 1; i3 >= drops[i][1] + 1; i3--) {
                
                int i4 = findDropIndex(drops[i][0] - 1, i3);
                drops[i4][1]++;
              }
              drops[i][0]--;
              drops[i][1]++;
            }
          }
        } else {
          drops[i][0]--;
          drops[i][1]++; 
        }
      }
    }
    else {
      drops[i][0] = drops[i][0] - 1;      
    }

    updateGrid();
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
  randomSeed(analogRead(0));
  
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
