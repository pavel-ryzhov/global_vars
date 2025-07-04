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
	bool operator== (const Node& other) const;
	
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

bool Node::operator< (const Node& other) const
{
	return weight > other.weight;
}

bool Node::operator== (const Node& other) const
{
	return index == other.index;
}

class Edge {
public:
	int to;
	int weight;
	Edge(int aTo, int aWeight) : to(aTo), weight(aWeight){};
};

class Graph {
	
private:
	std::vector<std::vector<Edge> > list;
public:
	Graph(int aSize);
	void add_edge(int from, int to, int weight);
	int size();
	std::vector<Edge>* get_adjacent(int node);
	~Graph() {};
};

Graph::Graph(int aSize)
{
	list.resize(aSize);
}

void Graph::add_edge(int from, int to, int weight)
{
	if (weight >= 0 && from > 0 && from <= list.size() && to > 0 && to <= list.size()) {
		Edge edge1(to - 1, weight);
		if(&list[from - 1] == 0){
			list[from - 1] = std::vector<Edge>(1, edge1);
		} else {
			list[from - 1].push_back(edge1);
		}
		Edge edge2(from - 1, weight);
		if(&list[to - 1] == 0){
			list[to - 1] = std::vector<Edge>(1, edge2);
		} else {
			list[to - 1].push_back(edge2);
		}
	}
}

int Graph::size()
{
	return list.size();
}

std::vector<Edge>* Graph::get_adjacent(int node)
{
	return &list[node];
}

std::vector<int> find_shortest(Graph* graph, int source)
{
	/*
	 * Initialization
	 */
	std::vector<int> distance(graph->size(), inf);

	std::priority_queue<Node> queue;
	queue.push(Node(source, 0));
	distance[source - 1] = 0;
	/*
	 * Work
	 */
	while (!queue.empty()) {
		
		Node node = queue.top();
		queue.pop();
		
		int u = node.get_index() - 1;
		
		std::vector<Edge>* adjacent = graph->get_adjacent(u);
		if(adjacent == 0)
			continue;

		for (std::vector<Edge>::iterator it = adjacent->begin(); it < adjacent->end(); ++it) {
			int v = (*it).to;
			int w = (*it).weight;

			/*
			 * Relaxation
			 */
			if (distance[u] < inf && distance[v] > distance[u] + w) {
				distance[v] = distance[u] + w;
				Node n(v + 1, distance[v]);
				queue.push(n);
			}
		}
	}
	
	return distance;
}

int main (int argc, char * const argv[]) {
	
	std::string line;
	// get vertices count
	getline(std::cin, line, '\n');
	int vertices = atoi(line.c_str());
	
	// get edges
	Graph* graph = new Graph(vertices);
	
	std::vector<std::vector<int> > weights(vertices, std::vector<int>(vertices, inf));
	
	for(int i = 0; i < vertices - 1; i++){
		getline(std::cin, line, '\n');
		int f, t, w;
		sscanf(line.c_str(), "%i %i %i\n", &f, &t, &w);
		graph->add_edge(f, t, w);
	}
		
	// get pairs count
	getline(std::cin, line, '\n');
	int pairs_count = atoi(line.c_str());
	
	// get pairs
	std::map<int, std::vector<int> > pairs;
	for(int i = 0; i < pairs_count; i++){
		getline(std::cin, line, '\n');
		int f, t;
		sscanf(line.c_str(), "%i %i\n", &f, &t);
		std::map<int, std::vector<int> >::iterator it1 = pairs.find(f);
		std::map<int, std::vector<int> >::iterator it2 = pairs.find(t);
		if(it1 == pairs.end() && it2 == pairs.end()) {
			std::vector<int> shortest = find_shortest(graph, f);
			//a++;
			pairs[f] = shortest;
			std::cout << shortest[t - 1] << std::endl;
		} else if(it1 != pairs.end()) {
			std::cout << (*it1).second[t - 1] << std::endl;
		} else if(it2 != pairs.end()){
			std::cout << (*it2).second[f - 1] << std::endl;
		}
	}
	
	delete graph;
	graph = 0;
	
    return 0;
}
