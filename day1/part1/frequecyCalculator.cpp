// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

  int frequency = 0;
  for(string i : fileLines) {
    frequency += stoi(i);
  }

  cout << frequency << endl;

  return 0;
}