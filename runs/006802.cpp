#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

const int INFINITE_VERTEX = 2000000000;
const int INFINITE_WEIGHT = 2000000000;

struct Edge {
    int source;
    int destination;
    int weight;

    Edge(int edge_source, int edge_destination, int edge_weight):
        source(edge_source),
        destination(edge_destination),
        weight(edge_weight) {
    }

    bool operator< (const Edge& edge) const {
        return source < edge.source;
    }
};

typedef std::pair<int, int> VertexesPair;

void InputData(int& vertex_count, vector<Edge>& tree, vector<VertexesPair>& queries) {
    std::cin >> vertex_count;
    for (int index = 0; index + 1< vertex_count; ++index) {
        int source, destination, weight;
        std::cin >> source >> destination >> weight;
        --source;
        --destination;
        tree.push_back(Edge(source, destination, weight));
        tree.push_back(Edge(destination, source, weight));
    }
    int queries_count;
    std::cin >> queries_count;
    for (int index = 0; index < queries_count; ++index) {
        int first_vertex, second_vertex;
        std::cin >> first_vertex >> second_vertex;
        --first_vertex;
        --second_vertex;
        queries.push_back(std::make_pair(first_vertex, second_vertex));
    }
    return;
}

void TreeTraverse(
    const vector<Edge>& tree,
    vector<bool>& visited,
    const int vertex_index,
    vector<int>& traverse_trace_depth,
    const int depth,
    vector<int>& vertex_index_in_trace) {

    visited[vertex_index] = true;
    traverse_trace_depth.push_back(depth);
    vertex_index_in_trace[vertex_index] = traverse_trace_depth.size() - 1;

    vector<Edge>::const_iterator tree_iterator = 
        std::lower_bound(tree.begin(), tree.end(), 
                         Edge(vertex_index, INFINITE_VERTEX, INFINITE_WEIGHT));
    while (tree_iterator != tree.end() && tree_iterator->source == vertex_index) {
        if (!visited[tree_iterator->destination]) {
            TreeTraverse(tree, visited, tree_iterator->destination, traverse_trace_depth,
                         depth + tree_iterator->weight, vertex_index_in_trace);
            traverse_trace_depth.push_back(depth);
        }
        ++tree_iterator;
    }
}

void BuildRMQ(
    const vector<int>& data,
    vector<int>& rmq_tree,
    const int index,
    const int left_index,
    const int right_index) {

    if (left_index == right_index) {
        rmq_tree[index] = data[left_index];
        return;
    }

    const int middle_index = (left_index + right_index) / 2;
    BuildRMQ(data, rmq_tree, 2 * index, left_index, middle_index);
    BuildRMQ(data, rmq_tree, 2 * index + 1, middle_index + 1, right_index);
    rmq_tree[index] = std::min(rmq_tree[2 * index], rmq_tree[2 * index + 1]);
    return;
}

int GetRMQRangeMinimum(
    const vector<int>& rmq_tree,
    const int range_left,
    const int range_right,
    const int index,
    const int left_index,
    const int right_index) {

    if (range_left == left_index && range_right == right_index) {
        return rmq_tree[index];
    }
    const int middle_index = (left_index + right_index) / 2;
    if (range_left <= middle_index && middle_index < range_right) {
        const int left_minimum = 
            GetRMQRangeMinimum(rmq_tree, range_left, middle_index,
                               2 * index, left_index, middle_index);
        const int right_minimum =
            GetRMQRangeMinimum(rmq_tree, middle_index + 1, range_right, 
                               2 * index + 1, middle_index + 1, right_index);
        return std::min(left_minimum, right_minimum);
    }
    else if (range_left <= middle_index) {
        return GetRMQRangeMinimum(rmq_tree, range_left, range_right,
                                  2 * index, left_index, middle_index);
    }
    else {
        return GetRMQRangeMinimum(rmq_tree, range_left, range_right,
                                  2 * index + 1, middle_index + 1, right_index);
    }
}

vector<int> GetQueriesAnser(int vertex_count, vector<Edge>& tree, const vector<VertexesPair>& queries) {
    vector<int> queries_anser(queries.size());
    std::sort(tree.begin(), tree.end());

    vector<bool> visited(vertex_count, false);
    vector<int> traverse_trace_depth;
    vector<int> vertex_index_in_trace(vertex_count);
    TreeTraverse(tree, visited, 0, traverse_trace_depth, 0, vertex_index_in_trace);

    vector<int> rmq_tree(traverse_trace_depth.size() * 4);
    const int rmq_last_index = traverse_trace_depth.size() - 1;
    BuildRMQ(traverse_trace_depth, rmq_tree, 1, 0, rmq_last_index);

    for (int index = 0; index < queries.size(); ++index) {
        int first_index = vertex_index_in_trace[queries[index].first];
        int second_index = vertex_index_in_trace[queries[index].second];
        if (first_index > second_index) {
            std::swap(first_index, second_index);
        }
        const int LCA_depth = GetRMQRangeMinimum(rmq_tree, first_index, second_index, 1, 0, rmq_last_index);
        queries_anser[index] = 
            (traverse_trace_depth[first_index] - LCA_depth) + (traverse_trace_depth[second_index] - LCA_depth);
            
    }

    return queries_anser;
}

void OutputQueriesAnser(const vector<int>& queries_anser) {
    for (int index = 0; index < queries_anser.size(); ++index) {
        std::cout << queries_anser[index] << std::endl;
    }
}

int main() {
    int vertex_count;
    vector<Edge> tree; 
    vector<VertexesPair> queries;
    InputData(vertex_count, tree, queries);
    vector<int> queries_anser = 
        GetQueriesAnser(vertex_count, tree, queries);
    OutputQueriesAnser(queries_anser);
    return 0;
}