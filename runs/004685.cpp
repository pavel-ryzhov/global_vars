#include <iostream>
#include <cstdlib>
#include <vector>

using std::cout;
using std::cin;
using std::pair;
using std::vector;

const int NULL_POINTER = -1;

struct Node {
  Node() {
    distanceFromParent = 0;
    depth = 0;
    int parentId = NULL_POINTER;
  }

  int distanceFromParent;
  int depth;
  int parentId;
};

vector<Node> buildTree() {
  int numOfNodes = 0;
  vector<Node> nodesArray;
  cin >> numOfNodes;
  nodesArray.resize(numOfNodes);
  nodesArray[0].parentId = NULL_POINTER;
  for (int idEdge = 0; idEdge < numOfNodes - 1; ++idEdge) {
    int parentId = 0;
    cin >> parentId;
    --parentId;
    int curNodeId = 0;
    cin >> curNodeId;
    --curNodeId;
    int distanceFromParent = 0;
    cin >> distanceFromParent;
    nodesArray[curNodeId].depth = nodesArray[parentId].depth + 1;
    nodesArray[curNodeId].distanceFromParent = distanceFromParent;
    nodesArray[curNodeId].parentId = parentId;
  }
  return nodesArray;
}

int getPathBeforeOneLevel(const vector<Node>& nodeArray, int& idFirstNode, int idSecondNode) {
  int lengthOfPath = 0;
  while (nodeArray[idFirstNode].depth > nodeArray[idSecondNode].depth) {
    lengthOfPath += nodeArray[idFirstNode].distanceFromParent;
    idFirstNode = nodeArray[idFirstNode].parentId;
  }
  return lengthOfPath;
}

int getPathForSameLevelNodes(const vector<Node>& nodeArray, int idFirstNode, int idSecondNode) {
  int firstLength = 0;
  int secnodLength = 0;
  while (idFirstNode != idSecondNode) {
    firstLength += nodeArray[idFirstNode].distanceFromParent;
    secnodLength += nodeArray[idSecondNode].distanceFromParent;
    idFirstNode = nodeArray[idFirstNode].parentId;
    idSecondNode = nodeArray[idSecondNode].parentId;
  }
  return firstLength + secnodLength;
}

int getPath(const vector<Node>& nodeArray, int idFirstNode, int idSecondNode) {
  if (nodeArray[idFirstNode].depth == nodeArray[idSecondNode].depth) {
    return getPathForSameLevelNodes(nodeArray, idFirstNode, idSecondNode);
  }
  else {
    int length = 0;
    if (nodeArray[idFirstNode].depth > nodeArray[idSecondNode].depth) {
      length += getPathBeforeOneLevel(nodeArray, idFirstNode, idSecondNode);
      length += getPathForSameLevelNodes(nodeArray, idFirstNode, idSecondNode);
    }
    else {
      length += getPathBeforeOneLevel(nodeArray, idSecondNode, idFirstNode);
      length += getPathForSameLevelNodes(nodeArray, idFirstNode, idSecondNode);
    }
    return length;
  }
}

vector<pair<int, int> > getRequestArray() {
  int size = 0;
  cin >> size;
  vector<pair<int, int> > array;
  array.resize(size);
  for (int idRequest = 0; idRequest < size; ++idRequest) {
    cin >> array[idRequest].first;
    cin >> array[idRequest].second;
  }
  return array;
}

void printAnswers(const vector<Node>& nodeArray, const vector<pair<int, int> >& requestArray) {
  for (int idRequest = 0; idRequest < static_cast<int>(requestArray.size()); ++idRequest) {
    cout << getPath(nodeArray, requestArray[idRequest].first - 1, requestArray[idRequest].second - 1) << "\n";
  }
}

int main() {
  vector<Node> tree = buildTree();
  printAnswers(tree, getRequestArray());
  return 0;
}

