#include <cstdio>
#include <climits>
#include <vector>
#include <map>
#include <utility>

using std::vector;
using std::pair;
using std::map;
using std::make_pair;

//"DFS" stands for Depth First Search

typedef map<int, vector<int> > VertexPathsMap;
typedef pair<int, int> VertexPathPair;
typedef map<int, bool> VertexProceededMap;

class CPairHeap
{
  //variables
  vector<VertexPathPair> heap;
  vector<int> vertex_location;  //vertex_location.at(i) stands for location of vertex "i" in heaps

  //private methods
  void FixHeap(int node_index);
  void BuildHeap();
  int Parent(int node_index);
  int LeftChild(int node_index);
  int RightChild(int node_index);

public:
  CPairHeap(const vector<int>& source_vector);
  ~CPairHeap();

  void DecreaseVertexValue(int vertex, int value);
  int ExtractMin();

  bool Empty();
  bool VertexLeft(int vertex);
};

CPairHeap::CPairHeap(const vector<int>& source_vector) {
  int vector_size = static_cast<int>(source_vector.size());
  this->heap.reserve(vector_size);
  this->vertex_location.assign(vector_size, 0);

  for (int heap_index = 0; heap_index < vector_size; ++heap_index) {
    this->heap.push_back(make_pair(heap_index, source_vector.at(heap_index)));
    this->vertex_location.at(heap_index) = heap_index;
  }

  this->BuildHeap();
}

CPairHeap::~CPairHeap() {
  this->heap.clear();
  this->vertex_location.clear();
}

bool CPairHeap::Empty() {
  return this->heap.empty();
}

bool CPairHeap::VertexLeft(int vertex) {
  return (vertex_location.at(vertex) != -1);
}

inline int CPairHeap::Parent(int node_index)
{
	return (node_index - 1) / 2;
}

inline int CPairHeap::LeftChild(int node_index)
{
	return (node_index << 1) + 1;
}

inline int CPairHeap::RightChild(int node_index)
{
	return (node_index << 1) + 2;
}

void CPairHeap::FixHeap(int node_index)
{
  int left_child_index = this->LeftChild(node_index);
  int right_child_index = this->RightChild(node_index);

  int index_of_smallest;

  int heap_size = static_cast<int>(this->heap.size());

  if (left_child_index < heap_size && 
    this->heap.at(left_child_index).second < 
    this->heap.at(node_index).second) {
    index_of_smallest = left_child_index;
  } else {
    index_of_smallest = node_index;
  }

  if (right_child_index < heap_size && 
    this->heap.at(right_child_index).second <
    this->heap.at(index_of_smallest).second) {
    index_of_smallest = right_child_index;
  }

  if (index_of_smallest != node_index) {
    int location_swap = 
      this->vertex_location.at(heap.at(index_of_smallest).first);
    this->vertex_location.at(heap.at(index_of_smallest).first) = 
      this->vertex_location.at(heap.at(node_index).first);
    this->vertex_location.at(heap.at(node_index).first) =
      location_swap;

    VertexPathPair pair_swap = this->heap.at(index_of_smallest);
    this->heap.at(index_of_smallest) = this->heap.at(node_index);
    this->heap.at(node_index) = pair_swap;
    this->FixHeap(index_of_smallest);
  }
}

void CPairHeap::BuildHeap() {
  int heap_size = static_cast<int>(this->heap.size());

  for (int node_index = heap_size / 2; node_index >= 0; --node_index) {
    this->FixHeap(node_index);
  }
}

int CPairHeap::ExtractMin() {
  int min_path_vertex = -1;
  if (!this->heap.empty()) {
    min_path_vertex = this->heap.front().first;
  }

  this->vertex_location.at(this->heap.front().first) = -1;
  this->heap.front() = this->heap.back();
  this->vertex_location.at(this->heap.back().first) = 0;
  this->heap.pop_back();
  this->FixHeap(0);

  return min_path_vertex;
}

void CPairHeap::DecreaseVertexValue(int vertex, int value) {
  int vertex_heap_index = vertex_location.at(vertex);
  int parent_heap_index = Parent(vertex_heap_index);

  if (value < this->heap.at(vertex_heap_index).second) {
    this->heap.at(vertex_heap_index).second = value;

    //fixing heap
    while (vertex_heap_index > 0 && 
           this->heap.at(vertex_heap_index).second < 
           this->heap.at(parent_heap_index).second) {
      int location_swap = 
        this->vertex_location.at(heap.at(parent_heap_index).first);
      this->vertex_location.at(heap.at(parent_heap_index).first) = 
        this->vertex_location.at(heap.at(vertex_heap_index).first);
      this->vertex_location.at(heap.at(vertex_heap_index).first) =
        location_swap;

      VertexPathPair pair_swap = this->heap.at(parent_heap_index);
      this->heap.at(parent_heap_index) = this->heap.at(vertex_heap_index);
      this->heap.at(vertex_heap_index) = pair_swap;

      vertex_heap_index = parent_heap_index;
      parent_heap_index = Parent(vertex_heap_index);
    }
  }
}

//globals for decision of LCA problem
vector<int> vertices_height, DFS_list;
vector<int> vertices_occurence, LCA_tree;
vector<bool> used_in_depth_first_search;

void ReadGraph(vector<vector<pair<int, int> > >* graph) {
  int vertex_count;
  scanf("%d", &vertex_count);
  graph->resize(vertex_count);

  int edge_begin;
  int edge_end;
  int edge_weight;

  for (int edge_index = 0; edge_index < vertex_count - 1; ++edge_index) {
    scanf("%d %d %d", &edge_begin, &edge_end, &edge_weight);
    --edge_begin;
    --edge_end;
    graph->at(edge_begin).push_back(std::make_pair(edge_end, edge_weight));
    graph->at(edge_end).push_back(std::make_pair(edge_begin, edge_weight));
  }
}

void ReadRequests(vector<pair<int, int> >* requests) {
  int request_count;
  scanf("%d", &request_count);
  requests->reserve(request_count);

  int path_begin;
  int path_end;

  for (int request_index = 0; request_index < request_count; ++request_index) {
    scanf("%d %d", &path_begin, &path_end);
    --path_begin;
    --path_end;
    requests->push_back(std::make_pair(path_begin, path_end));
  }
}

int ChooseRoot(const vector<vector<pair<int, int> > >& graph) {
  int max_edges = -1;
  int root_vertex = -1;
  int vertex_count = static_cast<int>(graph.size());

  for (int vertex_index = 0; vertex_index < vertex_count; ++vertex_index) {
    int vertex_edges = static_cast<int>(graph.at(vertex_index).size());
    if (vertex_edges > max_edges) {
      root_vertex = vertex_index;
      max_edges = vertex_edges;
    }
  }

  return root_vertex;
}

void RunDFSForLCA(const vector<vector<pair<int, int> > >& graph, 
                  int vertex, 
                  int height = 1) {
  DFS_list.push_back(vertex);
  used_in_depth_first_search[vertex] = true;
  vertices_height[vertex] = height;

  int edges_count = static_cast<int>(graph.at(vertex).size());

  for (int edge_index = 0; edge_index < edges_count; ++edge_index) {
    int edge_end = graph.at(vertex).at(edge_index).first;
    if (!used_in_depth_first_search.at(edge_end)) {
      RunDFSForLCA(graph, edge_end, height + 1);
      DFS_list.push_back(vertex);
    }
  }
}

void BuildLCATree(int tree_element, int list_left_bound, int list_right_bound)
{
  if (list_left_bound == list_right_bound) {
    LCA_tree[tree_element] = DFS_list[list_left_bound];
  } else {
    int middle = (list_left_bound + list_right_bound) >> 1;
    BuildLCATree(tree_element << 1, list_left_bound, middle);
    BuildLCATree(tree_element << 1 | 1, middle + 1, list_right_bound);

    if (vertices_height.at(LCA_tree.at(tree_element << 1)) < 
        vertices_height.at(LCA_tree.at(tree_element << 1 | 1))) {
      LCA_tree.at(tree_element) = LCA_tree.at(tree_element << 1);
    } else {
      LCA_tree.at(tree_element) = LCA_tree.at(tree_element << 1 | 1);
    }
  }
}

void PrepareForLCA(const vector<vector<pair<int, int> > >& graph, int root) {
  int graph_size = static_cast<int>(graph.size());

  vertices_height.resize(graph_size);
  DFS_list.reserve(2 * graph_size);
  used_in_depth_first_search.assign(graph_size, false);

  RunDFSForLCA(graph, root);

  int DFS_list_size = static_cast<int>(DFS_list.size());
  vertices_occurence.assign(graph_size, -1);
  for (int element_index = 0; element_index < DFS_list_size; ++element_index) {
    int vertex = DFS_list.at(element_index);
    if (vertices_occurence[vertex] == -1) {
      vertices_occurence[vertex] = element_index;
    }
  }

  LCA_tree.assign(DFS_list_size * 4 + 1, -1);
  BuildLCATree(1, 0, DFS_list_size - 1);
}

int GetLCAFromTree(int tree_vertex, 
                   int vertex_range_left_bound, 
                   int vertex_range_right_bound, 
                   int list_left_bound, 
                   int list_right_bound) {
  if (vertex_range_left_bound == list_left_bound && 
      vertex_range_right_bound == list_right_bound) {
    return LCA_tree[tree_vertex];
  }

  int vertex_range_middle = 
    (vertex_range_left_bound + vertex_range_right_bound) >> 1;

  if (list_right_bound <= vertex_range_middle) {
    return GetLCAFromTree(tree_vertex << 1, vertex_range_left_bound, 
      vertex_range_middle, list_left_bound, list_right_bound);
  }
  if (list_left_bound > vertex_range_middle) {
    return GetLCAFromTree(tree_vertex << 1 | 1, vertex_range_middle + 1,
      vertex_range_right_bound, list_left_bound, list_right_bound);
  }
  int left_subtree_answer = 
    GetLCAFromTree(tree_vertex << 1, vertex_range_left_bound, 
      vertex_range_middle, list_left_bound, vertex_range_middle);
  int right_subtree_answer = 
    GetLCAFromTree(tree_vertex << 1 | 1, vertex_range_middle + 1, 
      vertex_range_right_bound, vertex_range_middle + 1, list_right_bound);

  return vertices_height[left_subtree_answer] < 
         vertices_height[right_subtree_answer] ? 
         left_subtree_answer : right_subtree_answer;
}

int GetLCA(int first_vertex, int second_vertex) {
  int left_bound = vertices_occurence[first_vertex];
  int right_bound = vertices_occurence[second_vertex];

  int DFS_list_size = static_cast<int>(DFS_list.size());

  if (left_bound > right_bound) {
    int swap_int = left_bound;
    left_bound = right_bound;
    right_bound = swap_int;
  }

  return GetLCAFromTree(1, 0, DFS_list_size - 1, left_bound, right_bound);
}

void GetVerticesForDijkstra(const vector<vector<pair<int, int> > >& graph,
                            const vector<pair<int, int> >& requests,
                            vector<int>* output_vertices) {
  int graph_root = ChooseRoot(graph);
  PrepareForLCA(graph, graph_root);

  int request_count = static_cast<int>(requests.size());

  for (int request_index = 0; request_index < request_count; ++request_index) {
    int vertices_LCA = GetLCA(requests.at(request_index).first, 
                              requests.at(request_index).second);
    output_vertices->push_back(vertices_LCA);
  }
}

void RunDijkstra(const vector<vector<pair<int, int> > >& graph, 
                 const vector<pair<int, int> >& requests,
                 const vector<int>& Dijkstra_start_vertices,
                 vector<int>* answers) {
  VertexPathsMap paths_from_sources;
  VertexProceededMap run_Dijkstra;

  int vertex_count = static_cast<int>(graph.size());

  int request_count = static_cast<int>(requests.size());
  answers->assign(request_count, 0);

  for (int request_index = 0; request_index < request_count; ++request_index) {
    int start_vertex = Dijkstra_start_vertices.at(request_index);
    paths_from_sources[start_vertex].assign(vertex_count, INT_MAX);
    run_Dijkstra[start_vertex] = false;
  }

  for (int request_index = 0; request_index < request_count; ++request_index) {
    int start_vertex = Dijkstra_start_vertices.at(request_index);

    if (!run_Dijkstra[start_vertex]) {

      CPairHeap not_attended_vertices(paths_from_sources[start_vertex]);
      not_attended_vertices.DecreaseVertexValue(start_vertex, 0);
      paths_from_sources[start_vertex].at(start_vertex) = 0;
      int current_vertex;

      while (!not_attended_vertices.Empty()) {
        current_vertex = not_attended_vertices.ExtractMin();
        int current_vertex_path = 
          paths_from_sources[start_vertex].at(current_vertex);
        int neighbour_count = 
          static_cast<int>(graph.at(current_vertex).size());

        //processing neighbours
        for (int neighbour_index = 0;
             neighbour_index < neighbour_count;
             ++neighbour_index) {
          int neighbour_vertex = 
            graph.at(current_vertex).at(neighbour_index).first;
          if (not_attended_vertices.VertexLeft(neighbour_vertex)) {
            int neighbour_weight = 
              graph.at(current_vertex).at(neighbour_index).second;
            int path_via_current = current_vertex_path + neighbour_weight;

            if (paths_from_sources[start_vertex].at(neighbour_vertex) > 
                path_via_current) {
              paths_from_sources[start_vertex].at(neighbour_vertex) = 
                path_via_current;
              not_attended_vertices.DecreaseVertexValue(
                neighbour_vertex, path_via_current);
            }
          }
        }
      }

      VertexPathsMap::iterator paths_iterator;

      for (paths_iterator = paths_from_sources.begin(); 
           paths_iterator != paths_from_sources.end();
           ++paths_iterator) {
        int current_Dijkstra_vertex = paths_iterator->first;
        if (current_Dijkstra_vertex != start_vertex) {
          paths_from_sources[current_Dijkstra_vertex].at(start_vertex) = 
            paths_from_sources[start_vertex].at(current_Dijkstra_vertex);
        }
      }

      run_Dijkstra[start_vertex] = true;
    }

    int request_answer = 
      paths_from_sources[start_vertex].at(requests.at(request_index).first) + 
      paths_from_sources[start_vertex].at(requests.at(request_index).second);
    answers->at(request_index) = request_answer;
  }
}

void PrintAnswers(const vector<int>& answers) {
  int answers_count = static_cast<int>(answers.size());

  for (int answer_index = 0; answer_index < answers_count; ++answer_index) {
    printf("%d\n", answers.at(answer_index));
  }
}

int main() {
  vector<vector<pair<int, int> > > graph;
  ReadGraph(&graph);

  vector<pair<int, int> > requests;
  ReadRequests(&requests);

  vector<int> vertices_for_Dijkstra;
  GetVerticesForDijkstra(graph, requests, &vertices_for_Dijkstra);

  vector<int> answers(vertices_for_Dijkstra.size());
  RunDijkstra(graph, requests, vertices_for_Dijkstra, &answers);

  PrintAnswers(answers);

  return 0;
}