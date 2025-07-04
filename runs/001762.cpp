#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

enum Color {Black, Grey, White};
struct Node {
    int ancestor;
    //pair <int, int> ancestor_with_path_cost;  
	list <pair <int, int> > adjacent_nodes_with_edge_cost;
    //int rank;
    int depth; //растояние от корня
	void AddAdjacentNode(int adjacent_node, int cost) {
		adjacent_nodes_with_edge_cost.push_back(std::make_pair(adjacent_node, cost));
	}
};
struct LeastCommonAncestor {
    int first_node;
    int second_node;
    int ancestor;
};

class DisjointSets {
public:
    int FindSet(vector <Node>* nodes, int node_number) {
        if(nodes->at(node_number).ancestor != node_number) {           
            nodes->at(node_number).ancestor = FindSet(nodes, nodes->at(node_number).ancestor);
        }
        return nodes->at(node_number).ancestor;
    }
    /*void Union(int first_node_number, int second_node_number) {//, int new_ancestor) {
        first_set_representative = FindSet(first_node_number);
        second_set_representative = FindSet(second_node_number);
        if(nodes[first_set_representative].rank > nodes[second_set_representative].rank) {
            nodes[second_set_representative].ancestor_with_path_cost.first = first_set_representative;
        }
        else {
            nodes[first_set_representative].ancestor = second_set_representative;
        }
        if(nodes[first_set_representative].rank == nodes[second_set_representative].rank) {
            ++nodes[second_set_representative].rank;
        }
    }*/
    void Union(vector <Node>* nodes, int subtree_ancestor, int new_tree_ancestor) {
        nodes->at(subtree_ancestor).ancestor = new_tree_ancestor;
    }
    void MakeSet(vector <Node>* nodes, int node_number) {
        nodes->at(node_number).ancestor = node_number;        
    }
};

void Input(vector <Node >* nodes, vector <list <pair <int, int> > >* query_number_for_each_node, vector <LeastCommonAncestor>* nodes_in_queries) {
	int number_nodes, number_edges;
	cin >> number_nodes;
	nodes->resize(number_nodes);
    query_number_for_each_node->resize(number_nodes);
	for(int edge_counter = 0; edge_counter < number_nodes - 1; ++edge_counter) {
		int first_node, second_node, cost;
		cin >> first_node >> second_node >> cost;
        nodes->at(first_node - 1).AddAdjacentNode(second_node - 1, cost);
		nodes->at(second_node - 1).AddAdjacentNode(first_node - 1, cost);
	}
    int number_queries;
    cin >> number_queries;
    nodes_in_queries->resize(number_queries);
    for(int query_number = 0; query_number < number_queries; ++query_number) {
        int first_node, second_node;
        cin >> first_node >> second_node;
        query_number_for_each_node->at(first_node - 1).push_back(make_pair(second_node - 1, query_number));
        query_number_for_each_node->at(second_node - 1).push_back(make_pair(first_node - 1, query_number));
        nodes_in_queries->at(query_number).first_node = first_node - 1;
        nodes_in_queries->at(query_number).second_node = second_node - 1;
    }
}

void Output(vector <int>& shortest_path_length) {
    for(int i = 0; i < shortest_path_length.size(); ++i) {
        cout << shortest_path_length[i] << endl;
    }
}

void DFS(vector <Node >& nodes, int current_node, vector <Color>& colors, vector <list <pair <int, int> > >& query_number_for_each_node, vector <LeastCommonAncestor>& nodes_in_queries) {
    colors[current_node] = Grey;
    for(list <pair <int, int > >::const_iterator iter = nodes[current_node].adjacent_nodes_with_edge_cost.begin(); 
        iter != nodes[current_node].adjacent_nodes_with_edge_cost.end();  ++iter) {
        int adjacent_node = iter->first;
        int current_cost = iter->second;     
        if(colors[adjacent_node] == White) {
            nodes[adjacent_node].depth = nodes[current_node].depth + current_cost;
            DFS(nodes, adjacent_node, colors, query_number_for_each_node, nodes_in_queries);
            DisjointSets disjoint_sets;
            disjoint_sets.Union(&nodes, adjacent_node, current_node);
        }
    }
    for(list <pair <int, int> >::iterator queries_iterator = query_number_for_each_node[current_node].begin(); queries_iterator != query_number_for_each_node[current_node].end(); ++queries_iterator) {
        if(colors[queries_iterator->first] == Black) {
            DisjointSets disjoint_sets;
            int second_node_representative = disjoint_sets.FindSet(&nodes, queries_iterator->first);
            int least_common_ancestor = nodes[second_node_representative].ancestor;
            int query_number = queries_iterator->second;
            nodes_in_queries[query_number].first_node = current_node;
            nodes_in_queries[query_number].second_node = queries_iterator->first;
            nodes_in_queries[query_number].ancestor = least_common_ancestor;
        }
    }   
    colors[current_node] = Black;
}

vector <int> FindShortestPathLengthInTree(vector <Node> nodes, vector <list <pair <int, int> > >& query_number_for_each_node, vector <LeastCommonAncestor>& nodes_in_queries) {
    vector <int> answer(nodes_in_queries.size());
    DisjointSets disjoint_sets;
    for(int i = 0; i < nodes.size(); ++i) {
        disjoint_sets.MakeSet(&nodes, i);
    }
    vector <Color> colors(nodes.size(), White);
    int root = 0;
    nodes[root].depth = 0;
    DFS(nodes, root, colors, query_number_for_each_node, nodes_in_queries);
    for(int query_number = 0; query_number < nodes_in_queries.size(); ++query_number) {
        int first_node = nodes_in_queries[query_number].first_node;
        int second_node = nodes_in_queries[query_number].second_node;
        if(first_node != second_node) {
            int first_node_depth = nodes[first_node].depth;
            int second_node_depth = nodes[second_node].depth;
            int ancestor_depth = nodes[nodes_in_queries[query_number].ancestor].depth;
            answer[query_number] = first_node_depth + second_node_depth - 2 * ancestor_depth;
        }
        else {
            answer[query_number] = 0;
        }
    }
    return answer;
}

int main() {
    vector <Node > nodes;
    vector <list <pair <int, int> > > query_number_for_each_node;
    vector <LeastCommonAncestor> nodes_in_queries;
    Input(&nodes, &query_number_for_each_node, &nodes_in_queries);
    vector <int> shortest_path_length = FindShortestPathLengthInTree(nodes, query_number_for_each_node, nodes_in_queries);
    Output(shortest_path_length);
    return 0;
}

	