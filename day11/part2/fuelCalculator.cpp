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

  
  for (int y = 1 ; y <= MAX_Y; y += 1) {
    for (int x = 1 ; x <= MAX_X; x += 1) {
      cout << grid[y][x] << " ";
    }
    cout << endl;
  }

  int maxPower = INT32_MIN;
  int maxPowerX = 1;
  int maxPowerY = 1;
  int maxPowerSize = 1;
  int totalPower[MAX_Y + 1][MAX_X + 1];
  for (int s = 0; s <= 100; s += 1) {
    for (int y = 1 ; y <= MAX_Y - s + 1; y += 1) {
      for (int x = 1 ; x <= MAX_X - s + 1; x += 1) {
        int power = 0;
        for (int i = y; i < y + s; i += 1) {
          for (int j = x; j < x + s; j += 1) {
            power += grid[j][i]; 
          }
        }

        if (power > maxPower) {
          maxPower = power;
          maxPowerX = x;
          maxPowerY = y;
          maxPowerSize = s;
        }
      }
    }
  }

  cout << maxPower << endl;
  cout << maxPowerY << ", " << maxPowerX << ", " << maxPowerSize << endl;
}