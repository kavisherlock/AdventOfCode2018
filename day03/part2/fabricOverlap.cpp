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

  vector<vector<string>> fabric;
  vector<bool> ids;
  ids.push_back(false);
  int fabircDimension = 1254;
  for (int i = 0; i < fabircDimension; i += 1) {
    vector<string> row;
    for (int j = 0; j < fabircDimension; j += 1) {
      row.push_back(".");
    }
    ids.push_back(true);
    fabric.push_back(row);
  }

  for (string claim : fabricClaims) {
    if (!claim.size()) continue;
    string id = claim.substr(1, claim.find(" @ ") - 1);
    string claimInfo = claim.substr(claim.find(" @ ") + 3);
    string coordinates = claimInfo.substr(0, claimInfo.find(":"));
    int x = stoi(coordinates.substr(0, coordinates.find(",")));
    int y = stoi(coordinates.substr(coordinates.find(",") + 1));
    string size = claimInfo.substr(claimInfo.find(":") + 2);
    int w = stoi(size.substr(0, size.find("x")));
    int h = stoi(size.substr(size.find("x") + 1));
    for (int i = x; i < x + w; i ++) {
      for (int j = y; j < y + h; j ++) {
        if (fabric[i][j] == ".") {
          fabric[i][j] = id;
        } else {
          if (fabric[i][j] != "X") {
            ids[stoi(fabric[i][j])] = false;
          }
          ids[stoi(id)] = false;
          fabric[i][j] = "X";
        }
      }
    }
  }

  for (int i = 0; i < fabircDimension; i ++) {
    if (ids[i]) {
      cout << i << endl;
    }
  }

  return 0;
}