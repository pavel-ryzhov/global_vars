#include <iostream>
#include <utility>
#include <vector>

typedef unsigned int EdgeLength;
typedef std::vector<std::vector<std::pair<size_t, EdgeLength> > > AdjacencyList;
typedef std::vector<std::vector<std::pair<size_t, size_t> > > QueryList;

using std::cin;
using std::pair;
using std::vector;

class DisjointSets {
public:
	DisjointSets(size_t size);
	void MakeSet(size_t element);
	size_t FindSet(size_t element);
	void UniteSets(size_t first_element, size_t second_element);

private:
	vector<size_t> representatives;
	vector<int> ranks;
};

class GetMinDistances {
public:
	GetMinDistances(const AdjacencyList& adjacency_list, const QueryList& queries, size_t queries_number);

	vector<EdgeLength> operator ()() const;

private:
	const AdjacencyList& adjacency_list_;
	const QueryList& queries_;
	const size_t queries_number_;

	void doGetMinDistances(
		size_t vertex,
		size_t parent_vertex,
		vector<size_t>& ancestors, 
		DisjointSets& common_ancestor_sets,
		vector<bool>& visited_vertex_flags,
		vector<EdgeLength>& root_distances,
		vector<EdgeLength>& min_distances) const;
};

void Input(AdjacencyList* adjacency_list, QueryList* queries, size_t* queries_number);
void AdjacencyListInput(size_t vertices_number, AdjacencyList* adjacency_list);
void QueriesInput(size_t vertices_number, QueryList* queries, size_t* queries_number);
void Output(const vector<EdgeLength>& min_distances);

int main(int argc, char* argv[]) {
	AdjacencyList adjacency_list;
	QueryList queries;
	size_t queries_number;
	Input(&adjacency_list, &queries, &queries_number);
	vector<EdgeLength> min_distances = GetMinDistances(adjacency_list, queries, queries_number)();
	Output(min_distances);
	return 0;
}

inline void DisjointSets::MakeSet(size_t element) {
	representatives.at(element) = element;
}

inline size_t DisjointSets::FindSet(size_t element) {
	if(element != representatives.at(element)) {
		representatives[element] = FindSet(representatives[element]);
	}
	return representatives[element];
}

DisjointSets::DisjointSets(size_t size) : representatives(size, 0), ranks(size, 0) { };

void DisjointSets::UniteSets(size_t first_element, size_t second_element) {
	size_t first_representative = FindSet(first_element);
	size_t second_representative = FindSet(second_element);
	if(ranks[first_representative] > ranks[second_representative]) {
		representatives[second_representative] = first_representative;
	}
	else {
		representatives[first_representative] = second_representative;
		if(ranks[first_representative] == ranks[second_representative]) {
			++ranks[second_representative];
		}
	}
}

GetMinDistances::GetMinDistances(
	const AdjacencyList &adjacency_list, 
	const QueryList &queries,
	size_t queries_number)
	: adjacency_list_(adjacency_list), queries_(queries), queries_number_(queries_number) { }

vector<EdgeLength> GetMinDistances::operator ()() const {
	size_t vertices_number = adjacency_list_.size();
	vector<size_t> ancestors(vertices_number, 0);
	DisjointSets common_ancestor_sets(vertices_number);
	vector<bool> visited_vertex_flags(vertices_number, false);
	vector<EdgeLength> root_distances(vertices_number, 0);
	vector<EdgeLength> min_distances(queries_number_, 0);
	doGetMinDistances(0, 0, ancestors, common_ancestor_sets, visited_vertex_flags,
		root_distances, min_distances);
	return min_distances;
}

void GetMinDistances::doGetMinDistances(
		size_t vertex,
		size_t parent_vertex,
		vector<size_t>& ancestors, 
		DisjointSets& common_ancestor_sets,
		vector<bool>& visited_vertex_flags,
		vector<EdgeLength>& root_distances, 
		vector<EdgeLength>& min_distances) const {
	common_ancestor_sets.MakeSet(vertex);
	ancestors[vertex] = vertex;
	size_t vertex_adjacent_number = adjacency_list_[vertex].size();
	for(size_t adjacent_index = 0; adjacent_index < vertex_adjacent_number; ++adjacent_index) {
		size_t adjacent_vertex = adjacency_list_[vertex][adjacent_index].first;
		if(adjacent_vertex != parent_vertex) {
			EdgeLength edge_length = adjacency_list_[vertex][adjacent_index].second;
			root_distances[adjacent_vertex] = edge_length + root_distances[vertex];
			doGetMinDistances(adjacent_vertex, vertex, ancestors, common_ancestor_sets, visited_vertex_flags,
							  root_distances, min_distances);
			common_ancestor_sets.UniteSets(vertex, adjacent_vertex);
			ancestors[common_ancestor_sets.FindSet(vertex)] = vertex;
		}
	}
	visited_vertex_flags[vertex] = true;
	size_t queries_number = queries_[vertex].size();
	for(size_t query_index = 0; query_index < queries_number; ++query_index) {
		size_t query_vertex = queries_[vertex][query_index].first;
		if(visited_vertex_flags[query_vertex]) {
			size_t ancester = ancestors[common_ancestor_sets.FindSet(query_vertex)];
			EdgeLength min_distance = root_distances[vertex] + root_distances[query_vertex] - 
				2 * root_distances[ancester];
			size_t query_order = queries_[vertex][query_index].second;
			min_distances[query_order] = min_distance;
		}
	}
}

void Input(AdjacencyList* adjacency_list, QueryList* queries, size_t* queries_number) {
	size_t vertices_number;
	cin >> vertices_number;
	AdjacencyListInput(vertices_number, adjacency_list);
	QueriesInput(vertices_number, queries, queries_number);
}

void AdjacencyListInput(size_t vertices_number, AdjacencyList* adjacency_list) {
	adjacency_list->assign(vertices_number, vector<pair<size_t, EdgeLength> >());
	size_t edges_number = vertices_number - 1;
	for(size_t edge_index = 0; edge_index < edges_number; ++edge_index) {
		size_t first_vertex;
		cin >> first_vertex;
		size_t second_vertex;
		cin >> second_vertex;
		EdgeLength edge_length;
		cin >> edge_length;
		adjacency_list->at(first_vertex - 1).push_back(pair<size_t, EdgeLength>(second_vertex - 1, edge_length));
		adjacency_list->at(second_vertex - 1).push_back(pair<size_t, EdgeLength>(first_vertex - 1, edge_length));
	}
}

void QueriesInput(size_t vertices_number, QueryList* queries, size_t* queries_number) {
	queries->assign(vertices_number, vector<pair<size_t, size_t> >());
	cin >> *queries_number;
	for(size_t query_index = 0; query_index < *queries_number; ++query_index) {
		size_t first_vertex;
		cin >> first_vertex;
		size_t second_vertex;
		cin >> second_vertex;
		--first_vertex;
		--second_vertex;
		queries->at(first_vertex).push_back(pair<size_t, size_t>(second_vertex, query_index));
		queries->at(second_vertex).push_back(pair<size_t, size_t>(first_vertex, query_index));
	}
}

void Output(const vector<EdgeLength>& min_distances) {
	size_t size = min_distances.size();
	for(size_t i = 0; i < size; ++i) {
		std::cout << min_distances[i] << std::endl;
	}
}
