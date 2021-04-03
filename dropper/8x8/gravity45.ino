void updateGravity45() {
  int side;
  
  for (int i = 0; i < ndrops; i++) {
    if (drops[i][0] == 0 && drops[i][1] == 7) {
      
    }
    else if (drops[i][0] == 0 && drops[i][1] < 7) {
      if (!grid[drops[i][0]][drops[i][1] + 1]) {
        drops[i][1]++;
      }
      else if (!grid[drops[i][0] + 1][drops[i][1] + 1]) {
        drops[i][0]++;
        drops[i][1]++;
      }
    }
    else if (drops[i][1] == 7 && drops[i][0] > 0) {
      if (!grid[drops[i][0] - 1][drops[i][1]]) {
        drops[i][0]--;
      }
      else if(!grid[drops[i][0] - 1][drops[i][1] - 1]) {
        drops[i][0]--;
        drops[i][1]--;
      }
    }
    else if (!grid[drops[i][0] - 1][drops[i][1] + 1]) {
       drops[i][0]--;
       drops[i][1]++;
    }
    else {
      side = random(2);
      if (side == 0) {
        if (!grid[drops[i][0] - 1][drops[i][1]]) {
          drops[i][0]--;
        }
        else {
          side = random(2);
          if (side == 0) {
            if (!grid[drops[i][0] - 1][drops[i][1] - 1]) {
              drops[i][0]--;
              drops[i][1]--;
            }
          }
          else {
            if (!grid[drops[i][0] + 1][drops[i][1] + 1]) {
              drops[i][0]++;
              drops[i][1]++;
            }
          }
        }
      }
      else {
        if (!grid[drops[i][0]][drops[i][1] + 1]) {
          drops[i][1]++;
        }
        else {
          side = random(2);
          if (side == 0) {
            if (!grid[drops[i][0] - 1][drops[i][1] - 1]) {
              drops[i][0]--;
              drops[i][1]--;
            }
          }
          else {
            if (!grid[drops[i][0] + 1][drops[i][1] + 1]) {
              drops[i][0]++;
              drops[i][1]++;
            }
          }
        }
      }
    }
    updateGrid();
  }
}
