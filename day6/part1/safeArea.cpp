// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <regex>
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

set<pair<int,  int>> getNearbyCoordiates(int d, int x, int y, int maxX, int maxY) {
  set<pair<int, int>> coordinates;
  for (int i = 0; i <= d; i += 1) {
    if (x + (d - i) < maxX && y + i < maxY)
      coordinates.insert(pair<int, int>(x + (d - i), y + i));
    if (x - (d - i) >= 0 && y + i < maxY)
      coordinates.insert(pair<int, int>(x - (d - i), y + i));
    if (x + (d - i) < maxX && y - i >= 0)
      coordinates.insert(pair<int, int>(x + (d - i), y - i));
    if (x - (d - i) >= 0 && y - i >= 0)
      coordinates.insert(pair<int, int>(x - (d - i), y - i));
  }
  return coordinates;
}

char findClosest (vector<vector<char>> &area, int x, int y) {
  if (area[x][y] != ' ') return area[x][y];
  char closest = '#';
  int distance = 1;
  while (closest == '#') {
    set<pair<int,  int>> nearbyPoints = getNearbyCoordiates(distance, x, y, area.size(), area[0].size());
    for (pair<int,  int> point : nearbyPoints) {
      if (area[point.first][point.second] != ' ') {
        if (closest == '#') closest = area[point.first][point.second];
        else closest = '.';
      }
    }
    distance += 1;
  }
  // cout << " closest " << closest << endl;
  return closest;
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

  vector<vector<char>> area(ROW_COUNT, vector<char>(COLUMN_COUNT, ' '));
  for (int i = 0; i < coordinateLines.size(); i += 1) {
    string coordinate = coordinateLines[i];
    regex regexp("([0-9]+), ([0-9]+)");
    smatch match;
    regex_search(coordinate, match, regexp);
    int x = stoi(match.str(1));
    int y = stoi(match.str(2));
    area[x][y] = (char)i + 65;
  }
  vector<vector<char>> newArea(ROW_COUNT, vector<char>(COLUMN_COUNT, ' '));
  vector<int> charCount(50, 0);
  for (int i = 0; i < area.size(); i += 1) {
    for (int j = 0; j < area[0].size(); j += 1) {
      char closest = findClosest(area, i, j);
      charCount[((int)closest) - 65] += 1;
      newArea[i][j] = closest;
    }
  }

  for (int i = 0; i < area.size(); i += 1) {
    charCount[((int)newArea[i][0]) - 65] = 0;
    charCount[((int)newArea[0][i]) - 65] = 0;
    charCount[((int)newArea[i][newArea.size() - 1]) - 65] = 0;
    charCount[((int)newArea[newArea.size() - 1][i]) - 65] = 0;
  }

  int maxCount = -1;
  // printArea(newArea);
  for (int count : charCount) {
    if (maxCount < count) {
      maxCount = count;
    }
  }
  cout << maxCount << endl;

  return 0;
}