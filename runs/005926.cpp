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
                        unsigned int *weightVect,
                        vector<unsigned int> *brackets) {
  if (vertBegin == vertEnd) {
    return 0;
  }
  unsigned short int minI = 0;
  vector<unsigned int>::iterator iterBegin = brackets[vertBegin-1].begin();
  vector<unsigned int>::iterator iterEnd = brackets[vertEnd-1].begin();
  while (iterBegin != brackets[vertBegin-1].end()) {
    if (*iterBegin != *iterEnd || iterEnd == brackets[vertEnd-1].end()) {
      break;
    }
    *iterBegin++;
    *iterEnd++;
  }
  if (iterEnd == brackets[vertEnd-1].end() && iterBegin == brackets[vertBegin-1].end()) {
    if (weightVect[vertBegin-1] > weightVect[vertEnd-1]) {
      return weightVect[vertBegin-1]-weightVect[vertEnd-1];
    } else {
      return weightVect[vertEnd-1]-weightVect[vertBegin-1];
    }
  } else {
    *iterBegin--;
    minI = order[*iterBegin];
  }
  return weightVect[vertBegin-1]+weightVect[vertEnd-1]-2*weightVect[minI-1];
}

void rek(unsigned short int vert,
         unsigned short int lastVert,
         unsigned int weight,
         vector<vertex> *adjacentVert,
         unsigned short int *countAdjVert,
         vector<unsigned short int> &order,
         unsigned int *weightVect,
         vector<unsigned int> *brackets,
         vector<unsigned int> bracket) {
  order.push_back(vert);
  weightVect[vert-1] = weight;
  brackets[vert-1] = bracket;
  if (countAdjVert[vert-1] > 2) {
    bracket.push_back(count);
  }
  brackets[vert-1] = bracket;
  count++;
  if (countAdjVert[vert-1] == 1) {
    return;
  }
  for (unsigned short int i = 0; i < countAdjVert[vert-1]; i++) {
    if (adjacentVert[vert-1].at(i).vert != lastVert) {
      if (countAdjVert[vert-1] > 2) {
        bracket.push_back(count);
      }
      rek(adjacentVert[vert-1].at(i).vert, vert, weight+adjacentVert[vert-1].at(i).weight,
          adjacentVert, countAdjVert, order, weightVect, brackets, bracket);
      if (countAdjVert[vert-1] > 2) {
        bracket.pop_back();
        order.push_back(vert);
        count++;
      }
    }
  }
}

void showBrackets(vector<unsigned int> *brackets) {
  for (unsigned short int l = 0; l < N; l++) {
    cout << "   " << l+1 << endl;
    int i = 1;
    vector<unsigned int>::iterator iter;
    for (iter = brackets[l].begin(); iter != brackets[l].end(); iter++) {
      cout << i << "| " << *iter << endl;
      i++;
    }
    cout << endl;
  }
}

int main() {
  unsigned short int M = 0;
  unsigned short int i = 0;
  unsigned short int vertMaxCount = 1;
  vector<unsigned short int> order;
  unsigned int *weightVect;
  vector<vertex> *adjacentVert;
  vector<unsigned int> *brackets;
  unsigned short int *countAdjVert;
  vertex vert;
  unsigned short int vertBegin = 0;
  unsigned short int vertEnd = 0;
  unsigned short int weight = 0;
  cin >> N;
  weightVect = new unsigned int[N];
  brackets = new vector<unsigned int> [N];
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
    if (countAdjVert[vertBegin-1] > countAdjVert[vertMaxCount-1]) {
      vertMaxCount = vertBegin;
    }
    if (countAdjVert[vertEnd-1] > countAdjVert[vertMaxCount-1]) {
      vertMaxCount = vertEnd;
    }
  }
  vert.vert = 0;
  vert.weight = 0;
  adjacentVert[vertMaxCount-1].push_back(vert);
  countAdjVert[vertMaxCount-1]++;
  vector<unsigned int> bracket;
  bracket.push_back(0);
  rek(vertMaxCount, 0, 0, adjacentVert, countAdjVert, order, weightVect, brackets, bracket);
  cin >> M;
  for (i = 0; i < M; i++) {
    cin >> vertBegin;
    cin >> vertEnd;
    cout << lengthPath(vertBegin, vertEnd, order, weightVect, brackets) << endl;
  }
  delete [] adjacentVert;
  return 0;
}
