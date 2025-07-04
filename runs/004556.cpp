/*
 * shortpath2.cpp
 *
 *  Created on: 03.03.2011
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
typedef map <uint, uint> TMatrixRow;
typedef vector <TMatrixRow> TMatrix;

// Structure where all data keeps
struct TGraph {
	uint vertexCount; // vertex count
	TMatrix edge; // adjacency matrix (sparse)
	uint *height; // height of n-th vertex is a count of edges between him and root
	uint *parent;
	~TGraph();
	const bool next(uint vertexA, uint &vertexB);
	void read();
	void prepocess();
	void dfs(uint vertexA);
	const uint path(uint vertexA, uint vertexB);
};

// reads graph from stdin using template "FROM TO WEIGHT"
void TGraph::read() {
	// read vertex count
	cin >> vertexCount;

	// initialize arrays
	height = new uint[vertexCount];
	parent = new uint[vertexCount];
	edge.resize(vertexCount);

	// input edges to adjacency matrix
	uint from, to, weight;
	for (uint i = 0; i < vertexCount-1; i++) {
		cin >> from >> to >> weight;
		edge[from-1][to-1] = weight;
		edge[to-1][from-1] = weight;
	}
}

TGraph::~TGraph() {
	delete[] height;
	delete[] parent;
}

// Returns true, if there is once more edge from vertexA besides [vertexA, vertexB] and previous.
// Returns false if none
// If vertexB == vertexA tries to find the first one.
const bool TGraph::next(uint vertexA, uint &vertexB) {
	TMatrixRow ::iterator ptr;
	if (vertexB == vertexA)
		ptr = edge[vertexA].begin();
	else
		ptr = ++(edge[vertexA].find(vertexB));

	if (ptr == edge[vertexA].end())
		return false;
	else {
		vertexB = ptr->first;
		if (vertexB == parent[vertexA])
			return next (vertexA, vertexB);
		return true;
	}
}

// DFS step
// Calculate vertex's height and recursively do it with all its children
void TGraph::dfs (uint vertexA) {
	height[vertexA] = height[parent[vertexA]] + 1;
	uint vertexB = vertexA;
	while (next(vertexA, vertexB)) {
		parent[vertexB] = vertexA;
		dfs(vertexB);
	}
}

// Graph preprocessing
// The goal is mark height and parent to each vertex
void TGraph::prepocess() {
	height[0] = 0;
	uint vertexB = 0;
	while (next(0, vertexB)) {
		parent[vertexB] = 0;
		dfs(vertexB);
	}
}

// swap a and b
inline void swap (uint &a, uint &b) {
	uint c  = a;
	a = b;
	b = c;
}

// returns path from vertexA to vertexB in dfs-proceed tree
const uint TGraph::path(uint vertexA, uint vertexB) {
	uint result = 0;
	if (height[vertexA] < height[vertexB])
		swap (vertexA, vertexB);
	while (height[vertexA] != height[vertexB]) {
		result += edge[vertexA][parent[vertexA]];
		vertexA = parent[vertexA];
	}
	while (vertexA != vertexB) {
		result += edge[vertexA][parent[vertexA]] + edge[vertexB][parent[vertexB]];
		vertexA = parent[vertexA];
		vertexB = parent[vertexB];
	}
	return result;
}

// main cycle
// reads two vertexes, returns path between them
void answer (TGraph &graph) {
	int answersCount, vertexA, vertexB;
	cin >> answersCount;
	for (int i = 0; i < answersCount; i++) {
		cin >> vertexA >> vertexB;
		cout << graph.path (vertexA - 1, vertexB - 1) << endl;
	}
}

int main(void) {
	TGraph graph;
	graph.read();
	graph.prepocess();
	answer(graph);
	return 0;
}
