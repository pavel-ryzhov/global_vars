#include <iostream>
#include <utility>
#include <vector>

typedef unsigned int EdgeLength;

using std::cin;
using std::pair;
using std::vector;

struct Tree {
    vector<vector<pair<size_t, EdgeLength> > > adjacency_list;
};

struct Queries {
    size_t number;
    vector<vector<pair<size_t, size_t> > > adjacency_list;
};

class DisjointSets {
public:
    explicit DisjointSets(size_t size);
    void MakeSet(size_t element);
    size_t FindSet(size_t element);
    void UniteSets(size_t first_element, size_t second_element);

private:
    std::vector<size_t> representatives;
    std::vector<int> ranks;

    DisjointSets(const DisjointSets&);
    void operator =(const DisjointSets&);
};

inline void DisjointSets::MakeSet(size_t element) {
    representatives.at(element) = element;
}

class GetMinDistances {
public:
    GetMinDistances(const Tree& tree, const Queries& queries);

    vector<EdgeLength> operator ()() const;

private:
    const Tree& tree_;
    const Queries& queries_;

    void doGetMinDistances(
        size_t vertex,
        size_t parent_vertex,
        vector<size_t>& ancestors, 
        DisjointSets& common_ancestor_sets,
        vector<bool>& visited_vertex_flags,
        vector<EdgeLength>& root_distances,
        vector<EdgeLength>& min_distances) const;

    GetMinDistances(const GetMinDistances&);
    void operator =(const GetMinDistances&);
};

void InputTree(size_t vertices_number, Tree* tree);
void InputQueries(size_t vertices_number, Queries* queries);
void Output(const vector<EdgeLength>& min_distances);

int main(int argc, char* argv[]) {
    size_t vertices_number;
    cin >> vertices_number;
    Tree tree;
    InputTree(vertices_number, &tree);
    Queries queries;
    InputQueries(vertices_number, &queries);
    vector<EdgeLength> min_distances = GetMinDistances(tree, queries)();
    Output(min_distances);
    return 0;
}

DisjointSets::DisjointSets(size_t size) : representatives(size, 0), ranks(size, 0) { };

size_t DisjointSets::FindSet(size_t element) {
    if(element != representatives.at(element)) {
        representatives[element] = FindSet(representatives[element]);
    }
    return representatives[element];
}

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

GetMinDistances::GetMinDistances(const Tree &tree, const Queries &queries)
    : tree_(tree), queries_(queries) { }

vector<EdgeLength> GetMinDistances::operator ()() const {
    size_t vertices_number = tree_.adjacency_list.size();
    vector<size_t> ancestors(vertices_number, 0);
    DisjointSets common_ancestor_sets(vertices_number);
    vector<bool> visited_vertex_flags(vertices_number, false);
    vector<EdgeLength> root_distances(vertices_number, 0);
    vector<EdgeLength> min_distances(queries_.number, 0);
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
    size_t vertex_adjacent_number = tree_.adjacency_list[vertex].size();
    for(size_t adjacent_index = 0; adjacent_index < vertex_adjacent_number; ++adjacent_index) {
        size_t adjacent_vertex = tree_.adjacency_list[vertex][adjacent_index].first;
        if(adjacent_vertex != parent_vertex) {
            EdgeLength edge_length = tree_.adjacency_list[vertex][adjacent_index].second;
            root_distances[adjacent_vertex] = edge_length + root_distances[vertex];
            doGetMinDistances(adjacent_vertex, vertex, ancestors, common_ancestor_sets,
                              visited_vertex_flags, root_distances, min_distances);
            common_ancestor_sets.UniteSets(vertex, adjacent_vertex);
            ancestors[common_ancestor_sets.FindSet(vertex)] = vertex;
        }
    }
    visited_vertex_flags[vertex] = true;
    size_t queries_number = queries_.adjacency_list[vertex].size();
    for(size_t query_index = 0; query_index < queries_number; ++query_index) {
        size_t query_vertex = queries_.adjacency_list[vertex][query_index].first;
        if(visited_vertex_flags[query_vertex]) {
            size_t ancester = ancestors[common_ancestor_sets.FindSet(query_vertex)];
            EdgeLength min_distance = root_distances[vertex] + root_distances[query_vertex] - 
                2 * root_distances[ancester];
            size_t query_order = queries_.adjacency_list[vertex][query_index].second;
            min_distances[query_order] = min_distance;
        }
    }
}

void InputTree(size_t vertices_number, Tree* tree) {
    tree->adjacency_list.assign(vertices_number, vector<pair<size_t, EdgeLength> >());
    size_t edges_number = vertices_number - 1;
    for(size_t edge_index = 0; edge_index < edges_number; ++edge_index) {
        size_t first_vertex;
        cin >> first_vertex;
        size_t second_vertex;
        cin >> second_vertex;
        EdgeLength edge_length;
        cin >> edge_length;
        tree->adjacency_list.at(first_vertex - 1).push_back(
            pair<size_t, EdgeLength>(second_vertex - 1, edge_length));
        tree->adjacency_list.at(second_vertex - 1).push_back(
            pair<size_t, EdgeLength>(first_vertex - 1, edge_length));
    }
}

void InputQueries(size_t vertices_number, Queries* queries) {
    queries->adjacency_list.assign(vertices_number, vector<pair<size_t, size_t> >());
    cin >> queries->number;
    for(size_t query_index = 0; query_index < queries->number; ++query_index) {
        size_t first_vertex;
        cin >> first_vertex;
        size_t second_vertex;
        cin >> second_vertex;
        --first_vertex;
        --second_vertex;
        queries->adjacency_list.at(first_vertex).push_back(
            pair<size_t, size_t>(second_vertex, query_index));
        queries->adjacency_list.at(second_vertex).push_back(
            pair<size_t, size_t>(first_vertex, query_index));
    }
}

void Output(const vector<EdgeLength>& min_distances) {
    size_t size = min_distances.size();
    for(size_t i = 0; i < size; ++i) {
        std::cout << min_distances[i] << std::endl;
    }
}
