#include <iostream>
#include <vector>

using namespace std;

unsigned short int N = 0;
unsigned int count = 0;

struct vertex {
  unsigned short int vert;
  unsigned short int weight;
};

unsigned int lengthPath(unsigned short int vertBegin,
                        unsigned short int vertEnd,
                        vector<unsigned short int> order,
                        vector<unsigned short int> height,
                        vector<unsigned short int> first,
                        vector<unsigned int> weightVect) {
  unsigned int minH = N;
  unsigned short int minI = 0;
  if (first[vertBegin-1] < first[vertEnd-1]) {
    for(unsigned short int i = first[vertBegin-1]; i <= first[vertEnd-1]; i++) {
      if (height[order[i]-1] < minH) {
        minH = height[order[i]-1];
        minI = order[i];
      }
    }
  } else if (first[vertBegin-1] > first[vertEnd-1]) {
    for(unsigned short int i = first[vertEnd-1]; i <= first[vertBegin-1]; i++) {
      if (height[order[i]-1] < minH) {
        minH = height[order[i]-1];
        minI = order[i];
      }
    }
  } else if (first[vertBegin-1] == first[vertEnd-1]) {
    return 0;
  }
  return weightVect[vertBegin-1]+weightVect[vertEnd-1]-2*weightVect[minI-1];
}

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

void showVector(vector<unsigned short int> vect) {
  vector<unsigned short int>::iterator iter;
  for (iter = vect.begin(); iter != vect.end(); iter++) {
    cout << *iter << endl;
  }
  cout << endl;
}

int main() {
  unsigned short int M = 0;
  unsigned short int i = 0;
  vector<unsigned short int> order;
  vector<unsigned short int> height;
  vector<unsigned short int> first;
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
  for (i = 0; i < M; i++) {
    cin >> vertBegin;
    cin >> vertEnd;
    cout << lengthPath(vertBegin, vertEnd, order, height, first, weightVect) << endl;
  }
  delete [] adjacentVert;
  return 0;
}
