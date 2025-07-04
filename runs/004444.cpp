#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using std::vector;

struct Edge {
  int vertex;
  int distance;

  Edge(int vertex, int distance): vertex(vertex), distance(distance) {}
};

typedef vector<vector<Edge> > Tree;

typedef vector<std::pair<int, int> > Queries;

void Input(Tree* tree, Queries* queries) {
  int size;
  std::cin >> size;
  assert(0 < size && size <= 40000);
  tree->resize(size);
  for (int i = 0; i + 1 < size; ++i) {
    int source, destination, distance;
    std::cin >> source >> destination >> distance;
    --source;
    --destination;
    assert(0 <= source && source < size && 0 <= destination && destination < size);//связность не проверяю, ибо сложно
    tree->at(source).push_back(Edge(destination, distance));
    tree->at(destination).push_back(Edge(source, distance));
  }
  int queries_number;
  std::cin >> queries_number;
  assert(0 <= queries_number && queries_number <= 40000);
  queries->resize(queries_number);
  for (int i = 0; i < queries_number; ++i) {
    int source, destination;
    std::cin >> source >> destination;
    assert(0 <= source && source < size && 0 <= destination && destination < size);
    queries->at(i) = std::make_pair(--source, --destination);
  }
}

class AlgorithmOfTarjan {
  enum Color {WHITE, GREY, BLACK};
  struct Query {
    int destination;
    int query_number;

    Query(int destination, int query_number): destination(destination), query_number(query_number) {}
  };

  const Tree& tree;
  vector<vector<Query> > queries_table;
  vector<Color> colors;
  vector<int> ancestors;
  vector<int> remotenesses;
  vector<int> result;

  int GetRoot(int vertex) {
      int parent = ancestors[vertex];
      if (parent == vertex) {
        return vertex;
      }
      int root = GetRoot(parent);
      ancestors[vertex] = root;
      return root;
    }

  void Union(int left, int right) {
      int left_root = GetRoot(left);
      int right_root = GetRoot(right);
      if (left_root == right_root) {
        return;
      }
      if (left_root < right_root) {
        ancestors[right_root] = left_root;
      } else {
        ancestors[left_root] = right_root;
      }
    }

  void SearchAnswers(int vertex) {
    for (int i = 0; i < queries_table[vertex].size(); ++i) {
      const Query& query = queries_table[vertex][i];
      int query_number = query.query_number;
      int destination = query.destination;
      if (colors[destination] == BLACK) {
        int LCA = GetRoot(destination);
        result[query_number] = remotenesses[vertex] + remotenesses[destination] - 2*remotenesses[LCA];
      }
    }
  }

  void DFS(int vertex, int shift) {
    if (colors[vertex] != WHITE) {
      return;
    }
    colors[vertex] = GREY;
    remotenesses[vertex] = shift;
    const vector<Edge>& edges = tree[vertex];
    for (int i = 0; i < edges.size(); ++i) {
      const Edge& edge = edges[i];
      int destination = edge.vertex;
      int distance = edge.distance;
      DFS(destination, shift + distance);
      Union(vertex, destination);
    }
    SearchAnswers(vertex);
    colors[vertex] = BLACK;
  }

 public:

  AlgorithmOfTarjan(const Tree& tree, const Queries& queries): tree(tree) {
     int size = tree.size();
     remotenesses.resize(size);
     colors.assign(size, WHITE);
     ancestors.resize(size);
     for (int i = 0; i < size; ++i) {
       ancestors[i] = i;
     }
     int queries_number = queries.size();
     result.resize(queries_number);
     queries_table.resize(size);
     for (int i = 0; i < queries_number; ++i) {
       int source = queries[i].first;
       int destination = queries[i].second;
       queries_table[source].push_back(Query(destination, i));
       queries_table[destination].push_back(Query(source, i));
     }
   }

  vector<int> Execute() {
    DFS(0, 0);
    return result;
  }
};

int main() {
  Tree tree;
  Queries queries;
  Input(&tree, &queries);
  vector<int> answers = AlgorithmOfTarjan(tree, queries).Execute();
  for (int i = 0; i < answers.size(); ++i) {
    std::cout << answers[i] << std::endl;
  }

  return 0;
}