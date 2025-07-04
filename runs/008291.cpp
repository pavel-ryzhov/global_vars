#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct graph_node {
  size_t outgoing;
  size_t distance;
  graph_node(size_t outgoing_id, size_t distance): outgoing(outgoing_id), 
                                                   distance(distance) {}
};

typedef vector < vector < graph_node > > graph;

void input_graph(graph* Graph) {
  size_t node_count = 0;
  std::cin >> node_count;
  Graph->resize(node_count + 1);
  for (size_t edge_index = 0; edge_index + 1 < node_count; ++edge_index) {
    size_t incoming = 0, outgoing = 0, distance = 0;
    std::cin >> incoming >> outgoing >> distance;
    Graph->at(incoming).push_back(graph_node(outgoing, distance));
    Graph->at(outgoing).push_back(graph_node(incoming, distance));
  }
}

void find_Eulerian_path(size_t root_id,
                        vector < size_t >* explored,
                        const graph& Graph,
                        vector < size_t >* distances,
                        vector < size_t >* eulerian_path,
                        vector < size_t >* new_indexes) {
  explored->at(root_id) = 1;
  eulerian_path->push_back(distances->at(root_id));
  new_indexes->at(root_id) = eulerian_path->size() - 1;
  for (vector < graph_node >::const_iterator iter = Graph.at(root_id).begin();
       iter != Graph.at(root_id).end();
       ++iter) {
    if (explored->at(iter->outgoing) != 1) {
      size_t parent_distance = distances->at(root_id);
      distances->at(iter->outgoing) = parent_distance + iter->distance;
      find_Eulerian_path(iter->outgoing, explored, Graph, distances, eulerian_path, new_indexes);
      distances->at(root_id) = parent_distance;
      eulerian_path->push_back(distances->at(root_id));
      new_indexes->at(root_id) = eulerian_path->size() - 1;
    }
  }
}

void build_segment_tree(const vector < size_t >& bypass_order, 
                        size_t root_id,
                        size_t left_bound,
                        size_t right_bound,
                        vector < size_t >* segment_tree) {
  if (segment_tree->size() != 4 * bypass_order.size()) {
    segment_tree->resize(4 * bypass_order.size());
  }
  if (left_bound == right_bound) {
    segment_tree->at(root_id) = bypass_order[left_bound];
  } else {
    size_t middle = (left_bound + right_bound) / 2;
    build_segment_tree(bypass_order, root_id * 2, left_bound, middle, segment_tree);
    build_segment_tree(bypass_order, root_id * 2 + 1, middle + 1, right_bound, segment_tree);
    segment_tree->at(root_id) = std::min(segment_tree->at(root_id * 2), segment_tree->at(root_id * 2 + 1));
  }
}

size_t RMQ (size_t root_id, 
            size_t left_bound, 
            size_t right_bound, 
            size_t request_left, 
            size_t request_right,
            const vector < size_t >& segment_tree) {
  if (request_left > request_right) {
    return (size_t)(-1);
  }
  if (request_left == left_bound && request_right == right_bound) {
    return segment_tree[root_id];
  }
  size_t middle = (left_bound + right_bound) / 2;
  return std::min(RMQ(root_id * 2, 
                      left_bound, 
                      middle, 
                      request_left, 
                      std::min(request_right, middle), 
                      segment_tree),
                  
                  RMQ(root_id * 2 + 1, 
                      middle + 1, 
                      right_bound, 
                      std::max(request_left, middle + 1), 
                      request_right, 
                      segment_tree));
}

void input_requests(vector < vector < size_t > >* requests) {
  size_t requests_count;
  std::cin >> requests_count;
  requests->resize(requests_count);
  for (size_t request_index = 0; request_index < requests_count; ++request_index) {
    requests->at(request_index).resize(2);
    std::cin >> requests->at(request_index)[0];
    std::cin >> requests->at(request_index)[1];
  }
}

void get_answers(const graph& Graph,
                 const vector < vector < size_t > > requests,
                 vector < size_t >* answers) {
  answers->resize(requests.size());
  vector < size_t > explored(Graph.size());
  vector < size_t > distances(Graph.size());
  vector < size_t > eulerian_path;
  eulerian_path.reserve(Graph.size() * 2 - 1);
  vector < size_t > new_indexes(Graph.size());
  find_Eulerian_path(1, &explored, Graph, &distances, &eulerian_path, &new_indexes);
  vector < size_t > segment_tree;
  build_segment_tree(eulerian_path, 1, 0, eulerian_path.size() - 1, &segment_tree);
  for (size_t request_index = 0; request_index < requests.size(); ++request_index) {
    size_t left_node_index = new_indexes.at(requests.at(request_index)[0]);
    size_t right_node_index = new_indexes.at(requests.at(request_index)[1]);
    if (left_node_index > right_node_index) {
      std::swap(left_node_index, right_node_index);
    }
    size_t lca_distance = RMQ(1, 0, eulerian_path.size() - 1, left_node_index, right_node_index, segment_tree);
    answers->at(request_index) = distances.at(requests[request_index][0]) + distances.at(requests[request_index][1]) - 2 * lca_distance;
  }
}

void print (const vector < size_t >& distances) {
  for (size_t distance_index = 0; distance_index < distances.size(); ++distance_index) {
    std::cout << distances[distance_index] << std::endl;
  }
}

int main() {
  graph Graph;
  input_graph(&Graph);
  vector < vector < size_t > > requests;
  input_requests(&requests);
  vector < size_t > answers;
  get_answers(Graph, requests, &answers);
  print(answers);
  return 0;
}
