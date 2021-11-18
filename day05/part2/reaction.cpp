// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  string ogpolymer;
  if (myfile.is_open()) {
    getline(myfile, ogpolymer);
  }
  myfile.close();
  string polymer = ogpolymer;

  int minLength = -1;
  for (int i = (int)'A'; i <= (int)'Z'; i += 1) {
    string polymer = "";
    for (char c : ogpolymer) {
      if ((int)c != i && (int)c != (i + 32))
        polymer.push_back(c);
    }
    string result = "";
    while (result.length() != polymer.length()) {
      if (result.length())
        polymer = result;
      result = "";
      for (int i = 0; i < polymer.length() - 1; i += 1) {
        int c1 = (int)polymer[i];
        int c2 = (int)polymer[i + 1];
        if (c1 - c2 == 32 || c1 - c2 == -32) {
          i += 1;
        } else {
          result.push_back(polymer[i]);
        }
      }
      result.push_back(polymer[polymer.length() - 1]);
    }
    if (minLength == -1 || minLength > result.length()) {
      minLength = result.length();
    }
  }
  
  cout << minLength << endl;


  return 0;
}