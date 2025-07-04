#include <iostream>
#include <vector>

using namespace std;

unsigned short int N = 0;
unsigned int count = 0;

struct vertex {
  unsigned short int vert;
  unsigned short int weight;
};

void rek(unsigned short int vert,
         unsigned short int lastVert,
         unsigned short int h,
         unsigned int weight,
         vector<vertex> *adjacentVert,
         unsigned short int *countAdjVert,
         vector<unsigned short int> &order,
         vector<unsigned short int> &height,
         vector<unsigned short int> &first,
         vector<unsigned int> &weightVect) {
  order.push_back(vert);
  height[vert-1] = h;
  first[vert-1] = count;
  weightVect[vert-1] = weight;
  count++;
  if (countAdjVert[vert-1] == 1) {
    return;
  }
  for (unsigned short int i = 0; i < countAdjVert[vert-1]; i++) {
    if (adjacentVert[vert-1].at(i).vert != lastVert) {
      rek(adjacentVert[vert-1].at(i).vert, vert, h+1, weight+adjacentVert[vert-1].at(i).weight,
          adjacentVert, countAdjVert, order, height, first, weightVect);
      order.push_back(vert);
      count++;
    }
  }
}

unsigned short int buildTree (vector<unsigned short int> order,
                              vector<unsigned short int> height,
                              vector<unsigned short int> &treeRMQ,
                              unsigned short int vert,
                              unsigned int l,
                              unsigned int r) {
  if (l == r) {
    return treeRMQ[vert-1] = order[l];
  }
  unsigned int m = (l+r)/2;
  unsigned short int minL = buildTree(order, height, treeRMQ, vert*2, l, m);
  unsigned short int minR = buildTree(order, height, treeRMQ, vert*2+1, m+1, r);
  if (height[minL-1] < height[minR-1]) {
    return treeRMQ[vert-1] = minL;
  } else {
    return treeRMQ[vert-1] = minR;
  }
}

unsigned short int minHeight (vector<unsigned short int> order,
                              vector<unsigned short int> height,
                              vector<unsigned short int> treeRMQ,
                              unsigned short int vert,
                              unsigned int l,
                              unsigned int r,
                              unsigned int constL,
                              unsigned int constR) {
  if (l == constL && r == constR) {
    return treeRMQ[vert-1];
  }
  unsigned int m = (constL+constR)/2;
  if (l < m+1 && r > m) {
    unsigned short int minL = minHeight(order, height, treeRMQ, vert*2, l, m, constL, m);
    unsigned short int minR = minHeight(order, height, treeRMQ, vert*2+1, m+1, r, m+1, constR);
    if (height[minL-1] < height[minR-1]) {
      return minL;
    } else {
      return minR;
    }
  } else if(l > m && r > m) {
    return minHeight(order, height, treeRMQ, vert*2+1, l, r, m+1, constR);
  } else if(l < m+1 && r < m+1) {
    return minHeight(order, height, treeRMQ, vert*2, l, r, constL, m);
  }
  return 0;
}

unsigned int lengthPath(unsigned short int vertBegin,
                        unsigned short int vertEnd,
                        unsigned int constL,
                        unsigned int constR,
                        vector<unsigned short int> order,
                        vector<unsigned short int> height,
                        vector<unsigned short int> first,
                        vector<unsigned short int> treeRMQ,
                        vector<unsigned int> weightVect) {
  unsigned int minI = 0;
  minI = minHeight(order, height, treeRMQ, 1, min(first[vertBegin-1], first[vertEnd-1]),
                   max(first[vertBegin-1], first[vertEnd-1]), constL, constR);
  return weightVect[vertBegin-1]+weightVect[vertEnd-1]-2*weightVect[minI-1];
}

void showVector(vector<unsigned short int> vect) {
  int i = 1;
  vector<unsigned short int>::iterator iter;
  for (iter = vect.begin(); iter != vect.end(); iter++) {
    cout << i << "  " << *iter << endl;
    i++;
  }
  cout << endl;
}

int main() {
  unsigned short int M = 0;
  unsigned short int i = 0;
  vector<unsigned short int> order;
  vector<unsigned short int> height;
  vector<unsigned short int> first;
  vector<unsigned short int> treeRMQ;
  vector<unsigned int> weightVect;
  vector<vertex> *adjacentVert;
  unsigned short int *countAdjVert;
  vertex vert;
  unsigned short int vertBegin = 0;
  unsigned short int vertEnd = 0;
  unsigned short int weight = 0;
  cin >> N;
  weightVect.resize(N, 0);
  height.resize(N, 0);
  first.resize(N, 0);
  adjacentVert = new vector<vertex> [N];
  countAdjVert = new unsigned short int[N];
  for (i = 0; i < N; i++) {
    countAdjVert[i] = 0;
  }
  for (i = 0; i < N-1; i++) {
    cin >> vertBegin;
    cin >> vertEnd;
    cin >> weight;
    vert.vert = vertEnd;
    vert.weight = weight;
    adjacentVert[vertBegin-1].push_back(vert);
    vert.vert = vertBegin;
    vert.weight = weight;
    adjacentVert[vertEnd-1].push_back(vert);
    countAdjVert[vertBegin-1]++;
    countAdjVert[vertEnd-1]++;
  }
  vert.vert = 0;
  vert.weight = 0;
  adjacentVert[1-1].push_back(vert);
  countAdjVert[1-1]++;
  rek(1, 0, 1, 0, adjacentVert, countAdjVert, order, height, first, weightVect);
  cin >> M;
  treeRMQ.resize(order.size()*4, 0);
  buildTree(order, height, treeRMQ, 1, 0, order.size()-1);
  unsigned int constL = 0;
  unsigned int constR = order.size()-1;
  for (i = 0; i < M; i++) {
    cin >> vertBegin;
    cin >> vertEnd;
    cout << lengthPath(vertBegin, vertEnd, constL, constR, order, height, first, treeRMQ, weightVect) << endl;
  }
  delete [] adjacentVert;
  return 0;
}
