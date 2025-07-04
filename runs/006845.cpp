#include<iostream>
#include<vector>
#include<utility>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::pair;


typedef enum {WHITE, GREY, BLACK} Color;


struct Edge {
    int tail;
    int head;
	int weight;

	Edge(int tail_value, int head_value, int weight_value) :
	    tail(tail_value), head(head_value), weight(weight_value) {}
};

Edge ReverseEdge(const Edge& old_edge) {
	return Edge(old_edge.head, old_edge.tail, old_edge.weight);
}


class UndirectedGraph {

    vector<vector<Edge> > adjacency_lists_;

    public:

    typedef vector<Edge>::const_iterator EdgeIterator;

    UndirectedGraph() {}
    explicit UndirectedGraph(int order) : adjacency_lists_(order) {}

    void InsertEdge(const Edge& new_edge) {
        adjacency_lists_[new_edge.tail].push_back(new_edge);
        adjacency_lists_[new_edge.head].push_back(ReverseEdge(new_edge));
    }

    void Resize(int order) {
        adjacency_lists_.resize(order);
    }

    int Order() const {
        return adjacency_lists_.size();
    }

    EdgeIterator EdgesBegin(int vertex) const {
        return adjacency_lists_[vertex].begin();
    }

    EdgeIterator EdgesEnd(int vertex) const {
        return adjacency_lists_[vertex].end();
    }
};


//class DefaultDFSVisitor
//Implements (empty) functions of DFS Visitor concept
class DefaultDFSVisitor {

    public:

    void DiscoverVertex(const Edge& incoming_edge) {}
    void ExamineEdge(const Edge& processed_Edge) {}
    void TreeEdge(const Edge& processed_Edge) {}
    void BackEdge(const Edge& processed_edge) {}
    void FinishVertex(int vertex) {}
};


//class PredecessorsRecorder
//Implements a visitor concept used to extend an DFS algorithm.
//For each vertex calculates enter and exit times,
//records predecessors of order 2^i (i= 0, 1, 2...) and paths to predecessors
class PredecessorsRecorder : public DefaultDFSVisitor {

    int time_;
    vector<int> enter_time_;
    vector<int> exit_time_;
    vector<vector<int> > predecessors_matrix_;
    vector<vector<int> > paths_to_predecessors_;
    int num_of_predecessors_;

    public:

    PredecessorsRecorder() {}
    explicit PredecessorsRecorder(int order) : time_(0), enter_time_(order), exit_time_(order),
            predecessors_matrix_(order), paths_to_predecessors_(order) {

        num_of_predecessors_ = 1;
        while ((1 << num_of_predecessors_) <= order) {
            ++num_of_predecessors_;
        }
    }

    void DiscoverVertex(const Edge& incoming_edge) {

        int vertex = incoming_edge.head;
        int parent = incoming_edge.tail;

        enter_time_[vertex] = time_++;

        predecessors_matrix_[vertex].push_back(parent);
        paths_to_predecessors_[vertex].push_back(incoming_edge.weight);

        for (int i = 1; i < Size(); ++i) {
            predecessors_matrix_[vertex].push_back(
                    predecessors_matrix_[predecessors_matrix_[vertex][i - 1]][i - 1]);
            paths_to_predecessors_[vertex].push_back(
                    paths_to_predecessors_[vertex][i - 1] +
                    paths_to_predecessors_[predecessors_matrix_[vertex][i - 1]][i -1]);
		}
	}

    void FinishVertex(int vertex) {
	    exit_time_[vertex] = time_;
    }

    int GetPredecessor(int vertex, int index) const {
        return predecessors_matrix_[vertex][index];
    }

    int GetPathToPredecessor(int vertex, int index) const {
        return paths_to_predecessors_[vertex][index];
    }

    bool IsPredecessor(int first, int second) const {
        return (enter_time_[first] <= enter_time_[second] &&
                exit_time_[first] >= exit_time_[second]);
    }

    int Size() const {
        return num_of_predecessors_;
    }
};


void Input(UndirectedGraph* graph, vector<pair<int, int> >* vertix_pairs);
void Output(const vector<long long>& shortest_paths);

void FindShortestPaths(const UndirectedGraph& graph,
        const vector<pair<int, int> >& vertix_pairs, vector<long long>* shortest_paths);

template<class DFSVisitor>
void DepthFirstSearch(const UndirectedGraph& graph, DFSVisitor* visitor);
template<class DFSVisitor>
void DepthFirstSearch(const UndirectedGraph& graph, int vertex, const Edge& incoming_edge,
        vector<Color>* colors, DFSVisitor* visitor);

int LowestCommonAncestor(int first, int second, const PredecessorsRecorder& predecessors);
long long PathToAncestor(int vertex, int ancestor, const PredecessorsRecorder& predecessors);


int main() {

    UndirectedGraph graph;
    vector<pair<int, int> > vertix_pairs;
    vector<long long> shortest_paths;

    Input(&graph, &vertix_pairs);
    FindShortestPaths(graph, vertix_pairs, &shortest_paths);
    Output(shortest_paths);

    return 0;
}

//===========================================================================

void FindShortestPaths(const UndirectedGraph& graph,
        const vector<pair<int, int> >& vertix_pairs, vector<long long>* shortest_paths) {

    PredecessorsRecorder predecessors(graph.Order());
    DepthFirstSearch<PredecessorsRecorder>(graph, &predecessors);

    shortest_paths->clear();

    for (int i = 0; i < vertix_pairs.size(); ++i) {

        int lca = LowestCommonAncestor(vertix_pairs[i].first, vertix_pairs[i].second, predecessors);

        shortest_paths->push_back(PathToAncestor(vertix_pairs[i].first, lca, predecessors) +
                PathToAncestor(vertix_pairs[i].second, lca, predecessors));
    }
}


//===========================================================================

int LowestCommonAncestor(int first, int second, const PredecessorsRecorder& predecessors) {

    if (predecessors.IsPredecessor(first, second)) {
        return first;
    }
    if (predecessors.IsPredecessor(second, first)) {
        return second;
    }

    for (int index = static_cast<int>(predecessors.Size()) - 1; index >= 0; --index) {
        int parent = predecessors.GetPredecessor(first, index);

        if (!predecessors.IsPredecessor(parent, second)) {
            first = parent;
        }
    }

    return predecessors.GetPredecessor(first, 0);
}

//===========================================================================

long long PathToAncestor(int vertex, int ancestor, const PredecessorsRecorder& predecessors) {

    if (vertex == ancestor) {
        return 0;
    }

    long long path = 0;

    for (int index = static_cast<int>(predecessors.Size()) - 1; index >= 0; --index) {
        int parent = predecessors.GetPredecessor(vertex, index);

        if (predecessors.IsPredecessor(ancestor, parent) && parent != ancestor) {
            path += predecessors.GetPathToPredecessor(vertex, index);
            vertex = parent;
        }
    }

    path += predecessors.GetPathToPredecessor(vertex, 0);
    return path;
}

//===========================================================================

template<class DFSVisitor>
void DepthFirstSearch(const UndirectedGraph& graph, DFSVisitor* visitor) {

    vector<Color> colors(graph.Order(), WHITE);
    DepthFirstSearch<PredecessorsRecorder>(graph, 0, Edge(0, 0, 0), &colors, visitor);
}

//===========================================================================

template<class DFSVisitor>
void DepthFirstSearch(const UndirectedGraph& graph, int vertex, const Edge& incoming_edge,
		vector<Color>* colors, DFSVisitor* visitor) {

    colors->at(vertex) = GREY;
    visitor->DiscoverVertex(incoming_edge);

    UndirectedGraph::EdgeIterator edge;
    for (edge = graph.EdgesBegin(vertex); edge != graph.EdgesEnd(vertex);
            ++edge) {

        visitor->ExamineEdge(*edge);

        if (colors->at(edge->head) == GREY) {
            visitor->BackEdge(*edge);
        }

        if (colors->at(edge->head) == WHITE) {
            DepthFirstSearch(graph, edge->head, *edge, colors, visitor);
            visitor->TreeEdge(*edge);
        }
    }

    visitor->FinishVertex(vertex);
    colors->at(vertex) = BLACK;
}

//===========================================================================

void Input(UndirectedGraph* graph, vector<pair<int, int> >* vertix_pairs) {

    vertix_pairs->clear();

    int order;
    cin >> order;
    graph->Resize(order);

    for (int i = 0; i + 1 < order; ++i) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph->InsertEdge(Edge(source - 1, destination - 1, weight));
    }

    int num_of_pairs;
    cin >> num_of_pairs;
    vertix_pairs->resize(num_of_pairs);

    for (int i = 0; i < num_of_pairs; ++i) {
        int first, second;
        cin >> first >> second;
        vertix_pairs->at(i) = std::make_pair(first - 1, second - 1);
    }
}

//===========================================================================

void Output(const vector<long long>& shortest_paths) {

    for (int i = 0; i < shortest_paths.size(); ++i) {
        cout << shortest_paths[i] << endl;
    }
}

