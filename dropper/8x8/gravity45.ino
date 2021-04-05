void updateGravity45() {
  int side;
  int side2;
  
  for (int i = 0; i < ndrops; i++) {
    if (drops[i][0] == 0 && drops[i][1] == 0) {
      
    }
    else if (drops[i][0] == 0) {
      if (!grid[drops[i][0]][drops[i][1] - 1]) {
        drops[i][1]--;
      }
      else if (!grid[drops[i][0] + 1][drops[i][1] - 1]) {
        drops[i][0]++;
        drops[i][1]--;
      }
    }
    else if (drops[i][1] == 0) {
      if (!grid[drops[i][0] - 1][drops[i][1]]) {
        drops[i][0]--;
      }
      else if(!grid[drops[i][0] - 1][drops[i][1] + 1]) {
        drops[i][0]--;
        drops[i][1]++;
      }
    }
    else if (!grid[drops[i][0] - 1][drops[i][1] - 1]) {
       drops[i][0]--;
       drops[i][1]--;
    }
    else {
      side = random(2);
      if (side == 0) {
        if (!grid[drops[i][0]][drops[i][1] - 1]) {
          drops[i][1]--;
        }
        else {
          side2 = random(2);
          if (side2 == 0 && !grid[drops[i][0] + 1][drops[i][1] - 1]) {
            drops[i][0]++;
            drops[i][1]--;
          }
          else if (!grid[drops[i][0] - 1][drops[i][1] + 1]) {
            drops[i][0]--;
            drops[i][1]++;
          }
        }
      }
      else {
        if (!grid[drops[i][0] - 1][drops[i][1]]) {
          drops[i][0]--;
        }
        else {
          side2 = random(2);
          if (side2 == 0 && !grid[drops[i][0] + 1][drops[i][1] - 1]) {
            drops[i][0]++;
            drops[i][1]--;
          }
          else if (!grid[drops[i][0] - 1][drops[i][1] + 1]) {
            drops[i][0]--;
            drops[i][1]++;
          }
        }
      }
    }
    updateGrid();
  }
}
