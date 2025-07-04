#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::vector;
using std::pair;

struct Edge {
  size_t targetNode;
  long long weight;
  Edge(): targetNode(0), weight(0) {}
  Edge(size_t _targetNode, long long _weight): targetNode(_targetNode), weight(_weight) {}
};

typedef vector <vector <Edge> > EdgeList;
typedef pair <size_t, size_t> Query;

void getInput(istream &input, EdgeList *const edges, vector <Query> *const queries) {
  size_t treeSize;
  input >> treeSize;
  edges->resize(treeSize);
  for (size_t edgeIndex = 0; edgeIndex + 1 < treeSize; ++edgeIndex) {
    size_t firstNode, secondNode;
    long long edgeWeight;
    input >> firstNode >> secondNode >> edgeWeight;
    --firstNode;
    --secondNode;
    (*edges)[firstNode].push_back(Edge(secondNode, edgeWeight));
    (*edges)[secondNode].push_back(Edge(firstNode, edgeWeight));
  }
  size_t queriesNumber;
  input >> queriesNumber;
  queries->resize(queriesNumber);
  for (size_t queryIndex = 0; queryIndex < queriesNumber; ++queryIndex) {
    Query currentQuery;
    input >> currentQuery.first >> currentQuery.second;
    --currentQuery.first;
    --currentQuery.second;
    (*queries)[queryIndex] = currentQuery;
  }
}

void writeResult(ostream &output, const vector <long long> &answers) {
  for (size_t answerIndex = 0; answerIndex < answers.size(); ++answerIndex) {
    output << answers[answerIndex] << '\n';
  }
}

void countingDFS(const EdgeList &edges, size_t currentNode,
                 vector <vector <Edge> > *const binaryUplinks,
                 vector <size_t> *const heights, vector <bool> &visited) {
  visited[currentNode] = true;
  for (size_t edgeIndex = 0; edgeIndex < edges[currentNode].size(); ++edgeIndex) {
    Edge currentEdge = edges[currentNode][edgeIndex];
    size_t nextNode = currentEdge.targetNode;
    if (!visited[nextNode]) {
      (*heights)[nextNode] = (*heights)[currentNode] + 1;
      (*binaryUplinks)[nextNode].push_back(Edge(currentNode, currentEdge.weight));
      size_t currentUplinkNode = currentNode;
      long long currentUplinkWeight = currentEdge.weight;
      size_t currentUplinkBinaryHeight = 0;
      while (currentUplinkBinaryHeight < (*binaryUplinks)[currentUplinkNode].size()) {
        Edge nextUplink = (*binaryUplinks)[currentUplinkNode][currentUplinkBinaryHeight];
        (*binaryUplinks)[nextNode].push_back(
          Edge(nextUplink.targetNode, currentUplinkWeight + nextUplink.weight));
        currentUplinkWeight += nextUplink.weight;
        currentUplinkNode = nextUplink.targetNode;
        ++currentUplinkBinaryHeight;
      }
      countingDFS(edges, currentEdge.targetNode, binaryUplinks, heights, visited);
    }
  }
}

void countBinaryUplinksAndHeights(const EdgeList &edges, size_t root,
                                  vector <vector <Edge> > *const binaryUplinks,
                                  vector <size_t> *const heights) {
  binaryUplinks->resize(edges.size());
  heights->resize(edges.size());
  (*heights)[root] = 0;
  vector <bool> visited(edges.size(), false);
  countingDFS(edges, root, binaryUplinks, heights, visited);
}

Edge uplinkByHeight(const vector <vector <Edge> > &binaryUplinks, size_t currentNode,
                    size_t height) {
  long long weight = 0;
  size_t currentBinaryHeight = binaryUplinks[currentNode].size() - 1;
  while (height > 0) {
    size_t currentUplinkHeight = (1 << currentBinaryHeight);
    if (currentBinaryHeight < binaryUplinks[currentNode].size() && height >= currentUplinkHeight) {
      height -= currentUplinkHeight;
      weight += binaryUplinks[currentNode][currentBinaryHeight].weight;
      currentNode = binaryUplinks[currentNode][currentBinaryHeight].targetNode;
    }
    --currentBinaryHeight;
  }
  return Edge(currentNode, weight);
}

size_t leastCommonAncestor(const vector <vector <Edge> > &binaryUplinks,
                      const vector <size_t> &heights, size_t root,
                      size_t firstNode, size_t secondNode) {
  if (heights[firstNode] > heights[secondNode]) {
    firstNode = uplinkByHeight(binaryUplinks, firstNode,
      heights[firstNode] - heights[secondNode]).targetNode;
  } else {
    secondNode = uplinkByHeight(binaryUplinks, secondNode,
      heights[secondNode] - heights[firstNode]).targetNode;
  }
  size_t result;
  if (firstNode == secondNode) {
    result = firstNode;
  } else {
    for (int uplinkBinaryHeight = binaryUplinks[firstNode].size() - 1;
      uplinkBinaryHeight >= 0; --uplinkBinaryHeight) {
      size_t firstAncestor = binaryUplinks[firstNode][uplinkBinaryHeight].targetNode;
      size_t secondAncestor = binaryUplinks[secondNode][uplinkBinaryHeight].targetNode;
      if (firstAncestor != secondAncestor) {
        firstNode = firstAncestor;
        secondNode = secondAncestor; 
      }
    }
    result = binaryUplinks[firstNode][0].targetNode;
  }
  return result;
}

long long pathWeight(const vector <vector <Edge> > &binaryUplinks,
                      const vector <size_t> &heights, size_t root,
                      size_t firstNode, size_t secondNode) {
  size_t pathTopNode = leastCommonAncestor(binaryUplinks, heights, root, firstNode, secondNode);
  size_t firstVerticalPathLength = heights[firstNode] - heights[pathTopNode];
  size_t secondVerticalPathLength = heights[secondNode] - heights[pathTopNode];
  return uplinkByHeight(binaryUplinks, firstNode, firstVerticalPathLength).weight +
    uplinkByHeight(binaryUplinks, secondNode, secondVerticalPathLength).weight;
}

void processQueries(const vector <vector <Edge> > &binaryUplinks, const vector <size_t> &heights,
                    const size_t root, const vector <Query> &queries, vector <long long> *answers) {
  answers->resize(queries.size());
  for (size_t queryIndex = 0; queryIndex < queries.size(); ++queryIndex) {
    (*answers)[queryIndex] = pathWeight(binaryUplinks, heights, root,
      queries[queryIndex].first, queries[queryIndex].second);
  }
}

int main() {
  EdgeList edges;
  vector <Query> queries;
  std::fstream fin("input.txt", std::fstream::in);
  getInput(fin, &edges, &queries);
  vector <vector <Edge> > binaryUplinks;
  vector <size_t> heights;
  const size_t root = 0;
  countBinaryUplinksAndHeights(edges, root, &binaryUplinks, &heights);
  vector <long long> answers;
  processQueries(binaryUplinks, heights, root, queries, &answers);
  writeResult(cout, answers);
  return 0;
}
