#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdlib>

using std::vector;
using std::pair;

typedef long long LongInt;

class DSU {
public:
    DSU( size_t size = 0)
        : parents_( size), ancestors_( size) {
    }
    void set_size( size_t size);
    void create( size_t element);
    void unite( size_t element1, size_t element2, size_t ancestor);
    size_t get( size_t element);
    size_t get_ancestor( size_t element); 
private:
    vector<size_t> parents_;
    vector<size_t> ancestors_;
};

class Edge {
public:
    Edge( size_t to = 0, LongInt weight = 0) 
       : to_(to), weight_(weight) {
    }
    size_t to() { return to_; }
    LongInt weight() { return weight_; }
private:
    size_t to_;
    LongInt weight_;
};

struct SearchState {
    DSU dsu;
    vector<bool> visited;
    vector< vector< pair<size_t, size_t> > > queries;
    vector<LongInt> distances_from_root;
    vector<LongInt> answers;
};

class Tree {
public:
    Tree( size_t size = 0) : tree_nodes_( size + 1) {
    }
    void set_size( size_t size);
    void add_edge( size_t from, size_t to, LongInt weight);
    void find_distances( const vector< pair<size_t, size_t> >& queries, vector<LongInt>* answers);
private:
    vector< vector<Edge> > tree_nodes_;
    void dfs( size_t node, LongInt root_distance, SearchState* state);
};

void DSU::set_size( size_t size) {
    parents_.assign( size, 0);
    ancestors_.assign( size, 0);
    return;
}

void DSU::create( size_t element) {
    parents_[element] = element;
    ancestors_[element] = element;
    return;
}

void DSU::unite( size_t element1, size_t element2, size_t ancestor) {
    element1 = get( element1);
    element2 = get( element2);
    if ( rand() & 1 ) {
        std::swap( element1, element2);
    }
    parents_[element1] = element2;
    ancestors_[element2] = ancestor;
    return;
}

size_t DSU::get( size_t element) {
    if ( element != parents_[element] ) {
        parents_[element] = get( parents_[element]);
    }
    return parents_[element];
}

size_t DSU::get_ancestor( size_t element) {
    return ancestors_[get( element)];
}

void Tree::add_edge( size_t from, size_t to, LongInt weight) {
    tree_nodes_[from].push_back( Edge( to, weight));
    tree_nodes_[to].push_back( Edge( from, weight));
    return;
}

void Tree::set_size( size_t size) {
    tree_nodes_.clear();
    tree_nodes_.resize( size + 1);
    return;
}

void Tree::find_distances( const vector< pair<size_t, size_t> >& queries, vector<LongInt>* answers) {
    SearchState state;
    state.distances_from_root.resize( tree_nodes_.size());
    state.dsu.set_size( tree_nodes_.size());
    state.queries.resize( tree_nodes_.size());
    state.visited.assign( tree_nodes_.size(), false);
    state.answers.resize( queries.size()); 
    for ( int query_index = 0; query_index < queries.size(); ++query_index ) {
        pair<size_t, size_t> query = queries[query_index];
        state.queries[query.first].push_back( std::make_pair( query.second, query_index));
        if ( query.first != query.second ) {
            state.queries[query.second].push_back( std::make_pair( query.first, query_index));
        }
    }
    dfs( 1, 0, &state);
    *answers = state.answers;
    return;
}

void Tree::dfs( size_t node, LongInt root_distance, SearchState* state) {
    srand( 0);
    state->dsu.create( node);
    state->visited[node] = true;
    state->distances_from_root[node] = root_distance;
    for ( vector<Edge>::iterator edge = tree_nodes_[node].begin();
          edge != tree_nodes_[node].end();
          ++edge ) {
        if ( !state->visited[edge->to()] ) {
            dfs( edge->to(), root_distance + edge->weight(), state);
            state->dsu.unite( node, edge->to(), node);
        }
    }
    for ( vector< pair<size_t, size_t> >::iterator query = state->queries[node].begin();
          query != state->queries[node].end();
          ++query ) {
        if ( state->visited[query->first] ) {
            size_t lca = state->dsu.get_ancestor( query->first);
            state->answers[query->second] = root_distance + state->distances_from_root[query->first]
                - 2 * state->distances_from_root[lca];
        } 
    }
    return;
}

void Input( Tree* tree, vector< pair<size_t, size_t> >* queries) {
    size_t tree_size;
    std::cin >> tree_size;
    tree->set_size( tree_size);
    for ( int edge_index = 1; edge_index < tree_size; ++ edge_index ) {
        size_t from, to, weight;
        std::cin >> from >> to >> weight;
        tree->add_edge( from, to, weight);
    }
    size_t query_count;
    std::cin >> query_count;
    queries->clear();
    for ( size_t query_index = 0; query_index < query_count; ++query_index ) {
        pair<size_t, size_t> query;
        std::cin >> query.first >> query.second;
        queries->push_back( query);
    }
    return;
}

void Output( const vector<LongInt>& answers) {
    for ( vector<LongInt>::const_iterator answer = answers.begin();
          answer != answers.end();
          ++answer ) {
        std::cout << *answer << std::endl;
    }
    return;
}

int main() {
    Tree tree;
    vector< pair<size_t, size_t> > queries;
    Input( &tree, &queries);
    vector<LongInt> answers;
    tree.find_distances( queries, &answers);
    Output( answers);
    return 0;
}

