#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void printField(const vector<string> &field) {
  for (string row : field) {
    cout << row << endl;
  }
}

enum turnDirections { LEFT, STRAIGHT, RIGHT };

vector<string> moveCarts (const vector<string> &field, const vector<string> &emptyField, vector<char> &cartDirections, vector<int> &nextIntersectionTurn) {
  const int nCols = field[0].length();
  const int nRows = field.size() - 1;

  vector<string> newField = field;
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (field[i][j] >= 'A' && field[i][j] <= 'Z') {
        int cartIndex = (int)field[i][j] - 65;

        if (cartDirections[cartIndex] == 'v') {
          newField[i][j] = emptyField[i][j];
          char nextSquare = newField[i + 1][j];
          if (nextSquare == '|' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == STRAIGHT)) {
            cartDirections[cartIndex] = 'v';
          } else if (nextSquare == '\\' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == LEFT)) {
            cartDirections[cartIndex] = '>';
          } else if (nextSquare == '/' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == RIGHT)) {
            cartDirections[cartIndex] = '<';
          }
          if (nextSquare == '+') {
            nextIntersectionTurn[cartIndex] = (nextIntersectionTurn[cartIndex] + 1) % 3;
          }
          if (nextSquare >= 'A' && nextSquare <= 'Z') {
            cout << "COLLISSION AT " << j << ", " << i + 1 << endl;
            return vector<string>();
          }
          newField[i + 1][j] = field[i][j];
        } else if (cartDirections[cartIndex] == '^') {
          newField[i][j] = emptyField[i][j];
          char nextSquare = newField[i - 1][j];
          if (nextSquare == '|' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == STRAIGHT)) {
            cartDirections[cartIndex] = '^';
          } else if (nextSquare == '/' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == RIGHT)) {
            cartDirections[cartIndex] = '>';
          } else if (nextSquare == '\\' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == LEFT)) {
            cartDirections[cartIndex] = '<';
          }
          if (nextSquare == '+') {
            nextIntersectionTurn[cartIndex] = (nextIntersectionTurn[cartIndex] + 1) % 3;
          }
          if (nextSquare >= 'A' && nextSquare <= 'Z') {
            cout << "COLLISSION AT " << j << ", " << i - 1 << endl;
            return vector<string>();
          }
          newField[i - 1][j] = field[i][j];
        } else if (cartDirections[cartIndex] == '>') {
          newField[i][j] = emptyField[i][j];
          char nextSquare = newField[i][j + 1];
          if (nextSquare == '-' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == STRAIGHT)) {
            cartDirections[cartIndex] = '>';
          } else if (nextSquare == '\\' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == RIGHT)) {
            cartDirections[cartIndex] = 'v';
          } else if (nextSquare == '/' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == LEFT)) {
            cartDirections[cartIndex] = '^';
          }
          if (nextSquare == '+') {
            nextIntersectionTurn[cartIndex] = (nextIntersectionTurn[cartIndex] + 1) % 3;
          }
          if (nextSquare >= 'A' && nextSquare <= 'Z') {
            cout << "COLLISSION AT " << j + 1 << ", " << i << endl;
            return vector<string>();
          }
          newField[i][j + 1] = field[i][j];
        } else if (cartDirections[cartIndex] == '<') {
          newField[i][j] = emptyField[i][j];
          char nextSquare = newField[i][j - 1];
          if (nextSquare == '-' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == STRAIGHT)) {
            cartDirections[cartIndex] = '<';
          } else if (nextSquare == '/' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == LEFT)) {
            cartDirections[cartIndex] = 'v';
          } else if (nextSquare == '\\' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == RIGHT)) {
            cartDirections[cartIndex] = '^';
          }
          if (nextSquare == '+') {
            nextIntersectionTurn[cartIndex] = (nextIntersectionTurn[cartIndex] + 1) % 3;
          }
          if (nextSquare >= 'A' && nextSquare <= 'Z') {
            cout << "COLLISSION AT " << j - 1 << ", " << i << endl;
            return vector<string>();
          }
          newField[i][j - 1] = field[i][j];
        }
      }
    }
  }

  return newField;
}

int main() {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> field;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      field.push_back(mystring);
    }
  }
  myfile.close();

  const int nCols = field[0].length();
  const int nRows = field.size() - 1;

  vector<string> emptyField = field;
  char cartIndex = 'A';
  vector<char> cartDirections;
  vector<int> nextIntersectionTurn;
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (field[i][j] == 'v' || field[i][j] == '^') {
        emptyField[i][j] = '|';
      } else if (field[i][j] == '<' || field[i][j] == '>') {
        emptyField[i][j] = '-';
      }

      if (field[i][j] == 'v' || field[i][j] == '^' || field[i][j] == '<' || field[i][j] == '>') {
        cartDirections.push_back(field[i][j]);
        nextIntersectionTurn.push_back(LEFT);
        field[i][j] = cartIndex;
        cartIndex += 1;
      }
    }
  }
  vector<string> newField = field;
  for (int i = 0; i < 20000; i += 1) {
    newField = moveCarts(newField, emptyField, cartDirections, nextIntersectionTurn);
    // printField(newField);
    if (newField.size() == 0) {
      break;
    }
  }
}