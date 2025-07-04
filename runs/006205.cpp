#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using std::cin;
using std::cout;
using std::vector;
using std::list;
using std::pair;
using std::min;
using std::map;
using std::endl;

enum {WHITE, BLACK};

struct Edge {
	Edge() {};
	Edge(int linked_vertex, int weight) : linked_vertex_(linked_vertex), weight_(weight) {};
	int linked_vertex_;
	int weight_;
};


void Input(vector<list<Edge> >* tree, list<pair<int, int> >* queries_order, vector<list<int> >* queries) {
	int count_vertexes;
	cin >> count_vertexes;
	queries->resize(count_vertexes);
	tree->resize(count_vertexes);
	for(int index_vertex = 0; index_vertex + 1 < count_vertexes; ++index_vertex) {
		int start;
		int finish;
		int weight;
		cin >> start;
		cin >> finish;
		cin >> weight;

		finish -= 1;
		start -= 1;

		Edge first_edge(finish, weight);
		(*tree)[start].push_back(first_edge);
		Edge second_edge(start, weight);
		(*tree)[finish].push_back(second_edge);
	}


	int count_queries;
	cin >> count_queries;
	for(int index_query = 0; index_query < count_queries; ++index_query) {
		int start;
		int finish;
		cin >> start;
		cin >> finish;
		finish -= 1;
		start -= 1;

		if(start > finish) {
			std::swap(start, finish);
		}
		pair<int, int> nodes(start, finish);
		queries_order->push_back(nodes);

		(*queries)[start].push_back(finish);
		(*queries)[finish].push_back(start);
	}
}

int GetRoot(int vertex, vector<int>* dsu) {
	if(vertex != (*dsu)[vertex]) {
		(*dsu)[vertex] = GetRoot((*dsu)[vertex], dsu);
		return (*dsu)[vertex];
	} 
	return vertex;
}

void UniteDSU(int first, int second, int new_root, vector<int>* dsu, vector<int>* root) {
	int first_root = GetRoot(first, dsu);
	int second_root = GetRoot(second, dsu);
	if(rand() % 2 == 0) {
		(*dsu)[first_root] = second_root;
		(*root)[second_root] = new_root;
	} else {
		(*dsu)[second_root] = first_root;
		(*root)[first_root] = new_root;
	}
}

void DepthFirstSearch(int current_vertex, const vector<list<Edge> >& tree, const vector<list<int> >& queries,
					  vector<int>* distances, map<pair<int, int>, int>* lca_for_query, vector<int>* colour,
					  vector<int>* dsu, vector<int>* root) {
	(*dsu)[current_vertex] = current_vertex;
	(*root)[current_vertex] = current_vertex;
	(*colour)[current_vertex] = BLACK;

	for(list<Edge>::const_iterator node = tree[current_vertex].begin();
		node != tree[current_vertex].end(); ++node) {
			if((*colour)[node->linked_vertex_] == WHITE) {
				(*distances)[node->linked_vertex_] = (*distances)[current_vertex]  + node->weight_;
				DepthFirstSearch(node->linked_vertex_, tree, queries, distances, lca_for_query, colour, dsu, root);
				UniteDSU(current_vertex, node->linked_vertex_, current_vertex, dsu, root);
			}	
	}	

	for(list<int>::const_iterator query = queries[current_vertex].begin(); 
		query != queries[current_vertex].end(); ++query) {
		if((*colour)[*query] == BLACK) {
			if((*lca_for_query).count(pair<int, int>(current_vertex, *query)) == 0 &&
				(*lca_for_query).count(pair<int, int>(*query, current_vertex)) == 0) {
				int lca = GetRoot(*query, dsu);
				if(current_vertex < *query) {
					(*lca_for_query)[pair<int, int>(current_vertex, *query)] = (*root)[lca];
				} else {
					(*lca_for_query)[pair<int, int>(*query, current_vertex)] = (*root)[lca];
				}
			}
		}
	}
}

void FindAnswerForQueries(const vector<list<Edge> >& tree, const vector<list<int> >& queries, vector<int>* distances, map<pair<int, int>, int>* lca_for_query) {
	if(tree.size() == 1) {
		const int INDEX_NODE = 0;
		(*lca_for_query)[pair<int, int>(INDEX_NODE, INDEX_NODE)] = INDEX_NODE;
		return;
	}

	int start = 0;
	vector<int> colour(tree.size(), WHITE);
	vector<int> dsu(tree.size(),-1);
	vector<int> root(tree.size(),-1);

	DepthFirstSearch(start, tree, queries, distances, lca_for_query, &colour, &dsu, &root);
}

void Output(map<pair<int, int>, int>& lca_for_query, const list<pair<int, int> >& queries_order, const vector<int>& distances) {
	for(list<pair<int, int> >::const_iterator query = queries_order.begin(); query != queries_order.end(); ++query) {
		int lca = lca_for_query[*query];
		cout << distances[query->first] + distances[query->second] - 2 * distances[lca] << endl;
	}
}

int main() {
	vector<list<Edge> > tree;
	list<pair<int, int> > queries_order;
	vector<list<int> > queries;
	Input(&tree, &queries_order, &queries);

	vector<int> distances(tree.size(), 0);
	map<pair<int, int>, int> lca_for_query;
	FindAnswerForQueries(tree, queries, &distances, &lca_for_query);

	Output(lca_for_query, queries_order, distances);
	return 0;
}