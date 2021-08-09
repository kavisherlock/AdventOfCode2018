// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  string polymer;
  if (myfile.is_open()) {
    getline(myfile, polymer);
  }
  myfile.close();

  string result = "";
  int j = 0;
  while (result.length() != polymer.length()) {
    if (result.length())
      polymer = result;
    result = "";
    j += 1;
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
  
  cout << j << endl;
  cout << "Done " << result.length() << " " << polymer.length() << endl;


  return 0;
}