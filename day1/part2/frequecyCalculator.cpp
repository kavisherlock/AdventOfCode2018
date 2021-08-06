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

  map<int, bool> frequencies;
  int frequency = 0;
  for (int i = 0; i < 1000; i += 1) {
    for(string i : fileLines) {
      frequency += stoi(i);
      if (frequencies[frequency]) {
        cout << "Real Frequency " << frequency << endl;
        return 0;
      }
      frequencies[frequency] = true;
    }
  }

  cout << "Fake Frequency " << frequency << endl;

  return 0;
}