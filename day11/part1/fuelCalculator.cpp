#include <iostream>
using namespace std;

const int SERIAL_NUMBER = 9306;
const int MAX_X = 300;
const int MAX_Y = 300;

int main () {
  int grid[MAX_Y + 1][MAX_X + 1];
  for (int y = 1 ; y <= MAX_Y; y += 1) {
    for (int x = 1 ; x <= MAX_X; x += 1) {
      int rackId = x + 10;
      int powerLevel = rackId * y;
      powerLevel += SERIAL_NUMBER;
      powerLevel *= rackId;
      powerLevel %= 1000;
      powerLevel /= 100;
      powerLevel -= 5;
  
      grid[y][x] = powerLevel;
    }
  }

  int maxPower = INT16_MIN;
  int maxPowerX = 1;
  int maxPowerY = 1;
  for (int y = 1 ; y <= MAX_Y - 2; y += 1) {
    for (int x = 1 ; x <= MAX_X - 2; x += 1) {
      int power = grid[x][y] + grid[x][y + 1] + grid[x][y + 2];
      power += (grid[x + 1][y] + grid[x + 1][y + 1] + grid[x + 1][y + 2]);
      power += (grid[x + 2][y] + grid[x + 2][y + 1] + grid[x + 2][y + 2]);

      if (power > maxPower) {
        maxPower = power;
        maxPowerX = x;
        maxPowerY = y;
      }
    }
  }

  cout << maxPowerY << ", " << maxPowerX << endl;
}