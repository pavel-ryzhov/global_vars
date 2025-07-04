#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::queue;

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

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


struct TreeNode {

	int parent;
	vector<int> sons;
	int length;
};


class Tree {
public:
	Tree(const vector<vector<pair<int, int> > > & all_nodes) {

		InitializeTreeNodes(all_nodes);

		current_depth = 1;
		timer = 0;
	}
	
	void InitializeTreeNodes(const vector<vector<pair<int, int> > > & all_nodes);
	void PreprocessTreeParameters();
	void FindShortestPaths(const vector<pair <int, int> > & all_queries);
	void Output() const ;

private:
	vector<TreeNode> tree_nodes;	
	int root_node;
	vector<vector<int> > ancestors;

	vector<int> time_in;
	vector<int> time_out;
	vector<bool> is_used;
	vector<int>  shortest_paths_lengths;

	int timer;
	int current_depth;

	void DFS(const int vertex, const int previous_vertex);
	bool IsUpperVertex(const int first_vertex, const int second_vertex) const;
	int FindLeastCommonAncestor(int first_vertex, const int second_vertex);
};


void Tree::InitializeTreeNodes(const vector<vector<pair<int, int> > > & all_nodes) {
	
	vector<int> node_color(all_nodes.size(), WHITE);
	root_node = -1;

	for (int index = 0; index < all_nodes.size(); ++index) {
		
		if (all_nodes[index].size() == 1 || all_nodes.size() == 1) {

			root_node = index;
			break;
		}
	}

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

				tree_nodes[current_node].sons.push_back(all_nodes[current_node][son_index].first);
				tree_nodes[all_nodes[current_node][son_index].first].parent = current_node;
				tree_nodes[all_nodes[current_node][son_index].first].length = all_nodes[current_node][son_index].second;
			}
		}

		node_color[current_node] = BLACK;
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

	int start_vertex = root_node; 
	int previous_vertex = root_node;
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


void Tree::FindShortestPaths(const vector<pair <int, int> > & all_queries) {

	int least_common_ancestor;
	int shortest_path;
	shortest_paths_lengths.resize(all_queries.size());

	for (int index = 0; index < all_queries.size(); ++index) {

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

	for (int index = 0; index < shortest_paths_lengths.size(); ++index) {

		cout << shortest_paths_lengths[index] << endl;
	}
}



int main() {

	vector<vector<pair<int, int> > > all_nodes;
	vector<pair <int, int> > all_queries;
	Input(&all_nodes, &all_queries);

	Tree my_tree(all_nodes);
	my_tree.PreprocessTreeParameters();
	my_tree.FindShortestPaths(all_queries);
	my_tree.Output();

	return 0;
}