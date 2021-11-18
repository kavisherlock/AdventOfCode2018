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

  // Get the guard sleep amounts
  map<string, int> guardSleepTimes;
  string curGuardId;
  bool asleep;
  int prevAsleepTime = 0;
  for (string log : guardLogs) {
    smatch guardIdMatch;
    if (regex_search(log, guardIdMatch, guardRegexp)) {
      if (asleep) {
        guardSleepTimes[curGuardId] += prevAsleepTime;
        asleep = false;
        prevAsleepTime = 0;
      }
      curGuardId = guardIdMatch.str(1);
      if (guardSleepTimes.find(curGuardId) == guardSleepTimes.end())
        guardSleepTimes[curGuardId] = 0;
    } else {
      smatch minuteMatch;
      regex_search(log, minuteMatch, minuteRegex);
      regex infoRegex("([a-z]+)");
      smatch infoMatch;
      regex_search(log, infoMatch, infoRegex);
      if (infoMatch.str(0) == "falls") {
        asleep = true;
        prevAsleepTime = stoi(minuteMatch.str(1));
        guardSleepTimes[curGuardId] -= stoi(minuteMatch.str(1));
      } else {
        asleep = false;
        guardSleepTimes[curGuardId] += stoi(minuteMatch.str(1));
      }
    }
  }

  // Find the sleepiest guard
  pair<string, int> mostSleepy ("", -1);
  for (pair<string, int> time : guardSleepTimes) {
    if (mostSleepy.second < time.second) {
      mostSleepy.first = time.first;
      mostSleepy.second = time.second;
    }
  }
  cout << "Most sleepy: " << mostSleepy.first << endl;

  // Get the actual minutes Mr Sleepy is asleep
  vector<int> minutesAsleep;
  for (int i = 0; i < 60; i += 1) {
    minutesAsleep.push_back(0);
  }
  for (int i = 0; i < guardLogs.size(); i += 1) {
    string log = guardLogs[i];
    if (log.find("#" + mostSleepy.first) != string::npos) {
      smatch guardIdMatch;
      i += 1;
      do {
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
            i += 1;
            for (int m = asleepMinute; m < awakeMinute; m += 1) {
              minutesAsleep[m] ++;
            }
          }
        }
        if (i >= guardLogs.size()) {
          break;
        }
      } while (guardLogs[i].find("Guard") == string::npos);
    }
  }

  // Get the sleepiest minute of Mr Sleepy
  int maxAlseepMinute;
  int maxAlseepMinutes = -1;
  for (int i = 0; i < 60; i += 1) {
    if (maxAlseepMinutes < minutesAsleep[i]) {
      maxAlseepMinutes = minutesAsleep[i];
      maxAlseepMinute = i;
    }
  }
  cout << maxAlseepMinute  << endl;
  cout << maxAlseepMinute * stoi(mostSleepy.first) << endl;

  return 0;
}