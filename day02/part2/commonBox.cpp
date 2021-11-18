// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<char> getCommonLetters(string box1, string box2) {
  int boxLength = (int)box1.size();
  vector<char> commonLetters;
  for (int i = 0; i < boxLength; i += 1) {
    if (box1[i] == box2[i]) {
      commonLetters.push_back(box1[i]);
    }
  }
  return commonLetters;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> fileLines;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      fileLines.push_back(mystring);
    }
  }
  myfile.close();

  int nBoxes = (int)fileLines.size();
  for(int i = 0; i < nBoxes; i += 1) {
    for(int j = i + 1; j < nBoxes; j += 1) {
      vector<char> common = getCommonLetters(fileLines[i], fileLines[j]);
      if (common.size() == fileLines[i].size() - 1) {
        for (char c : common) {
          cout << c;
        }
        cout << endl;
        return 0;
      }
    }
  }

  return 0;
}