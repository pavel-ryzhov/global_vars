#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>

using std::cout;
using std::cin;
using std::pair;
using std::vector;
using std::swap;
using std::qsort;
using std::min;
using std::queue;
const int NULL_POINTER = -1;

struct Node {
  Node() {
    id = NULL_POINTER;
    distanceFromParent = 0;
    depth = 0;
    parentId = NULL_POINTER;
    isPassed = false;
  }
  int id;
  bool isPassed;
  int distanceFromParent;
  int depth;
  int parentId;
  vector<pair<int, int> > neighbors;
};


  bool comparator(const pair<pair<int, int>, int> p1, const pair<pair<int, int>, int> p2) {
    return min<int>(p1.first.first, p1.first.second) < min<int>(p2.first.first, p2.first.second);
  }


vector<pair<pair<int, int>, int> > getEdgeArray() {
  vector<pair<pair<int, int>, int> > edges;
  int numOfNodes = 0;
  cin >> numOfNodes;
  edges.resize(numOfNodes - 1);
  for (int idEdge = 0; idEdge < numOfNodes - 1; ++idEdge) {
    int parentId = 0;
    cin >> parentId;
    --parentId;
    int curNodeId = 0;
    cin >> curNodeId;
    --curNodeId;
    int distanceFromParent = 0;
    cin >> distanceFromParent;
    edges[idEdge].first.first = curNodeId;
    edges[idEdge].first.second = parentId;
    edges[idEdge].second = distanceFromParent;
  }
  return edges;
}


vector<Node> buildTree(const vector<pair<pair<int, int>, int> >& edgeArray) {
  vector<Node> nodeArray;
  nodeArray.resize(edgeArray.size() + 1);
  for (int edgeId = 0; edgeId < edgeArray.size(); ++edgeId) {
    nodeArray[edgeArray[edgeId].first.first].neighbors.
      push_back(pair<int, int>(edgeArray[edgeId].first.second, edgeArray[edgeId].second));
    nodeArray[edgeArray[edgeId].first.second].neighbors.
      push_back(pair<int, int>(edgeArray[edgeId].first.first, edgeArray[edgeId].second));
  }
  for (int nodeId = 0; nodeId < nodeArray.size(); ++nodeId) {
    nodeArray[nodeId].id = nodeId;
  }
  nodeArray[0].depth = 0;
  nodeArray[0].parentId = NULL_POINTER;
  nodeArray[0].distanceFromParent = 0;
  queue<int> queueOfTreeRound;
  queueOfTreeRound.push(0);
  while (!queueOfTreeRound.empty()) {
    int curNodeId = queueOfTreeRound.front();
    for (int relativeIdOfneighbor = 0; relativeIdOfneighbor < nodeArray[curNodeId].neighbors.size(); ++relativeIdOfneighbor) {
      int idOfNeighbor = nodeArray[curNodeId].neighbors[relativeIdOfneighbor].first;
      if (!nodeArray[idOfNeighbor].isPassed) {
        nodeArray[idOfNeighbor].depth = nodeArray[curNodeId].depth + 1;
        nodeArray[idOfNeighbor].distanceFromParent = nodeArray[curNodeId].neighbors[relativeIdOfneighbor].second;
        nodeArray[idOfNeighbor].parentId = nodeArray[curNodeId].id;
        queueOfTreeRound.push(idOfNeighbor);
      }

    }
    nodeArray[curNodeId].isPassed = true;
    queueOfTreeRound.pop();
  }
  return nodeArray;
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
  vector<Node> tree = buildTree(getEdgeArray());



  printAnswers(tree, getRequestArray());
  return 0;
}

