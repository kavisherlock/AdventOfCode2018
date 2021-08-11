// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

const int MAX_STEPS = 26;
const int N_WORKERS = 5;
const int MIN_STEP_TIME = 61;

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
  vector<char> curSteps(N_WORKERS, '.');
  vector<int> workers(N_WORKERS, 0);

  int timeTaken = -1;
  while (instructions.length() != MAX_STEPS) {
    timeTaken += 1;
    sort(availableSteps.begin(), availableSteps.end());
    int availableWorkers = 0;
    for(int i = 0; i < curSteps.size(); i += 1) {
      if (workers[i] != 0) {
        workers[i] -= 1;
        if (workers[i] == 0) {
          instructions.push_back(curSteps[i]);
          completed[curSteps[i] - 'A'] = true;
          for (char c : nextSteps[curSteps[i] - 'A']) {
            if (find(availableSteps.begin(), availableSteps.end(), c) == availableSteps.end()) {
              availableSteps.push_back(c);
            }
          }
          curSteps[i] = '.';
        }
      }
      if (workers[i] == 0) {
        availableWorkers += 1;
      }
    }

    vector<char> nextSteps;
    for (int i = 0; i < availableWorkers; i += 1) {
      char nextStep = '.';
      for (int j = 0; j < availableSteps.size(); j += 1) {
        nextStep = availableSteps[j];
        for (char c : prereqs[nextStep - 'A']) {
          if (!completed[c - 'A']) {
            nextStep = '.';
            break;
          }
        }
        if (nextStep != '.') {
          availableSteps.erase(availableSteps.begin() + j);
          break;
        }
      }
      if (nextStep != '.') {
        nextSteps.push_back(nextStep);
      }
    }

    int nextStepInd = 0;
    for (int i = 0; i < curSteps.size(); i += 1) {
      if (curSteps[i] == '.') {
        if (nextStepInd >= nextSteps.size()) {
          break;
        }

        curSteps[i] = nextSteps[nextStepInd];
        workers[i] = MIN_STEP_TIME + (int)(nextSteps[nextStepInd] - 'A');
        nextStepInd += 1;
      }
    }
  }

  cout << instructions << endl;
  cout << timeTaken << endl;

  return 0;
}