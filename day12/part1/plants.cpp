#include <vector>
#include <map>
#include <tuple>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

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

  string plants = ".........." + lines[0].substr(15) + "..........";

  cout << plants << endl;
  
  map<string, char> rules;
  for (int i = 2; i < lines.size(); i += 1) {
    string line = lines[i];
    if (!line.size()) continue;

    rules[line.substr(0, 5)] = line[9];
  }

  string nextPlants = "";
  for (int i = 0; i < 20; i += 1) {
    for (int p = 0; p < plants.size(); p += 1) {
      string adjacent = "";
      adjacent.push_back(p < 2 ? '.' : plants[p - 2]);
      adjacent.push_back(p < 1 ? '.' : plants[p - 1]);
      adjacent.push_back(plants[p]);
      adjacent.push_back(p >= plants.size() - 1 ? '.' : plants[p + 1]);
      adjacent.push_back(p >= plants.size() - 2 ? '.' : plants[p + 2]);

      nextPlants.push_back(rules[adjacent]);
    }
    plants = nextPlants;
    nextPlants = "";
    if (plants[plants.size() - 4] == '#' || plants[plants.size() - 3] == '#' || plants[plants.size() - 2] == '#' || plants[plants.size() - 1] == '#') plants += "..";
    cout << endl << plants.size() << endl << plants << endl;
  }


  int total = 0;
  for (int p = 0; p < plants.size(); p += 1) {
    if (plants[p] == '#') total += (p - 10);
  }
  cout << total << endl;
}
