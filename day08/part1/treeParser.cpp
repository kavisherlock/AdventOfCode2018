// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <regex>
#include <algorithm>
using namespace std;

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<int> nodes;
  if (myfile.is_open()) {
    string mystring;
    while(getline(myfile, mystring)) {
      stringstream lineStream(mystring);
      int value;
      while(lineStream >> value) {
        nodes.push_back(value);
      }
    }
  }
  myfile.close();
 
  int metadataTotal = 0;
  stack<pair<int, int>> nodeStack;
  for (int i = 0; i < nodes.size(); i += 1) {
    while (nodes[i] != 0) {
      pair<int, int> node(nodes[i], nodes[i + 1]);
      nodeStack.push(node);
      i += 2;
    }
    int nMetaData = nodes[i + 1];
    i += 2;
    for (int j = 0; j < nMetaData; j += 1) {
      metadataTotal += nodes[i + j];
    }
    i += nMetaData;

    pair<int, int> lastParent = nodeStack.top();
    nodeStack.pop();
    lastParent.first -= 1;
    if (lastParent.first == 0) {
      while (lastParent.first == 0) {
        int nMetaData = lastParent.second;
        for (int j = 0; j < nMetaData; j += 1) {
          metadataTotal += nodes[i + j];
        }
        i += nMetaData;
        if (nodeStack.empty()) {
          break;
        }
        lastParent = nodeStack.top();
        nodeStack.pop();
        lastParent.first -= 1;
      }
    }

    nodeStack.push(lastParent);
    i -= 1;
  }

  cout <<  metadataTotal << endl;

  return 0;
}