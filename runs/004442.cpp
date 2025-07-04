#include <cstdio>
#include <vector>
#include <utility>
#include <cmath>
#include <cstdlib>

using std::vector;
using std::swap;

const int MAXLENGTH = 40000;

struct EulerTourElement {
  int height;
  int node;
};

struct SegmentWithMin {
  int left_end;
  int right_end;
  EulerTourElement euler_tour_element;
};

class SegmentTree {
private:
  vector< SegmentWithMin > segments;
  EulerTourElement segment_min;
  void MakeSegments(int left_end, int right_end, int position, const vector< EulerTourElement >& euler_tour);
  EulerTourElement FindMin(int left_end, int right_end, const vector< EulerTourElement >& euler_tour);
  void Decompose(int left_index, int right_index, int position);
public:
  void MakeTree(const vector< EulerTourElement >& euler_tour);
  int FindSegmentMin(int left_index, int right_index);
};

void SegmentTree::MakeTree(const vector< EulerTourElement >& euler_tour) {
  int left_end = 0;
  int right_end = (int)euler_tour.size() - 1;
  segments.resize((int)euler_tour.size() * 4);
  MakeSegments(left_end, right_end, 0, euler_tour);
}

EulerTourElement SegmentTree::FindMin(int left_end, int right_end, const vector< EulerTourElement >& euler_tour) {
  EulerTourElement new_element = euler_tour[left_end];
  for (int index = left_end + 1; index <= right_end; ++index) {
    if (euler_tour[index].height < new_element.height) {
      new_element = euler_tour[index];
    }
  }
  return new_element;
}

void SegmentTree::MakeSegments(int left_end, int right_end, int position, const vector< EulerTourElement >& euler_tour) {
  SegmentWithMin new_segment;
  new_segment.left_end = left_end;
  new_segment.right_end = right_end;
  if (left_end == right_end) {
    new_segment.euler_tour_element = euler_tour[left_end];
  }
  else {
    new_segment.euler_tour_element = FindMin(left_end, right_end, euler_tour);
  }
  segments[position] = new_segment;
  if (left_end == right_end) {
    return;
  }
  int middle_end = (left_end + right_end) / 2;
  MakeSegments(left_end, middle_end, 2 * (position + 1) - 1, euler_tour);
  MakeSegments(middle_end + 1, right_end, 2 * (position + 1), euler_tour);
}

int SegmentTree::FindSegmentMin(int left_index, int right_index) {
  segment_min.height = MAXLENGTH;
  Decompose(left_index, right_index, 0);
  return segment_min.node;
}

void SegmentTree::Decompose(int left_index, int right_index, int position) {
  if ((segments[position].left_end == segments[position].right_end) ||
  ((left_index == segments[position].left_end) && (right_index == segments[position].right_end))) {
    if (segments[position].euler_tour_element.height < segment_min.height) {
      segment_min = segments[position].euler_tour_element;
    }
    else {
      return;
    }
  }
  else {
    int middle_index = (segments[position].left_end + segments[position].right_end) / 2;
    if (middle_index >= left_index) {
      if (middle_index > right_index) {
        middle_index = right_index;
      }
      Decompose(left_index, middle_index, 2 * (position + 1) - 1);
    }
    if (middle_index + 1 <= right_index) {
      if (middle_index + 1 < left_index) {
        middle_index = left_index - 1;
      }
      Decompose(middle_index + 1, right_index, 2 * (position + 1));
    }
  }
}

struct Edge {
  int next_node;
  int edge_length;
};

struct Node {
  Edge parent;
  vector< Edge > children;
  int euler_tour_place;
  int distance_to_root;
  int height;
};

class Tree {
private:
  vector< Node > nodes;
  vector< EulerTourElement > euler_tour;
  SegmentTree segment_tree;
  void MakeTour(int node_index);
public:
  explicit Tree(int tree_size);
  void Insert(int first_node, int second_node, int edge_length);
  void MakeEulerTour();
  int FindShortestPath(int first_node, int second_node);
};

Tree::Tree(int tree_size) {
  nodes.resize(tree_size);
  nodes[0].parent.next_node = -1;
  nodes[0].parent.edge_length = 0;
  nodes[0].distance_to_root = 0;
  nodes[0].height = 0;
  for (int index = 0; index < tree_size; ++index) {
    nodes[index].euler_tour_place = 0;
  }
}

int Tree::FindShortestPath(int first_node, int second_node) {
  int lca;
  if (nodes[first_node].euler_tour_place <= nodes[second_node].euler_tour_place) {
    lca = segment_tree.FindSegmentMin(nodes[first_node].euler_tour_place, nodes[second_node].euler_tour_place);
  }
  else {
    lca = segment_tree.FindSegmentMin(nodes[second_node].euler_tour_place, nodes[first_node].euler_tour_place);
  }

  return nodes[first_node].distance_to_root + nodes[second_node].distance_to_root -
    2 * nodes[lca].distance_to_root;
}

void Tree::Insert(int first_node, int second_node, int edge_length) {
  Edge new_edge;
  new_edge.next_node = second_node;
  new_edge.edge_length = edge_length;
  nodes[first_node].children.push_back(new_edge);
  new_edge.next_node = first_node;
  nodes[second_node].parent = new_edge;
  nodes[first_node].distance_to_root = 0;
  nodes[second_node].distance_to_root = 0;
}

void Tree::MakeTour(int node_index) {
  EulerTourElement new_element;
  new_element.node = node_index;
  new_element.height = nodes[node_index].height;

  euler_tour.push_back(new_element);
  if ((nodes[node_index].euler_tour_place == 0) && (node_index != 0)) {
    nodes[node_index].euler_tour_place = (int) euler_tour.size() - 1;
  }
  if ((int) nodes[node_index].children.size() != 0) {
    for (int index = 0; index < (int) nodes[node_index].children.size(); ++index) {
      nodes[nodes[node_index].children[index].next_node].height = 
        nodes[node_index].height + 1;
        nodes[nodes[node_index].children[index].next_node].distance_to_root = 
          nodes[node_index].distance_to_root + nodes[node_index].children[index].edge_length;
        MakeTour(nodes[node_index].children[index].next_node);
    }
  }
  if (node_index != 0) {
    new_element.height = nodes[nodes[node_index].parent.next_node].height;
    new_element.node = nodes[node_index].parent.next_node;
    euler_tour.push_back(new_element);
  }
}

void Tree::MakeEulerTour() {
  MakeTour(0);
  segment_tree.MakeTree(euler_tour);
}

void CheckSons(Tree& tree, int node, vector< vector< Edge > >& edges, vector< bool >& labels) {
  for (int index = 0; index < (int)edges[node].size(); ++index) {
     if (!labels[edges[node][index].next_node]) {
       tree.Insert(node, edges[node][index].next_node, edges[node][index].edge_length);
       labels[edges[node][index].next_node] = true;
       CheckSons(tree, edges[node][index].next_node, edges, labels);
     }
  }
}


void Input(Tree& tree, int tree_size) {
  
  vector< vector< Edge > > edges;
  edges.resize(tree_size);
  Edge edge;
  for (int index = 0; index < tree_size - 1; ++index) {
    int first_node;
    int second_node;
    int edge_length;

    scanf("%d%d%d", &first_node, &second_node, &edge_length);
    edge.edge_length = edge_length;
    edge.next_node = second_node - 1;
    edges[first_node - 1].push_back(edge);
    edge.next_node = first_node - 1;
    edges[second_node - 1].push_back(edge);
  }

  int counter = 0;
  int row = 0;
  vector< bool > labels;
  labels.assign(tree_size, false);
  labels[0] = true;
  CheckSons(tree, 0, edges, labels);
}

void Input(int& number_of_egdes, vector< int >& first_nodes, vector< int >& second_nodes) {
  scanf("%d", &number_of_egdes);
  int first_node;
  int second_node;
  for (int index = 0; index < number_of_egdes; ++index) {
    scanf("%d%d", &first_node, &second_node);
    first_nodes.push_back(first_node - 1);
    second_nodes.push_back(second_node - 1);
  }
}

int main() {
  int tree_size;
  scanf("%d", &tree_size);
  Tree tree(tree_size);
  Input(tree, tree_size);

  int number_of_edges; 
  vector< int > first_nodes;
  vector< int > second_nodes;
  Input(number_of_edges, first_nodes, second_nodes);

  tree.MakeEulerTour();
  for (int index = 0; index < number_of_edges; ++index) {
    printf("%d\n", tree.FindShortestPath(first_nodes[index], second_nodes[index]));
  }


  return 0;
}
  