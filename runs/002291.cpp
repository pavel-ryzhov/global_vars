#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

class Node {
public:
	int index;
	bool visited;

	Node(int aIndex) : index(aIndex), visited(false) {};
	
	int getIndex() {
		return index;		
	};
};

class Edge {
public:
	int to;
	int weight;
	
	Edge(int aTo, int aWeight) : to(aTo), weight(aWeight){};
};

class Graph {	
private:
	std::vector<std::vector<Edge> > list;
	std::vector<Node> nodes;

public:
	Graph(int aSize) {
		list.resize(aSize);
		for(int i = 0; i < aSize; ++i) {
			nodes.push_back(Node(i + 1));
		}
	};
	
	void addEdge(int from, int to, int weight) {
		if (weight >= 0 && from > 0 && from <= list.size() && to > 0 && to <= list.size()) {
			
			Edge edge1(to, weight);
			if(&list[from - 1] == 0) {
				list[from - 1] = std::vector<Edge>(1, edge1);
			} else {
				list[from - 1].push_back(edge1);
			}
			
			Edge edge2(from, weight);
			if(&list[to - 1] == 0) {
				list[to - 1] = std::vector<Edge>(1, edge2);
			} else {
				list[to - 1].push_back(edge2);
			}
		}		
	};
	
	int size() {
		return list.size();
	}
	
	std::vector<Edge>* getAdjacent(int node) {
		return &list[node - 1];
	};
	
	Node* getNode(int node) {
		return &nodes[node - 1];
	}
	
	void resetVisited() {
		for (std::vector<Node>::iterator it = nodes.begin(); it < nodes.end(); ++it) {
			(*it).visited = false;
		}
	}
};

class Pathfinder {
private:
	Graph* graph;
	int result;
	int start;
	std::vector<std::vector<int> > shortest;
public:
	Pathfinder(Graph* aGraph) {
		for(int i = 0; i < aGraph->size(); ++i) {
			shortest.push_back(std::vector<int>(aGraph->size(), -1));
		}
		graph = aGraph;
		result = 0;
	};
	
	int findShortest(int source, int destination) {
	
		result = 0;
		start = source;
		if(shortest[source - 1][destination - 1] > 0)
			return shortest[source - 1][destination - 1];
		if(shortest[destination - 1][source - 1] > 0)
			return shortest[destination - 1][source - 1];
		graph->resetVisited();
		DFS(source, destination);
		return result;
	};
	
	bool DFS(int source, int destination) {
		
		if(source == destination) {
			return true;
		}
		
		Node* node = graph->getNode(source);
		node->visited = true;
		
		std::vector<Edge>* adjacent = graph->getAdjacent(node->getIndex());
		if(adjacent == 0) {
			return false;
		}
		
		for (std::vector<Edge>::iterator it = adjacent->begin(); it < adjacent->end(); ++it) {
		
			Node* adj = graph->getNode((*it).to);
			if(!adj->visited) {
				result += (*it).weight;
				
				shortest[start - 1][source - 1] = result;
				shortest[source - 1][start - 1] = result;
				
				shortest[(*it).to - 1][source - 1] = (*it).weight;
				shortest[source - 1][(*it).to - 1] = (*it).weight;

				if(DFS((*it).to, destination)) {
					return true;
				}
				result -= (*it).weight;
			}
			
		}
		
		return false;
	};
};

int main (int argc, char * const argv[]) {
	
	std::string line;
	// get vertices count
	getline(std::cin, line, '\n');
	int vertices = atoi(line.c_str());
	std::cerr << "Vertices: " << vertices << std::endl;
	
	// get edges
	Graph* graph = new Graph(vertices);

	for(int i = 0; i < vertices - 1; i++){
		getline(std::cin, line, '\n');
		int f, t, w;
		sscanf(line.c_str(), "%i %i %i\n", &f, &t, &w);
		graph->addEdge(f, t, w);
	}
	Pathfinder pathfinder(graph);
	
	// get pairs count
	getline(std::cin, line, '\n');
	int pairs_count = atoi(line.c_str());
	std::cerr << "Pairs: " << pairs_count << std::endl;
	
	// get pairs
	for(int i = 0; i < pairs_count; i++){
		getline(std::cin, line, '\n');
		int f, t;
		sscanf(line.c_str(), "%i %i\n", &f, &t);
		
		int path = pathfinder.findShortest(f, t);
		std::cout << path << std::endl;
	}
	
	delete graph;
	graph = 0;
	
    return 0;
}
