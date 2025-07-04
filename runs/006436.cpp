#include <vector>
#include <cstdio>

using std::vector;
using std::pair;
using std::make_pair;
typedef pair<int,int> EdgeTo;
typedef vector< vector<EdgeTo> > Graph;

Graph ReadGraph(int vertice_number) {
  vector< vector<EdgeTo> > reading_graph(vertice_number);
  int from, to, length;
  for(int i = 0; i < vertice_number - 1; ++i) {
    scanf("%i%i%i", &from, &to, &length);
    reading_graph[from - 1].push_back(make_pair(to - 1, length));
    reading_graph[to - 1].push_back(make_pair(from - 1, length));
  }
  return reading_graph;
}
vector< vector< pair<int, int> > > ReadRequests(int request_number, int vertice_number) {
  vector< vector< pair<int, int> > > requests(vertice_number);
  int from, to;
  for(int i = 0; i < request_number; ++i) {
    scanf("%i%i", &from, &to);
    requests[from - 1].push_back(make_pair(to - 1, i));
    requests[to - 1].push_back(make_pair(from - 1, i));
  }
  return requests;
}

int DisjointSetGet(int vertice, const vector<int> &disjoint_set_union) {
  if(vertice == disjoint_set_union[vertice])
    return vertice;
  else
    return DisjointSetGet(disjoint_set_union[vertice], disjoint_set_union);
}
void DisjointSetUnite(int first_element, int second_element, vector<int> *disjoint_set_union,
                      vector<int> *ancestor, vector<int> *rank) {
  int new_ancestor = first_element;
  first_element = DisjointSetGet(first_element, *disjoint_set_union);
  second_element = DisjointSetGet(second_element, *disjoint_set_union);
  if((*rank)[first_element] < (*rank)[second_element]) {
    (*disjoint_set_union)[first_element] = second_element;
    (*ancestor)[second_element] = new_ancestor;
  }
  else {
    (*disjoint_set_union)[second_element] = first_element;
    (*ancestor)[first_element] = new_ancestor;
    if ((*rank)[first_element] == (*rank)[second_element])
      ++(*rank)[first_element];
  } 
}
void DepthSeek(const Graph &tree, int vertices, const vector< vector< pair<int, int> > > &requests,
               int current_vertice, int current_depth, vector<bool> *visited, vector<int> *disjoint_set_union,
               vector<int> *ancestor, vector<int> *depth, vector<int> *request_answers, vector<int> *rank) {
  (*disjoint_set_union)[current_vertice] = current_vertice;
  (*ancestor)[current_vertice] = current_vertice;
  (*visited)[current_vertice] = true;
  (*depth)[current_vertice] = current_depth;
  for(int i = 0; i < requests[current_vertice].size(); ++i) {
    int second_vertice = requests[current_vertice][i].first;
    if((*visited)[second_vertice]) {
      int lca = (*ancestor)[DisjointSetGet(second_vertice, *disjoint_set_union)];
      (*request_answers)[requests[current_vertice][i].second] = (*depth)[current_vertice] + (*depth)[second_vertice] -
                                                                2 * (*depth)[lca];
    }
  }
  
  for(int i = 0; i < tree[current_vertice].size(); ++i) {
    if(!(*visited)[tree[current_vertice][i].first]) {
      DepthSeek(tree, vertices, requests, tree[current_vertice][i].first,
                current_depth + tree[current_vertice][i].second, visited,
                disjoint_set_union, ancestor, depth, request_answers, rank);
      DisjointSetUnite(current_vertice, tree[current_vertice][i].first, disjoint_set_union, ancestor, rank);
    }
  }
}

int main (void)
{
  int vertice_number, request_number;
  scanf("%i", &vertice_number);
  Graph given_graph = ReadGraph(vertice_number);
  scanf("%i", &request_number);
  vector< vector< pair<int, int> > > requests = ReadRequests(request_number, vertice_number);
  
  vector<bool> visited(vertice_number, false);
  vector<int> disjoint_set_union(vertice_number);
  vector<int> ancestor(vertice_number);
  vector<int> depth(vertice_number);
  vector<int> request_answers(request_number);
  vector<int> rank(vertice_number, 0);
  
  DepthSeek(given_graph, vertice_number, requests, 0, 0, &visited, &disjoint_set_union,
            &ancestor, &depth, &request_answers, &rank);
  for(int i = 0; i < request_number; ++i)
    printf("%i\n", request_answers[i]);
  return 0;
}
