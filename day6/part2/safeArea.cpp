// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <regex>
#include <cmath>
using namespace std;

const int ROW_COUNT = 400;
const int COLUMN_COUNT = 400;

void printArea (vector<vector<char>> &area) {
  cout << endl;
  for (int i = 0; i < area.size(); i += 1) {
    for (int j = 0; j < area[0].size(); j += 1) {
      cout << area[j][i];
    }
    cout << endl;
  }
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> coordinateLines;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      coordinateLines.push_back(mystring);
    }
  }
  myfile.close();

  vector<pair<int, int>> coordinates;
  for (int i = 0; i < coordinateLines.size(); i += 1) {
    string coordinate = coordinateLines[i];
    regex regexp("([0-9]+), ([0-9]+)");
    smatch match;
    regex_search(coordinate, match, regexp);
    int x = stoi(match.str(1));
    int y = stoi(match.str(2));
    coordinates.push_back(pair<int, int>(x, y));
  }

  int closeCount;
  for (int i = 0; i < ROW_COUNT; i += 1) {
    for (int j = 0; j < COLUMN_COUNT; j += 1) {
      int distanceToAll = 0;
      for (const pair<int, int> coordinate : coordinates) {
        distanceToAll += abs(i - coordinate.first) + abs(j - coordinate.second);
      }
      if (distanceToAll < 10000) {
        closeCount += 1;
      }
    }
  }
  cout << closeCount << endl;

  return 0;
}