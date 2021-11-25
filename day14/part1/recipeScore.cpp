#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void printRecipes(const vector<int> &recipes, int elf1, int elf2) {
  for (int i = 0; i < recipes.size(); i += 1) {
    char prefix = ' ';
    char suffix = ' ';
    if (i == elf1) {
      prefix = '(';
      suffix = ')';
    }
    if (i == elf2) {
      prefix = '[';
      suffix = ']';
    }
    cout << prefix << recipes[i] << suffix;
  }
  cout << endl;
}

int main() {
  const int input = 637061;

  vector<int> recipes;
  recipes.push_back(3);
  recipes.push_back(7);
  int elf1 = 0;
  int elf2 = 1;
  int maxSize = input + 10;

  while (recipes.size() < maxSize) {
    int nextRecipes = recipes[elf1] + recipes[elf2];
    if (nextRecipes > 9) {
      recipes.push_back(nextRecipes / 10);
      recipes.push_back(nextRecipes % 10);
    } else {
      recipes.push_back(nextRecipes);
    }

    elf1 = (elf1 + recipes[elf1] + 1) % recipes.size();
    elf2 = (elf2 + recipes[elf2] + 1) % recipes.size();
    // printRecipes(recipes, elf1, elf2);
  }

  for (int i = input; i < input + 10; i += 1) {
    cout << recipes[i];
  }
  cout << endl;
}
