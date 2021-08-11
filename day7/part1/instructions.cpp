// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

const int MAX_STEPS = 26;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> instructionLines;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      instructionLines.push_back(mystring);
    }
  }
  myfile.close();

  vector<vector<char>> nextSteps(MAX_STEPS);
  vector<vector<char>> prereqs(MAX_STEPS);
  vector<bool> completed(MAX_STEPS, true);
  for (int i = 0; i < instructionLines.size(); i += 1) {
    string coordinate = instructionLines[i];
    regex regexp("Step ([A-Z]) must be finished before step ([A-Z]) can begin.");
    smatch match;
    regex_search(coordinate, match, regexp);
    char prereq = match.str(1)[0];
    char nextStep = match.str(2)[0];
    nextSteps[prereq - 'A'].push_back(nextStep);
    prereqs[nextStep - 'A'].push_back(prereq);
    completed[nextStep - 'A'] = false;
  }

  vector<char> availableSteps;
  cout << "First step(s):";
  for (int i = 0; i < completed.size(); i += 1) {
    if (completed[i]) {
      availableSteps.push_back(i + 'A');
      cout << " " << (char)(i + 'A');
    }
  }
  cout <<endl;

  string instructions = "";
  char curStep;
  while (instructions.length() != MAX_STEPS) {
    sort(availableSteps.begin(), availableSteps.end());
    char nextStep = '.';
    do {
      nextStep = availableSteps[0];
      availableSteps.erase(availableSteps.begin());
      for (char c : prereqs[nextStep - 'A']) {
        if (!completed[c - 'A']) {
          availableSteps.push_back(nextStep);
          nextStep = '.';
          break;
        }
      }
    } while (nextStep == '.');

    curStep = nextStep;
    instructions.push_back(curStep);
    completed[curStep - 'A'] = true;
    for (char c : nextSteps[curStep - 'A']) {
      if (find(availableSteps.begin(), availableSteps.end(), c) == availableSteps.end())
        availableSteps.push_back(c);
    }
  }

  cout << instructions << endl;

  return 0;
}