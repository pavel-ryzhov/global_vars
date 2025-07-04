#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <map>

const int inf = std::numeric_limits<int>::max();

class Node {
private:
	int index;
	int weight;
public:
	Node(int aIndex) : index(aIndex), weight(0) {};
	Node(int aIndex, int aWeight) : index(aIndex), weight(aWeight) {};
	
	bool operator< (const Node& other) const;
	
	int get_index();
	int get_weight();
	void set_weight(int aWeight);

	~Node() {};
};

int Node::get_index()
{
	return index;
}

int Node::get_weight()
{
	return weight;
}

void Node::set_weight(int aWeight)
{
	weight = aWeight;
}

//struct NodesComparator {
//public:
//	bool operation()(Node& x, Node& y)
//	{
//		return x.get_weight() == y.get_weight() ? x.get_index() < y.get_index() : x.get_weight() < y.get_weight();
//	}
//};
//bool operator< (Node& x, Node& y)
//{
//	return x.get_weight() == y.get_weight() ? x.get_index() < y.get_index() : x.get_weight() < y.get_weight();
//}

bool Node::operator< (const Node& other) const
{
	return weight > other.weight;
}

class AdjacencyMatrixGraph {
	
private:
	std::vector<std::vector<int> > weights;
public:
	AdjacencyMatrixGraph(int aSize);
	void add_edge(int from, int to, int weight);
	int size();
	int get_edge_weight(int from, int to);
	~AdjacencyMatrixGraph();
};

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int aSize)
{
	// Resize array and fill array with default values
	weights.resize(aSize);
	for (int i = 0; i < aSize; ++i){
		weights[i].resize(aSize);
		for (int j = 0; j < aSize; ++j) {
			weights[i][j] = (i == j) ? 0 : inf;
		}
	}
}

void AdjacencyMatrixGraph::add_edge(int from, int to, int weight)
{
	if (weight > 0 && from > 0 && from <= weights.size() && to > 0 && to <= weights.size()) {
		weights[from - 1][to - 1] = weight;
		weights[to - 1][from - 1] = weight;
	}
}

int AdjacencyMatrixGraph::size()
{
	return weights.size();
}

int AdjacencyMatrixGraph::get_edge_weight(int from, int to)
{
	if (from >= 0 && from < weights.size() && to >= 0 && to < weights.size())
		return weights[from][to];
	return inf;
}

AdjacencyMatrixGraph::~AdjacencyMatrixGraph()
{
}

std::vector<int> find_shortest(AdjacencyMatrixGraph* graph, int source){
	
	/*
	 * Initialization
	 */
	std::vector<int> distance(graph->size(), inf);

	std::vector<Node> queue;
	for (int i = 1; i <= graph->size(); ++i) {
		queue.push_back(Node(i, i == source ? 0 : inf));
	}
	std::make_heap(queue.begin(), queue.end());
	std::sort(queue.begin(), queue.end());

	distance[source - 1] = 0;
	
	/*
	 * Work
	 */
	while (!queue.empty()) {
		
		Node node = queue.back();
		queue.pop_back();
		
		int u = node.get_index() - 1;
		
		for (std::vector<Node>::iterator it = queue.begin(); it < queue.end(); ++it) {
			int v = (*it).get_index() - 1;

			/*
			 * Relaxation
			 */
			if (graph->get_edge_weight(u, v) < inf && distance[u] < inf && (distance[u] + graph->get_edge_weight(u, v)) > 0
				&& distance[v] > distance[u] + graph->get_edge_weight(u, v)) {
				distance[v] = distance[u] + graph->get_edge_weight(u, v);
				(*it).set_weight(distance[v]);
			}
		}
		std::sort(queue.begin(), queue.end());
		
	}
	
	return distance;
}

int main (int argc, char * const argv[]) {
	
	std::string line;
	// get vertices count
	getline(std::cin, line, '\n');
	int vertices = atoi(line.c_str());
	
	// get edges
	AdjacencyMatrixGraph* graph = new AdjacencyMatrixGraph(vertices);
	for(int i = 0; i < vertices - 1; i++){
		getline(std::cin, line, '\n');
		int f, t, w;
		sscanf(line.c_str(), "%i %i %i\n", &f, &t, &w);
		graph->add_edge(f, t, w);
	}
	
	// get pairs count
	getline(std::cin, line, '\n');
	int pairs_count = atoi(line.c_str());
	
	std::map<int, std::vector<int> > pairs;
	// get pairs
	for(int i = 0; i < pairs_count; i++){
		getline(std::cin, line, '\n');
		int f, t;
		sscanf(line.c_str(), "%i %i\n", &f, &t);
		std::map<int, std::vector<int> >::iterator it = pairs.find(f);
		if(it == pairs.end()) {
			std::vector<int> shortest = find_shortest(graph, f);
			pairs[f] = shortest;
			std::cout << shortest[t - 1] << std::endl;
		} else {
			std::cout << (*it).second[t - 1] << std::endl;
		}
	}
	
	delete graph;
	graph = 0;
	
    return 0;
}
