void updateGravity90() {
  int side;

  for (int i = 0; i < ndrops; i++) {
    if (drops[i][1] == 0) {
      continue;
    }

    if (grid[drops[i][0]][drops[i][1] - 1]) {
      side = random(2);
      if (side == 0 && drops[i][0] < 7) {
        if (grid[drops[i][0] + 1][drops[i][1] - 1]) {
          if (drops[i][0] + 1 < 7) {
            int emptyfoundAt = 8;
            int i2;
            for (i2 = drops[i][0] + 2; i2 <= 7; i2++) {
              if (!grid[i2][drops[i][1] - 1]) {
                emptyfoundAt = i2;
                break;
              }
            }
            if (emptyfoundAt < 8) {
              for (int i3 = i2 - 1; i3 >= drops[i][0] + 1; i3--) {
                int i4 = findDropIndex(i3, drops[i][1] - 1);
                drops[i4][0]++;
              }
              drops[i][0]++;
              drops[i][1]--;
            }
          }
        } else {
          drops[i][0]++;
          drops[i][1]--; 
        }
      }
      else if (side == 1 && drops[i][0] > 0) {
        if (grid[drops[i][0] - 1][drops[i][1] - 1]) {
          if (drops[i][0] - 1 > 0) {
            int emptyfoundAt = -1;
            int i2;
            for (i2 = drops[i][0] - 2; i2 >= 0; i2--) {
              if (!grid[i2][drops[i][1] - 1]) {
                emptyfoundAt = i2;
                break;
              }
            }
            if (emptyfoundAt > 0) {
              for (int i3 = i2 + 1; i3 <= drops[i][0] - 1; i3++) {
                int i4 = findDropIndex(i3, drops[i][1] - 1);
                drops[i4][0]--;
              }
              drops[i][0]--;
              drops[i][1]--;
            }
          }
        } else {
          drops[i][0]--;
          drops[i][1]--;
        }
      }
    }
    else {
      drops[i][1] = drops[i][1] - 1;      
    }

    updateGrid();
  }
}
