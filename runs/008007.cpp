#include <iostream>
#include <vector>

using std::vector;

struct node {
  size_t parent_id;
  size_t depth;
  size_t distance_to_parent;
  node() {
    parent_id = 0;
    depth = 0;
    distance_to_parent = 0;
  }
};

void input_tree(vector < node >* tree) {
  size_t node_count;
  std::cin >> node_count;
  tree->resize(node_count + 1);
  for (size_t node_index = 0; node_index + 1 < node_count; ++node_index) {
    size_t outgoing_node_id;
    std::cin >> outgoing_node_id;
    size_t incoming_node_id;
    std::cin >> incoming_node_id;
    size_t edge_length;
    std::cin >> edge_length;
    
    tree->at(incoming_node_id + 1).distance_to_parent = edge_length;

    tree->at(incoming_node_id + 1).parent_id = outgoing_node_id + 1;
    tree->at(incoming_node_id + 1).depth = tree->at(outgoing_node_id + 1).depth + 1;
  }
}

void input_bounds(vector < vector < size_t > >* bounds) {
  size_t bounds_count;
  std::cin >> bounds_count;
  bounds->resize(bounds_count);
  for (size_t bound_index = 0; bound_index < bounds_count; ++bound_index) {
    bounds->at(bound_index).resize(2);
    size_t left_bound, right_bound;
    std::cin >> left_bound;
    bounds->at(bound_index)[0] = left_bound + 1;
    std::cin >> right_bound;
    bounds->at(bound_index)[1] = right_bound + 1;
  }
}

size_t find_distance(const vector < node >& tree, 
                     size_t left_node_index, 
                     size_t right_node_index) {
  size_t left_depth = tree[left_node_index].depth;
  size_t right_depth = tree[right_node_index].depth;
  size_t left_ancestor_index = left_node_index;
  size_t right_ancestor_index = right_node_index;

  size_t distance = 0;

  while (left_depth != right_depth) {
    if (left_depth > right_depth) {
      distance += tree[left_ancestor_index].distance_to_parent;
      left_ancestor_index = tree[left_ancestor_index].parent_id;
      left_depth -= 1;
    } else {
      distance += tree[right_ancestor_index].distance_to_parent;
      right_ancestor_index = tree[right_ancestor_index].parent_id;
      right_depth -= 1;
    }
  }

  while (left_ancestor_index != right_ancestor_index) {
    distance += tree[left_ancestor_index].distance_to_parent + 
                tree[right_ancestor_index].distance_to_parent;
    left_ancestor_index = tree[left_ancestor_index].parent_id;
    right_ancestor_index = tree[right_ancestor_index].parent_id;
  }

  return distance;
}

void print_answer(const vector < node >& tree, const vector < vector < size_t > >& bounds) {
  for (size_t bound_index = 0; bound_index < bounds.size(); ++bound_index) {
    std::cout << find_distance(tree, bounds[bound_index][0], bounds[bound_index][1]) << std::endl;
  }
}

int main() {
  vector < node > tree;
  input_tree(&tree);
  vector < vector < size_t > > bnd;
  input_bounds(&bnd);
  print_answer(tree, bnd);
}