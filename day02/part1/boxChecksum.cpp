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
  vector<string> fileLines;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      fileLines.push_back(mystring);
    }
  }
  myfile.close();

  int nTwoLetters = 0;
  int nThreeLetters = 0;
  for(string i : fileLines) {
    map<char, int> letterCounts;
    for (char c : i) {
      if (letterCounts[c]) {
        letterCounts[c] += 1;
      } else {
        letterCounts[c] = 1;
      }
    }
    bool foundTwo = false;
    bool foundThree = false;
    for (pair<char, int> count : letterCounts) {
      if (count.second == 2 && !foundTwo) {
        nTwoLetters += 1;
        foundTwo = true;
      }
      if (count.second == 3 && !foundThree) {
        nThreeLetters += 1;
        foundThree = true;
      }
    }
  }

  cout << nTwoLetters * nThreeLetters << endl;

  return 0;
}