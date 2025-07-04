#include<iostream>
#include<vector>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;

const int MAXIMAL_RANK = 40000;

struct BasicNode {
    int number;
    int rank;

    BasicNode(int _rank, int _number)
        :number(_number), rank(_rank)
    {;}

    bool operator< (const BasicNode &rhs) const {
        return rank < rhs.rank;
    }
};

struct Node {
    int number;
    int rank;
    bool first_occurrence;

    Node(int _number, int _rank, bool _first_occurrence)
        :number(_number), rank(_rank), first_occurrence(_first_occurrence)
    {;}
};

struct Edge {
    int begin;
    int end;
    int length;
};

std::istream& operator>>(std::istream &cin, Edge &rhs) {
    cin >> rhs.begin;
    cin >> rhs.end;
    cin >> rhs.length;
    return cin;
}

struct AdjacencyListBase {
    int vertice;
    int edge_length;

    AdjacencyListBase(int _vertice, int _edge_length)
        :vertice(_vertice), edge_length(_edge_length)
    {;}
};

void Input(vector<Edge> *edges, vector<pair<int, int> > *queries) {
    int count_vertices;
    cin >> count_vertices;
    edges->resize(count_vertices - 1);

    for(size_t edge = 0; edge + 1 < count_vertices; ++edge) {
        cin >> (*edges)[edge];
    }

    int count_queries;
    cin >> count_queries;
    queries->resize(count_queries);
    for(size_t query_number = 0; query_number < count_queries; ++query_number) {
        cin >> (*queries)[query_number].first;
        cin >> (*queries)[query_number].second;
    }
}

void BuildAdjacencyList(const vector<Edge> &edges, 
    vector<vector<AdjacencyListBase> > *adjacency_list) {
        for(size_t number = 0; number < edges.size(); ++number) {
            (*adjacency_list)[edges[number].begin]
                .push_back(AdjacencyListBase(edges[number].end, edges[number].length));
            (*adjacency_list)[edges[number].end]
                .push_back(AdjacencyListBase(edges[number].begin, edges[number].length));
        }
}

void EulerTour(const vector<vector<AdjacencyListBase> > &adjacency_list, int current_node,
    int previous_node, int rank, vector<Node> *euler_tour) {
        euler_tour->push_back(Node(current_node, rank, true));
        for(vector<AdjacencyListBase>::const_iterator it = adjacency_list[current_node].begin();
            it != adjacency_list[current_node].end(); 
            ++it) {
                if(it->vertice != previous_node) {
                    EulerTour(adjacency_list, it->vertice, current_node, rank + 1, euler_tour);
                    euler_tour->push_back(Node(current_node, rank, false));
                }
        }
}


void BuildEulerTour(const vector<vector<AdjacencyListBase> > &adjacency_list, 
    vector<Node> *euler_tour) {
        EulerTour(adjacency_list, 1, -1, 0, euler_tour);
}

void ComputeBasicLength(const vector<vector<AdjacencyListBase> > &adjacency_list, int current_node,
    int previous_node, int current_length, vector<int> *basic_length) {
        (*basic_length)[current_node] = current_length;
        for(vector<AdjacencyListBase>::const_iterator it = adjacency_list[current_node].begin();
            it != adjacency_list[current_node].end(); 
            ++it) {
                if(it->vertice != previous_node) {
                    ComputeBasicLength(adjacency_list, it->vertice, current_node, 
                        current_length + it->edge_length, basic_length);
                }
        }

}

void BuildFirstOccurrence(const vector<Node> &euler_tour, vector<int> *first_occurrence) {
    for(size_t number = 1; number < euler_tour.size(); ++number) {
        if (euler_tour[number].first_occurrence == true) {
            (*first_occurrence)[euler_tour[number].number] = number;
        }
    }
}

void BuildSparseTable(const vector<Node> &euler_tour, vector<vector<BasicNode> > *sparse_table) {
    sparse_table->resize(euler_tour.size());
    for(size_t index = 0; index < euler_tour.size(); ++index) {
        (*sparse_table)[index].push_back(BasicNode(euler_tour[index].rank, euler_tour[index].number));
    }
    for(size_t two_in_power = 2, power = 1; 
        two_in_power < euler_tour.size(); 
        two_in_power <<= 1, ++power) {
            for (size_t begin_segment = 0; 
                begin_segment + two_in_power < euler_tour.size() + 1; 
                ++begin_segment) {
                    size_t previous_two_in_power = two_in_power >> 1;
                    BasicNode current_min(MAXIMAL_RANK, 0);
                    for(size_t index = 0; 
                        index + previous_two_in_power < two_in_power + 1; 
                        ++index) {
                            current_min = std::min(current_min, 
                                (*sparse_table)[begin_segment + index].back());
                    }
                    (*sparse_table)[begin_segment].push_back(current_min);
            }
    }
}

int RMQ(const vector<Node> &euler_tour, pair<int, int> query,
    const vector<vector<BasicNode> > &sparse_table) {
        if (query.first > query.second) {
            std::swap(query.first, query.second);
        }
        int distance = query.second - query.first;
        int basic_pow = static_cast<int>(floor(log(static_cast<double>(distance)) / log(2.0)));
        int basic_distance = 1 << basic_pow;
        return std::min(sparse_table[query.first][basic_pow], 
            sparse_table[query.second - basic_distance][basic_pow]).number;
}

int LCA(const vector<Node> &euler_tour, const vector<int> &first_occurrence, 
    const pair<int, int> &query, const vector<vector<BasicNode> > &sparse_table) {
        if (query.first == query.second) {
            return query.first;
        }
        return RMQ(euler_tour, std::make_pair(first_occurrence[query.first], 
            first_occurrence[query.second]), sparse_table);
}

void ComputeResultLengths(const vector<pair<int, int> > &queries, const vector<Node> &euler_tour, 
    vector<int> &basic_length, const vector<int> &first_occurrence, 
    const vector<vector<BasicNode> > &sparse_table, vector<int> *result){
        for(vector<pair<int, int> >::const_iterator it = queries.begin(); 
            it != queries.end(); 
            ++it) {
                int node_number = LCA(euler_tour, first_occurrence, *it, sparse_table);
                int distance = basic_length[it->first] + basic_length[it->second]
                    - 2 * basic_length[node_number];
                result->push_back(distance);
        }
}

void Output(const vector<int> *result) {
    for(vector<int>::const_iterator it = result->begin();
        it != result->end();
        ++it) {
            cout << *it << endl;
    }
}

int main()
{
    vector<Edge> edges;
    vector<pair<int, int> > queries;
    Input(&edges, &queries);

    vector<vector<AdjacencyListBase> > adjacency_list(edges.size() + 2);
    BuildAdjacencyList(edges, &adjacency_list);

    vector<int> basic_length(edges.size() + 2);
    vector<Node> euler_tour;
    BuildEulerTour(adjacency_list, &euler_tour);
    ComputeBasicLength(adjacency_list, 1, -1, 0, &basic_length);
    vector<int> first_occurrence(basic_length.size());
    BuildFirstOccurrence(euler_tour, &first_occurrence);
    
    vector<vector<BasicNode> > sparse_table;
    BuildSparseTable(euler_tour, &sparse_table);

    vector<int> result;
    ComputeResultLengths(queries, euler_tour, basic_length, first_occurrence, sparse_table, &result);

    Output(&result);

	return 0;
}

