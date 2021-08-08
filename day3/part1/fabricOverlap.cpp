// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> fabricClaims;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      fabricClaims.push_back(mystring);
    }
  }
  myfile.close();

  vector<vector<int>> fabric;
  int fabircDimension = 1100;
  for (int i = 0; i < fabircDimension; i += 1) {
    vector<int> row;
    for (int j = 0; j < fabircDimension; j += 1) {
      row.push_back(0);
    }
    fabric.push_back(row);
  }

  for (string claim : fabricClaims) {
    if (!claim.size()) continue;
    string claimInfo = claim.substr(claim.find(" @ ") + 3);
    string coordinates = claimInfo.substr(0, claimInfo.find(":"));
    int x = stoi(coordinates.substr(0, coordinates.find(",")));
    int y = stoi(coordinates.substr(coordinates.find(",") + 1));
    string size = claimInfo.substr(claimInfo.find(":") + 2);
    int w = stoi(size.substr(0, size.find("x")));
    int h = stoi(size.substr(size.find("x") + 1));
    for (int i = x; i < x + w; i ++) {
      for (int j = y; j < y + h; j ++) {
        fabric[i][j] += 1;
      }
    }
    // cout << x << " " << y << " " << w << " " << h << endl;
  }

  int nMultipleClaims = 0;
  for (int i = 0; i < fabircDimension; i ++) {
    for (int j = 0; j < fabircDimension; j ++) {
      if (fabric[i][j] > 1) {
        nMultipleClaims += 1;
      }
    }
  }

  cout << "Multiple claims " << nMultipleClaims << endl;

  return 0;
}