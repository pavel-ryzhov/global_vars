#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include "time.h"
#include <map>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::pair;
using std::swap;
using std::map;
using std::queue;


const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;


struct TreeNode {

	int parent;
	set<int> sons;
	int length;
};



class Tree {
	
public:
	Tree(const vector<vector<pair<int, int> > > & all_nodes) {

		InitializeTreeNodes(all_nodes);
	}

	friend void DFS (const Tree & , map<int, vector<pair<int, int> > > & extended_queries,
		  vector<int>* parent, vector<int>* ancestor, vector<bool>* color, int vertex, vector<int>* least_common_ancestor );

	friend void FindShortestPaths(const Tree & , const vector<pair <int, int> > & all_queries, const vector<int> & least_common_ancestor, vector<int> * shortest_paths_lengths);

private:
	vector<TreeNode> tree_nodes;

	void InitializeTreeNodes(const vector<vector<pair<int, int> > > & all_nodes);
};



void Input(vector<vector<pair<int, int> > > * all_nodes, vector<pair <int, int> > * all_queries) {

	int nodes_number;
	int first_node_index, second_node_index, edge_weight;
	cin >> nodes_number;

	all_nodes->resize(nodes_number);

	for (int node_index = 0; node_index < nodes_number - 1; ++node_index) {

		cin >> first_node_index >> second_node_index >> edge_weight;
		(*all_nodes)[first_node_index - 1].push_back(pair<int, int> (second_node_index - 1, edge_weight));
		(*all_nodes)[second_node_index - 1].push_back(pair<int, int> (first_node_index - 1, edge_weight));
	}

	int queries_number;
	cin >> queries_number;
	int from_node, to_node;

	for (int query_index = 0; query_index < queries_number; ++query_index) {

		cin >> from_node >> to_node;
		(*all_queries).push_back(pair <int, int> (from_node - 1, to_node - 1));
	}
}


void ExtendQueries(const vector<pair <int, int> > & all_queries, map<int, vector<pair<int, int> > > * extended_queries) {

	for (int index = 0; index < all_queries.size(); ++index) {
		
		int first_node = all_queries[index].first;
		int second_node = all_queries[index].second;

		if (extended_queries->find(first_node) == extended_queries->end()) {

			vector<pair<int, int> > tmp_vector(1, pair<int, int> (second_node, index));
			extended_queries->insert(pair<int, vector<pair<int, int> > > (first_node, tmp_vector));

		}	else {

			(*extended_queries)[first_node].push_back(pair<int, int> (second_node, index));
		}

		if (extended_queries->find(second_node) == extended_queries->end()) {

			vector<pair<int, int> > tmp_vector(1, pair<int, int> (first_node, index));
			extended_queries->insert(pair<int, vector<pair<int, int> > > (second_node, tmp_vector));

		}	else {

			(*extended_queries)[second_node].push_back(pair<int, int> (first_node, index));
		}
	}
}

void Tree::InitializeTreeNodes(const vector<vector<pair<int, int> > > & all_nodes) {
	
	vector<int> node_color(all_nodes.size(), WHITE);
	int root_node = 0;

	tree_nodes.resize(all_nodes.size());
	tree_nodes[root_node].parent = -1;
	
	queue<int> nodes_to_visit;
	node_color[root_node] = GRAY;
	nodes_to_visit.push(root_node);

	while (nodes_to_visit.size() != 0) {
		
		int current_node = nodes_to_visit.front();
		nodes_to_visit.pop();

		for (int son_index = 0; son_index < all_nodes[current_node].size(); ++son_index) {

			int son_node = all_nodes[current_node][son_index].first;
			
			if (node_color[son_node] == WHITE) {

				node_color[son_node] = GRAY;
				nodes_to_visit.push(son_node);
			}

			if (all_nodes[current_node][son_index].first != tree_nodes[current_node].parent) { 

				tree_nodes[current_node].sons.insert(all_nodes[current_node][son_index].first);
				tree_nodes[all_nodes[current_node][son_index].first].parent = current_node;
				tree_nodes[all_nodes[current_node][son_index].first].length = all_nodes[current_node][son_index].second;
			}
		}

		node_color[current_node] = BLACK;
	}
}


 
int FindSet(vector<int> *parent, int vertex) {	
	
	if (vertex == parent->at(vertex)) {

		return vertex;

	} else {

		return (parent->at(vertex) = FindSet(parent, parent->at(vertex)));  
	}

}
 


void UniteSets(vector<int>* parent, vector<int>* ancestor, const int first_vertex, const int second_vertex) {

	int first_vertex_representative = FindSet(parent, first_vertex);
	int second_vertex_representative = FindSet(parent, second_vertex);

	if (rand() & 1)  {
		swap(first_vertex_representative, second_vertex_representative);
	}

	parent->at(first_vertex_representative) = second_vertex_representative;
}
 


void DFS (const Tree & my_tree, map<int, vector<pair<int, int> > > & extended_queries,
		  vector<int>* parent, vector<int>* ancestor, vector<bool>* color, int vertex, vector<int>* least_common_ancestor ) {

	parent->at(vertex) = vertex;  
	ancestor->at(FindSet(parent, vertex)) = vertex; 

	set<int>::const_iterator current_son_iterator;

	for (current_son_iterator = my_tree.tree_nodes[vertex].sons.begin(); current_son_iterator != my_tree.tree_nodes[vertex].sons.end(); ++current_son_iterator) {

			DFS(my_tree, extended_queries, parent, ancestor, color, *current_son_iterator, least_common_ancestor);
			UniteSets(parent, ancestor, vertex, *current_son_iterator);
			ancestor->at(FindSet(parent, vertex)) = vertex;
	}

	color->at(vertex) = true;

	for (int index = 0; index < extended_queries[vertex].size(); ++index) {

		if (color->at(extended_queries[vertex][index].first)) {

			least_common_ancestor->at(extended_queries[vertex][index].second) = ancestor->at(FindSet(parent, extended_queries[vertex][index].first));

		}
	}
}
 

void FindShortestPaths(const Tree & my_tree, const vector<pair <int, int> > & all_queries, const vector<int> & least_common_ancestor, vector<int> * shortest_paths_lengths) {

	int current_least_common_ancestor;
	int shortest_path;
	(*shortest_paths_lengths).resize(all_queries.size());

	for (int index = 0; index < all_queries.size(); ++index) {

		shortest_path = 0;
		int first_vertex = all_queries[index].first;
		int second_vertex = all_queries[index].second;

		current_least_common_ancestor = least_common_ancestor[index];

		while (first_vertex != current_least_common_ancestor) {

			shortest_path += my_tree.tree_nodes[first_vertex].length;
			first_vertex = my_tree.tree_nodes[first_vertex].parent;
		}

		while (second_vertex != current_least_common_ancestor) {

			shortest_path += my_tree.tree_nodes[second_vertex].length;
			second_vertex = my_tree.tree_nodes[second_vertex].parent;
		}

		(*shortest_paths_lengths)[index] = shortest_path;
	}
}



void Output(const vector<int> & shortest_paths_lengths) {
	

	for (int index = 0; index < shortest_paths_lengths.size(); ++index) {

		cout << shortest_paths_lengths[index] << endl;
	}
}





int main() {

	vector<vector<pair<int, int> > > all_nodes;
	vector<pair <int, int> > all_queries;
	Input(&all_nodes, &all_queries);

	map<int, vector<pair<int, int> > > extended_queries;
	ExtendQueries(all_queries, &extended_queries);
	
	Tree my_tree(all_nodes);

	vector<int> parent(all_nodes.size(), 0), ancestor(all_nodes.size(), 0); 
	vector<bool> color(all_nodes.size(), false);
	vector<int> least_common_ancestor(all_queries.size());
	int root_node = 0;
	DFS(my_tree, extended_queries, &parent, &ancestor, &color, root_node, &least_common_ancestor);

	vector<int> shortest_paths_lengths;
	FindShortestPaths(my_tree, all_queries, least_common_ancestor, &shortest_paths_lengths);
	Output(shortest_paths_lengths);

	return 0;
}