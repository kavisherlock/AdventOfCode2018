// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <map>
using namespace std;

bool logSorter (string log1, string log2) {
  regex regexp("[0-9]{4}-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2})");
  smatch log1Matches;
  regex_search(log1, log1Matches, regexp);
  smatch log2Matches;
  regex_search(log2, log2Matches, regexp);

  int log1Month = stoi(log1Matches[1]);
  int log2Month = stoi(log2Matches[1]);
  if (log1Month < log2Month) return true;
  else if (log1Month > log2Month) return false;

  int log1Date = stoi(log1Matches[2]);
  int log2Date = stoi(log2Matches[2]);
  if (log1Date < log2Date) return true;
  else if (log1Date > log2Date) return false;

  int log1Hour = stoi(log1Matches[3]);
  int log2Hour = stoi(log2Matches[3]);
  if (log1Hour < log2Hour) return true;
  else if (log1Hour > log2Hour) return false;

  int log1Minute = stoi(log1Matches[4]);
  int log2Minute = stoi(log2Matches[4]);
  if (log1Minute < log2Minute) return true;
  else if (log1Minute > log2Minute) return false;

  return true;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> guardLogs;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      guardLogs.push_back(mystring);
    }
  }
  myfile.close();

  // Sort into chronological order
  sort(guardLogs.begin(), guardLogs.end(), logSorter);

  regex guardRegexp("Guard #([0-9]+)");
  regex minuteRegex("[0-9]{2}:([0-9]{2})");

  map<string, vector<int>> guardSleepTimes;
  string curGuardId;
  for (int i = 0; i < guardLogs.size(); i += 1) {
    smatch guardIdMatch;
    if (regex_search(guardLogs[i], guardIdMatch, guardRegexp)) {
      curGuardId = guardIdMatch.str(1);
      if (guardSleepTimes.find(curGuardId) == guardSleepTimes.end()) {
        guardSleepTimes[curGuardId] = vector<int>(60, 0);
      }
      while (guardLogs[i + 1].find("Guard") == string::npos) {
        i += 1;
        string asleepLog = guardLogs[i];
        smatch asleepMinuteMatch;
        if (regex_search(asleepLog, asleepMinuteMatch, minuteRegex)) {
          int asleepMinute = stoi(asleepMinuteMatch.str(1));

          i += 1;
          string awakeLog = guardLogs[i];
          smatch awakeMinuteMatch;
          int awakeMinute;
          if (regex_search(awakeLog, awakeMinuteMatch, minuteRegex)) {
            awakeMinute = stoi(awakeMinuteMatch.str(1));
            for (int m = asleepMinute; m < awakeMinute; m += 1) {
              guardSleepTimes[curGuardId][m] ++;
            }
          }
        }
        if (i >= guardLogs.size()) {
          break;
        }
      }
    }
  }

  string mostSleepyGuard2;
  int sleepiestMinute2 = -1;
  int maxMinutes = -1;
  int maxSleepTime = -1;
  for (pair<string, vector<int>> time : guardSleepTimes) {
    for (int i = 0; i < time.second.size(); i += 1) {
      if (maxSleepTime < time.second[i]) {
        maxSleepTime = time.second[i];
        sleepiestMinute2 = i;
        mostSleepyGuard2 = time.first;
      }
    } 
  }

  cout << mostSleepyGuard2 << " " << sleepiestMinute2 << endl;
  cout << stoi(mostSleepyGuard2) * sleepiestMinute2 << endl;

  return 0;
}