#include <iostream>
#include <vector>
 
using std::vector;
using std::cin;
using std::cout;

vector<bool> dfs_used_vertex;
vector<int> dfs_time_in, dfs_time_out;
int timer_for_dfs = 0;

struct Ancestor {
  public:
    int ancestor_index;
    int length_to_ancestor;
};

struct EdgeFromVertex {
  public:
    int end_edge;
    int length_edge;
    EdgeFromVertex(int end = 0, int length = 0) {
      end_edge = end;
      length_edge = length;
    }
};

int GetLogarithm(const int number) {
  int logarithm = 1;
  while ((1 << logarithm) <= number) {
    ++logarithm;
  }
  return logarithm;
}

void DepthFirstSearch(const vector< vector<EdgeFromVertex> >& graph, const int vertex_index,
  vector< vector<Ancestor> >& ancestors, const int parent_vertex_index = 0, const int length_to_parent = 0) {
  dfs_used_vertex[vertex_index] = true;
  dfs_time_in[vertex_index] = ++timer_for_dfs;
  ancestors[vertex_index][0].ancestor_index = parent_vertex_index;
  ancestors[vertex_index][0].length_to_ancestor = length_to_parent;
  for (int index = 1; index <= GetLogarithm(static_cast<int>(graph.size())); ++index) {
    ancestors[vertex_index][index].ancestor_index =
      ancestors[ancestors[vertex_index][index - 1].ancestor_index][index - 1].ancestor_index;
    ancestors[vertex_index][index].length_to_ancestor = ancestors[vertex_index][index - 1].length_to_ancestor +
      ancestors[ancestors[vertex_index][index - 1].ancestor_index][index - 1].length_to_ancestor;
  }
  for (int neighbor_index = 0; neighbor_index < static_cast<int>(graph[vertex_index].size());
    ++neighbor_index) {
    int neighbor_vertex_index = graph[vertex_index][neighbor_index].end_edge;
    if ( !dfs_used_vertex[neighbor_vertex_index] ) {
      DepthFirstSearch(graph, neighbor_vertex_index, ancestors, vertex_index,
        graph[vertex_index][neighbor_index].length_edge);
    }
  }
  dfs_time_out[vertex_index] = ++timer_for_dfs;
}

bool IsAncestor(int first_vertex_index, int second_vertex_index) {
  return ( (dfs_time_in[first_vertex_index] <= dfs_time_in[second_vertex_index]) &&
    (dfs_time_out[first_vertex_index] >= dfs_time_out[second_vertex_index]) );
}

int FindLengthToLCA(const vector< vector<EdgeFromVertex> >& graph, const vector< vector<Ancestor> >& ancestors,
  const int lca, int vertex) {
  if (vertex == lca) {
    return 0;
  }
  int length = 0;
  for (int index = GetLogarithm(static_cast<int>(graph.size())); index >= 0; --index) {
    if (!IsAncestor(ancestors[vertex][index].ancestor_index, lca)) {
      length += ancestors[vertex][index].length_to_ancestor;
      vertex = ancestors[vertex][index].ancestor_index;
    }
  }
  length += ancestors[vertex][0].length_to_ancestor;
  return length;
}

int FindLCA (const vector< vector<EdgeFromVertex> >& graph, const vector< vector<Ancestor> >& ancestors,
  int first_vertex, int second_vertex) {
  if (IsAncestor(first_vertex, second_vertex)) {
    return first_vertex;
  }
  if (IsAncestor(second_vertex, first_vertex)) {
    return second_vertex;
  }
  for (int index = GetLogarithm(static_cast<int>(graph.size())); index >= 0; --index) {
    if (!IsAncestor(ancestors[first_vertex][index].ancestor_index, second_vertex)) {
      first_vertex = ancestors[first_vertex][index].ancestor_index;
    }
  }
  return ancestors[first_vertex][0].ancestor_index;
}

vector< vector<EdgeFromVertex> > ReadGraph() {
  int vertex_number;
  cin >> vertex_number;
  vector< vector<EdgeFromVertex> > graph(vertex_number);
  for (int index = 0; index < vertex_number - 1; ++index) {
    int first_end_edge, second_end_edge, length_edge;
    cin >> first_end_edge >> second_end_edge >> length_edge;
    graph[first_end_edge - 1].push_back( EdgeFromVertex(second_end_edge - 1, length_edge) );
    graph[second_end_edge - 1].push_back( EdgeFromVertex(first_end_edge - 1, length_edge) );
  }
  return graph;
}

void PreProcessing(const vector< vector<EdgeFromVertex> >& graph, vector< vector<Ancestor> >& ancestors) {
  int vertex_number = static_cast<int>(graph.size());
  dfs_time_in.resize(vertex_number);
  dfs_time_out.resize(vertex_number);
  dfs_used_vertex.assign(vertex_number, false);
  ancestors.resize(vertex_number);
  for (int index = 0; index < vertex_number; ++index) {
    ancestors[index].resize(GetLogarithm(static_cast<int>(graph.size())) + 1);
  }
  DepthFirstSearch(graph, 0, ancestors);
}

void GetSolution(const vector< vector<EdgeFromVertex> >& graph) {
  vector< vector<Ancestor> > ancestors;
  PreProcessing(graph, ancestors);
  int request_number;
  cin >> request_number;
  for (int index = 0; index < request_number; ++index) {
    int first_vertex, second_vertex;
    cin >> first_vertex >> second_vertex;
    int lca = FindLCA(graph, ancestors, first_vertex - 1, second_vertex - 1);
    cout << FindLengthToLCA(graph, ancestors, lca, first_vertex - 1) +
      FindLengthToLCA(graph, ancestors, lca, second_vertex - 1)<< "\n";
  }
}

int main() {
  vector< vector<EdgeFromVertex> > graph = ReadGraph();
  GetSolution(graph);
}
