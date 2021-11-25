#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

enum turnDirections { LEFT, STRAIGHT, RIGHT };

void printField(const vector<string> &field) {
  for (string row : field) {
    cout << row << endl;
  }
}

void findLoneCart(const vector<string> &field) {
  const int nCols = field[0].length();
  const int nRows = field.size() - 1;
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (field[i][j] >= 'A' && field[i][j] <= 'Z') {
        cout << "Last cart is at " << j << "," << i << " " << field[i][j] << endl;
      }
    }
  }
}

vector<string> moveCarts (
  const vector<string> &field,
  const vector<string> &emptyField,
  vector<char> &cartDirections,
  vector<int> &nextIntersectionTurn,
  int &nCarts
) {
  const int nCols = field[0].length();
  const int nRows = field.size() - 1;

  vector<bool> cartMoved (26);
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (field[i][j] >= 'A' && field[i][j] <= 'Z') {
        int cartIndex = (int)field[i][j] - 65;
        cartMoved[cartIndex] = false;
      }
    }
  }
  vector<string> newField = field;
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (newField[i][j] >= 'A' && newField[i][j] <= 'Z') {
        int cartIndex = (int)newField[i][j] - 65;
        if (cartMoved[cartIndex]) continue;
        char cart = newField[i][j];
        int nextY;
        int nextX;
        char nextSquare;
        newField[i][j] = emptyField[i][j];

        if (cartDirections[cartIndex] == 'v') {
          nextY = i + 1;
          nextX = j;
          nextSquare = newField[i + 1][j];
          if (nextSquare == '|' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == STRAIGHT)) {
            cartDirections[cartIndex] = 'v';
          } else if (nextSquare == '\\' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == LEFT)) {
            cartDirections[cartIndex] = '>';
          } else if (nextSquare == '/' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == RIGHT)) {
            cartDirections[cartIndex] = '<';
          }
        } else if (cartDirections[cartIndex] == '^') {
          nextY = i - 1;
          nextX = j;
          nextSquare = newField[i - 1][j];
          if (nextSquare == '|' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == STRAIGHT)) {
            cartDirections[cartIndex] = '^';
          } else if (nextSquare == '/' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == RIGHT)) {
            cartDirections[cartIndex] = '>';
          } else if (nextSquare == '\\' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == LEFT)) {
            cartDirections[cartIndex] = '<';
          }
        } else if (cartDirections[cartIndex] == '>') {
          nextY = i;
          nextX = j + 1;
          nextSquare = newField[i][j + 1];
          if (nextSquare == '-' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == STRAIGHT)) {
            cartDirections[cartIndex] = '>';
          } else if (nextSquare == '\\' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == RIGHT)) {
            cartDirections[cartIndex] = 'v';
          } else if (nextSquare == '/' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == LEFT)) {
            cartDirections[cartIndex] = '^';
          }
        } else { // if (cartDirections[cartIndex] == '<')
          nextY = i;
          nextX = j - 1;
          nextSquare = newField[i][j - 1];
          if (nextSquare == '-' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == STRAIGHT)) {
            cartDirections[cartIndex] = '<';
          } else if (nextSquare == '/' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == LEFT)) {
            cartDirections[cartIndex] = 'v';
          } else if (nextSquare == '\\' || (nextSquare == '+' && nextIntersectionTurn[cartIndex] == RIGHT)) {
            cartDirections[cartIndex] = '^';
          }
        }
        if (nextSquare == '+') {
          nextIntersectionTurn[cartIndex] = (nextIntersectionTurn[cartIndex] + 1) % 3;
        }
        // cout << field[i][j] << " " << nextSquare << " " << nextIntersectionTurn[cartIndex] << " " << cartDirections[cartIndex] << endl;
        if (nextSquare >= 'A' && nextSquare <= 'Z') {
          nCarts -= 2;
          cout << "COLLISSION BETWEEN " << cart << " AND " << newField[nextY][nextX] << " AT " << nextX << "," << nextY << ". " << nCarts << " carts remaining." << endl;
          newField[nextY][nextX] = emptyField[nextY][nextX];
        } else {
          cartMoved[cartIndex] = true;
          newField[nextY][nextX] = cart;
        }
      }
    }
  }

  if (nCarts == 1) {
    findLoneCart(newField);
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
  int nCarts = (int)(cartIndex - 'A');

  vector<string> newField = field;
  for (int i = 0; i < 1000000; i += 1) {
    newField = moveCarts(newField, emptyField, cartDirections, nextIntersectionTurn, nCarts);
    if (nCarts == 1) {
      cout << i << endl;
      break;
    }
  }
}