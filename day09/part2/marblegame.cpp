#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

const int N_PLAYERS = 473;
const int N_MARBLES = 7090400;

int main () {
  cout << "Playing game with " << N_PLAYERS << " players and " << N_MARBLES << " marbles.\n";
  vector<unsigned long long int> playerScores (N_PLAYERS);
  list<int> marbles;
  marbles.push_back(0);
  list<int>::iterator marblesIt = marbles.begin();
  int curPlayer = 0;
  for (int i = 1; i <= N_MARBLES; i += 1) {
    if (i % 23 == 0) {
      playerScores[curPlayer] += i;
      for (int j = 0; j < 8; j += 1) {
        if (marblesIt == marbles.begin()) marblesIt = marbles.end();
        --marblesIt;
      }
      playerScores[curPlayer] += *marblesIt;
      marblesIt = marbles.erase(marblesIt);
      ++marblesIt;
    } else {
      marbles.insert(++marblesIt, i);
    }
    if (marblesIt == marbles.end()) marblesIt = marbles.begin();

    curPlayer = (curPlayer + 1) % N_PLAYERS;
  }

  unsigned long long int maxScore = 0;
  for (unsigned long long int score : playerScores) {
    cout << score << " ";
    if (score > maxScore) {
      maxScore = score;
    }
  }
  cout << "Max Score: " << maxScore << endl;
}