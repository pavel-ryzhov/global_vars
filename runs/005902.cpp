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
                        unsigned int size,
                        vector<unsigned short int> order,
                        unsigned short int *height,
                        unsigned short int *first,
                        unsigned short int *weightVect,
                        vector<unsigned short int> minHeight) {
  if (first[vertBegin-1] == first[vertEnd-1]) {
    return 0;
  }
  unsigned short int begin = min(first[vertBegin-1],first[vertEnd-1]);
  unsigned short int end = max(first[vertBegin-1],first[vertEnd-1]);
  unsigned int minH = N;
  unsigned short int minI = 0;
  if (begin < (size-1)/2 && end > (size-1)/2) {
    if (height[minHeight[begin]-1] < height[minHeight[end]-1]) {
      minI = minHeight[begin];
    } else {
      minI = minHeight[end];
    }
  } else if (end < (size-1)/2 && height[minHeight[begin]-1] < height[minHeight[end]-1]) {
    minI = minHeight[begin];
  } else if (begin > (size-1)/2 && height[minHeight[begin]-1] > height[minHeight[end]-1]) {
    minI = minHeight[end];
  } else {
    for(unsigned short int i = begin; i <= end; i++) {
      if (height[order[i]-1] < minH) {
        minH = height[order[i]-1];
        minI = order[i];
      }
    }
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
         unsigned short int *height,
         unsigned short int *first,
         unsigned short int *weightVect) {
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
      if (countAdjVert[vert-1] > 2) {
        order.push_back(vert);
        count++;
      }
    }
  }
}

void buildVect(unsigned int size,
               vector<unsigned short int> order,
               unsigned short int *height,
               vector<unsigned short int> &minHeight) {
  unsigned int i = 0;
  minHeight.resize(size);
  minHeight[(size-1)/2] = order[(size-1)/2];
  minHeight[0] = 1;
  if (size > 2) {
    for (i = (size-1)/2-1; i > 0; i--) {
      if (height[minHeight[i+1]-1] < height[order[i]-1]) {
        minHeight[i] = minHeight[i+1];
      } else {
        minHeight[i] = order[i];
      }
    }
  }
  if (size > 1) {
    for (i = (size-1)/2+1; i < order.size(); i++) {
      if (height[minHeight[i-1]-1] < height[order[i]-1]) {
        minHeight[i] = minHeight[i-1];
      } else {
        minHeight[i] = order[i];
      }
    }
  }
}

void reset(unsigned short int *array) {
  for (unsigned short int i = 0; i < N; i++) {
    array[i] = 0;
  }
}

int main() {
  unsigned short int M = 0;
  unsigned short int i = 0;
  vector<unsigned short int> order;
  unsigned short int *height;
  unsigned short int *first;
  unsigned short int *weightVect;
  vector<unsigned short int> minHeight;
  vector<vertex> *adjacentVert;
  unsigned short int *countAdjVert;
  vertex vert;
  unsigned short int vertBegin = 0;
  unsigned short int vertEnd = 0;
  unsigned short int weight = 0;
  cin >> N;
  weightVect = new unsigned short int[N];
  height = new unsigned short int[N];
  first = new unsigned short int[N];
  reset(weightVect);
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
  unsigned int size = order.size();
  buildVect(size, order, height, minHeight);
  cin >> M;
  for (i = 0; i < M; i++) {
    cin >> vertBegin;
    cin >> vertEnd;
    cout << lengthPath(vertBegin, vertEnd, size, order, height, first, weightVect, minHeight) << endl;
  }
  delete [] adjacentVert;
  return 0;
}
