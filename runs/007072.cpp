#include <iostream>
#include <vector>
#include <utility>

using std::cout;
using std::cin;
using std::vector;
using std::pair;
using std::make_pair;
using std::swap;

const int ROOT = 0;
const int NODE_IS_NOT_EXIST = -1;

enum COLOR {
    WHITE = 0,
    BLACK = 1
};

struct Edge {
    int weight;
    int head;
};

struct Graph {
    vector< vector<Edge> > adjacency_list;
};

void Input(Graph* graph, 
           vector< pair<int, int> >* queries) {   
    int number_node;
    cin >> number_node;
    graph->adjacency_list.resize(number_node);
    int number_edge = number_node - 1;
    for (int edge_index = 0; edge_index < number_edge; ++edge_index) {
        int tail;
        int head;
        int weight;
        cin >> tail >> head >> weight;
        --tail;
        --head;
        Edge edge;
        edge.weight = weight;
        edge.head = head;
        graph->adjacency_list.at(tail).push_back(edge);
        edge.head = tail;
        graph->adjacency_list.at(head).push_back(edge);
    }
    int number_query;
    cin >> number_query;
    for (int query_index = 0; query_index < number_query; ++query_index) {
        int first_node;
        int second_node;
        cin >> first_node >> second_node;
        queries->push_back(make_pair(first_node - 1, second_node - 1));
    }
}

void Output(const vector<int>& shortest_path) {
    for (int index_query = 0; index_query < shortest_path.size(); ++index_query) {
          cout << shortest_path.at(index_query) << "\n";
    }
} 

void Built_Segment_Nodes_Order(const Graph& graph, 
                               int current_node,
                               vector<int>* color,
                               vector<int>* segment_nodes_order) {
    color->at(current_node) = BLACK;
    segment_nodes_order->push_back(current_node);
    for (int edge_index = 0; edge_index < graph.adjacency_list.at(current_node).size(); ++edge_index) {
            int son = graph.adjacency_list.at(current_node).at(edge_index).head;
            if (color->at(son) == WHITE) {
                    Built_Segment_Nodes_Order(graph, son, color, segment_nodes_order);
                    segment_nodes_order->push_back(current_node);
            }
    }
} 

void Find_Depth(const Graph& graph, 
                int current_node,
                int current_depth,
                vector<int>* color,
                vector<int>* depth) {
    color->at(current_node) = BLACK;
    depth->at(current_node) = current_depth;
    for (int edge_index = 0; edge_index < graph.adjacency_list.at(current_node).size(); ++edge_index) {
            int son = graph.adjacency_list.at(current_node).at(edge_index).head;
            if (color->at(son) == WHITE) {
                    Find_Depth(graph, son, current_depth + 1, color, depth);
            }
    }
} 

void Find_Weight_Path_From_Root(const Graph& graph, 
                                int current_node,
                                int current_weight_path_from_root,
                                vector<int>* color,
                                vector<int>* weight_path_from_root) {
    color->at(current_node) = BLACK;
    weight_path_from_root->at(current_node) = current_weight_path_from_root;
    for (int edge_index = 0; edge_index < graph.adjacency_list.at(current_node).size(); ++edge_index) {
            int son = graph.adjacency_list.at(current_node).at(edge_index).head;
            int edge_weight = graph.adjacency_list.at(current_node).at(edge_index).weight;
            if (color->at(son) == WHITE) {
                    Find_Weight_Path_From_Root(graph, 
                                               son, 
                                               current_weight_path_from_root + edge_weight, 
                                               color, 
                                               weight_path_from_root);
            }
    }
} 

void Initialize(const Graph& graph, 
                vector<int>* segment_nodes_order, 
                vector<int>* depth, 
                vector<int>* weight_path_from_root) {
    int numder_node = graph.adjacency_list.size();
    vector<int> color;

    color.resize(numder_node, WHITE);
    Built_Segment_Nodes_Order(graph, ROOT, &color, segment_nodes_order);

    depth->resize(numder_node);
    color.clear();
    color.resize(numder_node, WHITE);
    Find_Depth(graph, ROOT, 0, &color, depth);
    
    weight_path_from_root->resize(numder_node);
    color.clear();
    color.resize(numder_node, WHITE);
    Find_Weight_Path_From_Root(graph, ROOT, 0, &color, weight_path_from_root);
       
}

void Built_Tree_Of_Search_Min_On_Segment(const vector<int>& segment_nodes_order, 
                                         const vector<int>& depth, 
                                         int current_node, 
                                         int left_end_segment, 
                                         int right_end_segment, 
                                         vector<int>* least_common_ancestor_tree) {
    if (left_end_segment == right_end_segment) {
        least_common_ancestor_tree->at(current_node) = segment_nodes_order.at(left_end_segment);
    } else {
        int middle_segment = (left_end_segment + right_end_segment) / 2;
        int left_son = 2 * current_node + 1;
        int right_son = 2 * current_node + 2;
        Built_Tree_Of_Search_Min_On_Segment(segment_nodes_order, 
                                            depth, 
                                            left_son, 
                                            left_end_segment, 
                                            middle_segment, 
                                            least_common_ancestor_tree);
        Built_Tree_Of_Search_Min_On_Segment(segment_nodes_order, 
                                            depth, 
                                            right_son, 
                                            middle_segment + 1, 
                                            right_end_segment, 
                                            least_common_ancestor_tree);

        if (depth.at(least_common_ancestor_tree->at(left_son)) < 
                      depth.at(least_common_ancestor_tree->at(right_son))) {
            least_common_ancestor_tree->at(current_node) = least_common_ancestor_tree->at(left_son);
        } else {
            least_common_ancestor_tree->at(current_node) = least_common_ancestor_tree->at(right_son);
        }
    }
}

int Find_Node_Min_Depth(const vector<int>& least_common_ancestor_tree, 
                        const vector<int>& depth, 
                        int current_node, 
                        int left_end_segment, 
                        int right_end_segment, 
                        int left_node, 
                        int right_node) {

    if (left_end_segment == left_node && right_end_segment == right_node) {
        return least_common_ancestor_tree.at(current_node);
    }

    int middle_segment = (left_end_segment + right_end_segment) / 2;
    int left_son = 2 * current_node + 1;
    int right_son = 2 * current_node + 2;

    if (right_node <= middle_segment) {
        return Find_Node_Min_Depth(least_common_ancestor_tree, 
                                   depth, 
                                   left_son, 
                                   left_end_segment, 
                                   middle_segment, 
                                   left_node, 
                                   right_node);
    }

    if (left_node > middle_segment) {
        return Find_Node_Min_Depth(least_common_ancestor_tree, depth, 
                                   right_son, 
                                   middle_segment + 1, 
                                   right_end_segment, 
                                   left_node, 
                                   right_node);
    }

    int node_min_depth_in_left_segment = 
             Find_Node_Min_Depth(least_common_ancestor_tree, depth, 
                                 left_son, 
                                 left_end_segment, 
                                 middle_segment, 
                                 left_node, 
                                 middle_segment);

    int node_min_depth_in_right_segment = 
             Find_Node_Min_Depth(least_common_ancestor_tree, 
                                 depth, 
                                 right_son, 
                                 middle_segment + 1, 
                                 right_end_segment, 
                                 middle_segment + 1, 
                                 right_node);

    if (depth.at(node_min_depth_in_left_segment) < depth.at(node_min_depth_in_right_segment)) {
        return node_min_depth_in_left_segment;
    } else {
        return node_min_depth_in_right_segment;
    }
}

int Find_Least_Common_Ancestor(const vector<int>& least_common_ancestor_tree, 
                               const vector<int>& map_segment_nodes_order, 
                               const vector<int>& depth, 
                               int left_end_segment,
                               int right_end_segment,
                               int first_node, 
                               int second_node) {
    int left_node = map_segment_nodes_order.at(first_node);
    int right_node = map_segment_nodes_order.at(second_node);
    if (left_node > right_node) {
        swap(left_node, right_node);
    }
    return Find_Node_Min_Depth(least_common_ancestor_tree, 
                               depth, 
                               ROOT, 
                               left_end_segment, 
                               right_end_segment, 
                               left_node, 
                               right_node);
}

void Shortest_Path(const Graph& graph, 
                   const vector< pair<int, int> >& queries, 
                   vector<int>* shortest_path) {
    vector<int> depth;
    vector<int> weight_path_from_root;
    vector<int> segment_nodes_order;

    Initialize(graph, &segment_nodes_order, &depth, &weight_path_from_root);
   
    vector<int> least_common_ancestor_tree(4 * segment_nodes_order.size(), NODE_IS_NOT_EXIST);
    int left_end_segment = 0;
    int right_end_segment = static_cast<int>(segment_nodes_order.size()) - 1;

    Built_Tree_Of_Search_Min_On_Segment(segment_nodes_order, 
                                        depth, 
                                        ROOT, 
                                        left_end_segment, 
                                        right_end_segment, 
                                        &least_common_ancestor_tree);
    
    int numder_node = graph.adjacency_list.size();
    vector<int> map_segment_nodes_order(numder_node, -1);
    for (int position = 0; position < segment_nodes_order.size(); ++position) {
        int node = segment_nodes_order.at(position);
        if (map_segment_nodes_order.at(node) == -1) {
            map_segment_nodes_order.at(node) = position;
        }
    }

    for (int query_index = 0; query_index < queries.size(); ++query_index) {
           pair<int, int> query = queries.at(query_index);
           int least_common_ancestor = Find_Least_Common_Ancestor(least_common_ancestor_tree,
                                                                  map_segment_nodes_order,
                                                                  depth,
                                                                  left_end_segment,
                                                                  right_end_segment,
                                                                  query.first,
                                                                  query.second);
           int weight_path = weight_path_from_root.at(query.first) + 
                                  weight_path_from_root.at(query.second) - 
                                            2 * weight_path_from_root.at(least_common_ancestor);
           shortest_path->push_back(weight_path);
    }
}

int main() {
    Graph graph;
    vector< pair<int, int> > queries;
    Input(&graph, &queries);
    vector<int> shortest_path;
    Shortest_Path(graph, queries, &shortest_path);
    Output(shortest_path);
    return 0;
}
