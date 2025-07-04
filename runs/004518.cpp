/*
 * shortpath.cpp
 *
 *  Created on: 25.02.2011
 *      Author: cymkuh
 */

#include <iostream>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::map;

typedef unsigned int uint;
const uint MAXCOUNT = 40001; // by conditions, any numeral is 0<x<=40000

struct TGraph {
	uint vertexCount; // vertex count
	map <uint, map <uint, uint> > edges; // adjacency matrix
	uint *depth; // depth of n-th vertex
	vector <uint> dfsOrder; // order of passing in dfs algo; see below
	uint *dfsVisited; // first dfs visit step number; see below
	~TGraph();
	void read();
};

// reads graph from stdin using template "FROM TO WEIGHT"
void TGraph::read() {
	// read vertex count
	cin >> vertexCount;

	// initialize graph
	/*edges = new uint* [vertexCount];
	for (uint i = 0; i < vertexCount; i++)
		edges[i] = new uint[vertexCount];*/

	// prepare to dfs
	depth = new uint[vertexCount];
	dfsVisited = new uint[vertexCount];
	dfsOrder.reserve(vertexCount);

	// input edges to adjacency matrix
	uint from, to, weight;
	for (uint i = 0; i < vertexCount-1; i++) {
		cin >> from >> to >> weight;
		edges[from-1][to-1] = weight;
		edges[to-1][from-1] = weight;
	}
}

TGraph::~TGraph() {
	delete[] depth;
	dfsOrder.clear();
	delete[] dfsVisited;
	/*for (uint i = 0; i < vertexCount; i++)
		delete[] edges[i];
	delete[] edges;*/
}

// graph preprocessing - DFS
// the goal is to mark some properties of every vertex, such as
// 1. DFS order number ( dfsOrder[step_number] = vertex_number )
// 2. depth = path between 0st and this vertex. depth[n] = path from 0st to n-th
// 3. number of DFS step when this vertex was attended at first time
//                     ( dfsVisited[vertex_number] = step_number )
void dfs (TGraph &graph) {
	uint passed = 1; // current step number
	uint n = 0; // number of vertex which is currently proceed
	graph.dfsOrder.push_back(MAXCOUNT);

	while (true) {
		graph.dfsOrder.push_back(n);

		if (n == 0) {
			graph.depth[n] = 0;
			graph.dfsVisited[n] = 1;
		}

		if (graph.dfsVisited[n] == 0) {
			graph.dfsVisited[n] = passed;
			graph.depth[n] = graph.depth[graph.dfsOrder[passed - 1]] + graph.edges[n][graph.dfsOrder[passed - 1]];
		}

		for (uint i = 0; i < graph.vertexCount; i++)
			if ((graph.edges[n][i] !=0) && (graph.dfsVisited[i] == 0)) {
				n = i;
				break;
			}

		if (n == graph.dfsOrder[passed])
			n = graph.dfsOrder[graph.dfsVisited[n] - 1];

		if (n == MAXCOUNT)
			break;

		passed++;
	} // while
}

// swap a and b
inline void swap (uint &a, uint &b) {
	uint c  = a;
	a = b;
	b = c;
}

// find minimal G.depth on interval [vertexA, vertexB]
uint rmq (const TGraph &graph, uint vertexA, uint vertexB) {
	if (vertexA > vertexB)
		swap(vertexA, vertexB);
	uint parentVertex = vertexA;

	for (uint i = graph.dfsVisited[vertexA]; i <= graph.dfsVisited[vertexB]; i++)
		if (graph.depth[graph.dfsOrder[i]] < graph.depth[parentVertex])
			parentVertex = graph.dfsOrder[i];

	return graph.depth[parentVertex];
}

// returns path from vertexA to vertexB in dfs-proceed tree &graph
inline int path(const TGraph &graph, uint vertexA, uint vertexB) {
	return graph.depth[vertexA] + graph.depth[vertexB] - 2 * rmq (graph, vertexA, vertexB);
}

// main cycle
// reads two vertexes vertexA and vertexB
// returns path from vertexA to vertexB
void answer (const TGraph &graph) {
	int answersCount, vertexA, vertexB;
	cin >> answersCount;
	for (int i = 0; i < answersCount; i++) {
		cin >> vertexA >> vertexB;
		cout << path (graph, vertexA-1, vertexB-1) << endl;
	}
}

int main(void) {
	TGraph graph;
	graph.read();
	dfs(graph);
	answer(graph);
	return 0;
}
