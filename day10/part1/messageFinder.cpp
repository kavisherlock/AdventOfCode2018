#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

pair<pair<int, int>, pair<int, int>> getPlaneSize(vector<pair<int, int>> &coordinates) {
  int maxX = INT32_MIN, maxY = INT32_MIN, minX = INT32_MAX, minY = INT32_MAX;
  for (pair<int, int> coordinate : coordinates) {
    if (coordinate.first < minX) {
      minX = coordinate.first;
    }
    if (coordinate.second < minY) {
      minY = coordinate.second;
    }
    
    if (coordinate.first > maxX) {
      maxX = coordinate.first;
    }
    if (coordinate.second > maxY) {
      maxY = coordinate.second;
    }
  }
  return make_pair(make_pair(maxX - minX + 1, maxY - minY + 1), make_pair(minX, minY));
}

void printGrid (vector<pair<int, int>> &coordinates) {
  pair<pair<int, int>, pair<int, int>> planeSizes = getPlaneSize(coordinates);
  pair<int, int> planeSize = planeSizes.first;
  pair<int, int> minCoordinates = planeSizes.second;
  // return;
  char plane [planeSize.first][planeSize.second];
  for (int j = 0; j < planeSize.second; j += 1) {
    for (int i = 0; i < planeSize.first; i += 1) {
      plane[i][j] = '.';
    }
  }

  for (pair<int, int> coordinate : coordinates) {
    plane[coordinate.first - minCoordinates.first][coordinate.second - minCoordinates.second] = '#';
  }

  cout << endl;
  for (int j = 0; j < planeSize.second; j += 1) {
    for (int i = 0; i < planeSize.first; i += 1) {
      cout << plane[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> lines;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      lines.push_back(mystring);
    }
  }
  myfile.close();

  vector<pair<int, int>> coordinates;
  vector<pair<int, int>> velocity;

  // position=<-3, 11> velocity=< 1, -2>
  for (string line : lines) {
    if (!line.size()) continue;
    int positionStringEnd = line.find(">");
    string positionInfo = line.substr(10, positionStringEnd - 10);
    int x = stoi(positionInfo.substr(0, positionInfo.find(",")));
    int y = stoi(positionInfo.substr(positionInfo.find(",") + 1));

    string velocityInfo = line.substr(positionStringEnd + 12, line.size() - 1 - positionStringEnd - 12);
    int vx = stoi(velocityInfo.substr(0, velocityInfo.find(",")));
    int vy = stoi(velocityInfo.substr(velocityInfo.find(",") + 1));
    
    // cout << x << " " << y << ", " << vx << " " << vy << endl;
    coordinates.push_back(make_pair(x, y));
    velocity.push_back(make_pair(vx, vy));
  }
  
  // prep coz the coordinates are way to high for the first 10500 seconds
  int prepSeconds = 10500;
  for (int i = 0; i < prepSeconds; i += 1) {
    for (int c = 0; c < coordinates.size(); c += 1) {
      coordinates[c].first += velocity[c].first;
      coordinates[c].second += velocity[c].second;
    }
  }

  pair<int, int> planeSize = getPlaneSize(coordinates).first;
  int curXSize = planeSize.first;  
  int curYSize = planeSize.second;  
  int prevXSize = INT32_MAX;  
  int prevYSize = INT32_MAX;
  while (curXSize < prevXSize && curYSize < prevYSize) {
    for (int c = 0; c < coordinates.size(); c += 1) {
      coordinates[c].first += velocity[c].first;
      coordinates[c].second += velocity[c].second;
    }
    prevXSize = curXSize;
    prevYSize = curYSize;
    planeSize = getPlaneSize(coordinates).first;
    curXSize = planeSize.first;  
    curYSize = planeSize.second; 
  }
  for (int c = 0; c < coordinates.size(); c += 1) {
    coordinates[c].first -= velocity[c].first;
    coordinates[c].second -= velocity[c].second;
  }

  printGrid(coordinates);
}
