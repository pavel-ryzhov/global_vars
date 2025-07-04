#include <iostream>
#include <vector>
#include <set>
#include <list>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::list;
using std::pair;
using std::iterator;


struct Node {
	int parent;
	vector<int> sons;
	int length;
};


class Tree {
public:
	Tree() {
		current_depth = 1;
		timer = 0;

	}
	
	void Input();
	void PreprocessTreeParameters();
	void FindShortestPaths();
	void Output() const ;

private:
	vector<Node> tree_nodes;	
	vector<vector<int> > ancestors;

	vector<int> time_in;
	vector<int> time_out;
	vector<bool> is_used;
	vector<pair <int, int> > all_queries;
	vector<int>  shortest_paths_lengths;

	int timer;
	int current_depth;

	void DFS(const int vertex, const int previous_vertex);
	bool IsUpperVertex(const int first_vertex, const int second_vertex) const;
	int FindLeastCommonAncestor(int first_vertex, const int second_vertex);

};


void Tree::Input() {
	int nodes_number;
	int parent_node_index, son_node_index, edge_weight;
	cin >> nodes_number;
	tree_nodes.resize(nodes_number);
	tree_nodes[0].parent = -1;


	for (int node_index = 0; node_index < nodes_number - 1; ++node_index) {

		cin >> parent_node_index >> son_node_index >> edge_weight;
		tree_nodes[parent_node_index - 1].sons.push_back(son_node_index - 1);
		tree_nodes[son_node_index - 1].parent =  parent_node_index - 1;
		tree_nodes[son_node_index - 1].length = edge_weight;
	}

	int queries_number;
	cin >> queries_number;
	int from_node, to_node;

	for (int query_index = 0; query_index < queries_number; ++query_index) {
		cin >> from_node >> to_node;
		all_queries.push_back(pair <int, int> (from_node - 1, to_node - 1));
	}
}


void Tree::PreprocessTreeParameters() {

	is_used.resize(tree_nodes.size(), false);
	time_in.resize(tree_nodes.size());
	time_out.resize(tree_nodes.size());
	ancestors.resize(tree_nodes.size());

	

	while ((1 << current_depth) <= tree_nodes.size()) {
		++current_depth;	
	}

	for (int index = 0; index < tree_nodes.size(); ++index) {
		ancestors[index].resize(current_depth + 1);
	}

	int start_vertex = 0;
	int previous_vertex = 0;
	DFS(start_vertex, previous_vertex);
}



void Tree::DFS(const int vertex, const int previous_vertex) {

	is_used[vertex] = true;
	time_in[vertex] = ++timer;
	ancestors[vertex][0] = previous_vertex;

	for (int index = 1; index < current_depth; ++index) {
		ancestors[vertex][index] = ancestors[ancestors[vertex][index - 1]][index - 1];
	}

	if ( !tree_nodes[vertex].sons.empty()) {
		for (int index = 0; index < tree_nodes[vertex].sons.size(); ++index) {
			
			int next_vertex = tree_nodes[vertex].sons[index];
			if ( !is_used[next_vertex]) {

				DFS(next_vertex, vertex);
			}
		}
	}

	time_out[vertex] = ++timer;

}


bool Tree::IsUpperVertex(const int first_vertex, const int second_vertex) const {
	return time_in[first_vertex] <= time_in[second_vertex] && time_out[first_vertex] >= time_out[second_vertex];
}


int Tree::FindLeastCommonAncestor(int first_vertex, const int second_vertex) {
	if (IsUpperVertex(first_vertex, second_vertex)) {
		return first_vertex;
	}

	if (IsUpperVertex(second_vertex, first_vertex)) {
		return second_vertex;
	}

	for (int index = current_depth; index >= 0 ; --index) {
		if ( !IsUpperVertex(ancestors[first_vertex][0], second_vertex)) {
				
				first_vertex = ancestors[first_vertex][0];
		}
	}
	
	return ancestors[first_vertex][0];
}


void Tree::FindShortestPaths() {
	int least_common_ancestor;
	int shortest_path;
	shortest_paths_lengths.resize(all_queries.size());

	for ( int index = 0; index < all_queries.size(); ++index) {
		shortest_path = 0;
		int first_vertex = all_queries[index].first;
		int second_vertex = all_queries[index].second;

		least_common_ancestor = FindLeastCommonAncestor(first_vertex, second_vertex);

		while (first_vertex != least_common_ancestor) {
			shortest_path += tree_nodes[first_vertex].length;
			first_vertex = tree_nodes[first_vertex].parent;
		}

		while (second_vertex != least_common_ancestor) {
			shortest_path += tree_nodes[second_vertex].length;
			second_vertex = tree_nodes[second_vertex].parent;
		}

		shortest_paths_lengths[index] = shortest_path;
	}
}



void Tree::Output() const {
	for ( int index = 0; index < shortest_paths_lengths.size(); ++index) {

		cout << shortest_paths_lengths[index] << endl;
	}
}



int main() {

	Tree my_tree;
	my_tree.Input();
	my_tree.PreprocessTreeParameters();
	my_tree.FindShortestPaths();
	my_tree.Output();

	return 0;
}