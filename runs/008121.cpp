#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct graph_node {
  size_t outgoing;
  size_t edge_weight;
  graph_node(): outgoing(0), edge_weight(0){}

  graph_node(size_t outgoing, size_t distance): outgoing(outgoing), edge_weight(distance) {}
};

struct tree_node {
  unsigned long long distance_to_root;
  vector < size_t > children;
  size_t ancestor;
  size_t parent;
  size_t colour;
  tree_node(): distance_to_root(0), 
               children(vector < size_t>::vector()),
               ancestor(0),
               parent(0),
               colour(0) {
  }
};

typedef vector < vector < graph_node > > graph;
typedef vector < tree_node > oriented_tree;

void MakeSet(oriented_tree* tree, size_t node_id) {
  tree->at(node_id).parent = node_id;
}

size_t Find(oriented_tree* tree, size_t node_id) {
  if (tree->at(node_id).parent == node_id) {
    return node_id;
  } else {
    tree->at(node_id).parent = Find(tree, tree->at(node_id).parent);
    return tree->at(node_id).parent;
  }
}

void Union(oriented_tree* tree, size_t left, size_t right, size_t new_ancestor) {
  size_t left_root = Find(tree, left);
  size_t right_root = Find(tree, right);
  std::srand(1723);
  if (std::rand() % 2 == 0) {
    std::swap(left_root, right_root);
  }
  tree->at(right_root).parent = left_root;
  tree->at(left_root).ancestor = new_ancestor;
}

void add_edge(const vector < size_t >& edge_values, graph* graph) {
  graph->at(edge_values[0]).push_back(graph_node(edge_values[1], edge_values[2]));
  graph->at(edge_values[1]).push_back(graph_node(edge_values[0], edge_values[2]));
}

void make_oriented_tree(const graph& Graph, 
                        size_t root_id, 
                        vector < size_t >* explored,
                        oriented_tree* tree) {
  explored->at(root_id) = 1;
  for (vector < graph_node >::const_iterator iter = Graph.at(root_id).begin(); 
       iter != Graph.at(root_id).end();
       ++iter) {
    if (explored->at(iter->outgoing) != 1) {
      unsigned long long parent_distance = tree->at(root_id).distance_to_root;
      tree->at(iter->outgoing).distance_to_root = parent_distance + iter->edge_weight;
      tree->at(root_id).children.push_back(iter->outgoing);
      make_oriented_tree(Graph, iter->outgoing, explored, tree);
    }
  }
}

size_t input_graph(graph* Graph) {
  size_t edges_count;
  std::cin >> edges_count;
  Graph->resize(edges_count + 1);
  vector < size_t > edge_values;
  edge_values.resize(3);
  size_t root_id = 0;
  for (size_t edge_index = 0; edge_index + 1 < edges_count; ++edge_index) {
    std::cin >> edge_values[0] >> edge_values[1] >> edge_values[2];
    if(edge_index == 0) {
      root_id = edge_values[0];
    }
    add_edge(edge_values, Graph);
  }
  return root_id;
}

void input_bounds(vector < vector < size_t > >* bounds) {
  size_t bounds_count;
  std::cin >> bounds_count;
  bounds->resize(bounds_count);
  for (size_t bound_index = 0; bound_index < bounds_count; ++bound_index) {
    bounds->at(bound_index).resize(2);
    std::cin >> bounds->at(bound_index)[0];
    std::cin >> bounds->at(bound_index)[1];
  }
}

void find_distances(size_t root_id, 
                    const vector < vector < size_t > >& bounds, 
                    vector < tree_node >* tree,
                    vector < unsigned long long >* distances) {
  MakeSet(tree, root_id);
  tree->at(root_id).ancestor = root_id;
  tree->at(root_id).colour = 1;
  for (size_t child_index = 0; child_index < tree->at(root_id).children.size(); ++child_index) {
    find_distances(tree->at(root_id).children[child_index], bounds, tree, distances);
    Union(tree, root_id, tree->at(root_id).children[child_index], root_id);
  }
  vector < size_t > root_bounds;
  for (size_t bound_index = 0; bound_index < bounds.size(); ++bound_index) {
    if (bounds[bound_index][0] == root_id) {
      root_bounds.push_back(bound_index);
    }
  }
  for (size_t bound_index = 0; bound_index < root_bounds.size(); ++bound_index) {
    if (tree->at(bounds[root_bounds[bound_index]][0]).colour = 1) {
      size_t ancestor = tree->at(Find(tree, bounds[root_bounds[bound_index]][1])).ancestor;
      distances->at(root_bounds[bound_index]) = tree->at(root_id).distance_to_root + 
                                                tree->at(bounds[root_bounds[bound_index]][1]).distance_to_root - 
                                                2 * tree->at(ancestor).distance_to_root;
    }
  }
}

void print (const vector < unsigned long long >& distances) {
  for (size_t distance_index = 0; distance_index < distances.size(); ++distance_index) {
    std::cout << distances[distance_index] << std::endl;
  }
}

int main() {
  graph Graph;
  size_t root_id = 0;
  root_id = input_graph(&Graph);
  vector < vector < size_t > > bounds;
  input_bounds(&bounds);
  oriented_tree tree(Graph.size());
  vector < size_t > explored(Graph.size(), 0);
  explored[0] = 1;
  make_oriented_tree(Graph, root_id, &explored, &tree);
  vector < unsigned long long > distances;
  distances.resize(bounds.size(), 0);
  tree.at(0).colour = 1;
  find_distances(root_id, bounds, &tree, &distances);
  print(distances);
  return 0;
}
