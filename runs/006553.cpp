#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <deque>
#include <iterator>

using std::cout;
using std::cin;
using std::vector;
using std::deque;
using std::pair;
using std::make_pair;
using std::swap;

template<typename T>
class RMQFinder {
public:
  RMQFinder(const vector<T>& v_) : v(v_) {}
  // O(n*log(n)) preprocessing time
  void Preprocess() {
    size_t n = v.size();
    size_t m = log2(n) + 1;
    min_table.resize(n, vector<T>(m));
    index_table.resize(n, vector<size_t>(m));
    for (size_t i = 0; i < n; ++i) {
      min_table[i][0] = v[i];
      index_table[i][0] = i;
    }
    for (size_t j = 1; j < m; ++j) {
      for (size_t i = 0; i + (1 << j) <= n; ++i) {
        if (min_table[i][j - 1] < min_table[i + (1 << (j - 1))][j - 1]) {
          min_table[i][j] = min_table[i][j - 1];
          index_table[i][j] = index_table[i][j - 1];
        } else {
          min_table[i][j] = min_table[i + (1 << (j - 1))][j - 1];
          index_table[i][j] = index_table[i + (1 << (j - 1))][j - 1];
        }
      }
    }
  }
  // RMQ(left, right) = min_{left <= i < right} { v[i] }
  size_t RMQ(size_t left, size_t right) const { 
    size_t len = right - left;
    size_t k = log2(len);
    if (min_table[left][k] < min_table[right - (1 << k)][k]) {
      return index_table[left][k];
    } else {
      return index_table[right - (1 << k)][k];
    }
  }
private:
  const vector<T>& v;
  vector<vector<T> > min_table; 
  vector<vector<size_t> > index_table;
  static size_t log2(size_t x) {
    size_t result = 0;
    while (x >>= 1) {
      ++result;
    }
    return result;
  }
};


class DistanceFinder {
public:
  DistanceFinder() : graph(MAX_N), root(-1), finder(depths) {}

  void AddEdge(int u, int v, int distance) {
    --u; 
    --v;
    if (root == -1) {
      root = u;
    }
    graph[u].push_back(make_pair(v, distance));
    graph[v].push_back(make_pair(u, distance));
  }

  void Preprocess() {
    index.resize(MAX_N);
    distance_from_root.resize(MAX_N);
    visited.resize(MAX_N, false);
    euler_tour.reserve(2 * MAX_N);
    depths.reserve(2 * MAX_N);
    EulerTour(root, 0);
    finder.Preprocess();
  }

  int Distance(int u, int v) const {
    --u; 
    --v;
    size_t left = index[u], right = index[v];
    if (left > right) {
      swap(left, right);
    }
    int lca = euler_tour[finder.RMQ(left, right + 1)];
    return distance_from_root[u] + distance_from_root[v] - 2 * distance_from_root[lca];
  }

private:
  void EulerTour(int u, int depth) {
    visited[u] = true;
    index[u] = euler_tour.size();
    euler_tour.push_back(u);
    depths.push_back(depth);
    for (size_t i = 0; i < graph[u].size(); ++i) {
      int v = graph[u][i].first;
      if (visited[v]) {
        continue;
      }
      int distance = graph[u][i].second;
      distance_from_root[v] = distance_from_root[u] + distance;
      EulerTour(v, depth + 1);
      euler_tour.push_back(u);
      depths.push_back(depth);
    }
  }

  const static int MAX_N = 40000;
  vector<vector<pair<int, int> > > graph;
  int root;
  vector<int> euler_tour;
  vector<int> depths; // depths of nodes in Euler tour
  vector<size_t> index; // index[v] is the index of the first occurence of v in Euler tour;
  vector<int> distance_from_root;
  deque<bool> visited;
  RMQFinder<int> finder;
};

void InputGraph(DistanceFinder* finder) {
  size_t size;
  cin >> size;
  for (size_t i = 0; i + 1 < size; ++i) {
    int u, v, dist;
    cin >> u >> v >> dist;
    finder->AddEdge(u, v, dist);
  }
}

void Answer(const DistanceFinder& finder) {
  size_t size;
  cin >> size;
  vector<int> answer(size);
  for (size_t i = 0; i < size; ++i) {
    int u, v;
    cin >> u >> v;
    answer[i] = finder.Distance(u, v);
  }
  std::copy(answer.begin(), answer.end(), std::ostream_iterator<int>(cout, "\n"));
}

int main() {
  DistanceFinder finder;
  InputGraph(&finder);
  finder.Preprocess();
  Answer(finder);
  return 0;
}
