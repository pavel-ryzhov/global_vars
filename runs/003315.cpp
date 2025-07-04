#include <iostream>
#include <vector>
#include <map>
#include <math.h>

using std::vector;
using std::map;
using std::pair;
using std::cout;
using std::cin;
using std::endl;

// We're using global variables, because using them as functions parameters
// makes functions too "heavy". As our task is quite simple, it's not
// such a big problem (I suppose :))
vector<vector<int> > graph;
vector<bool> usedVerticies;
vector<int> verticiesInDFSTime, verticiesOutDFSTime;
vector<vector<int> > ancestors;
vector<map<int, int> > edges;
vector<int> verticiesHeights;
vector<pair<int, int> > queries;
int timer;
int treeHeight;

void Dfs (int vertex, int parentVertex = 0) {
	verticiesHeights[vertex] = edges[vertex][parentVertex] + verticiesHeights[parentVertex];
	usedVerticies[vertex] = true;
	verticiesInDFSTime[vertex] = ++timer;
	ancestors[vertex][0] = parentVertex;
	for (int index = 1; index <= treeHeight; ++index) {
		ancestors[vertex][index] = ancestors[ancestors[vertex][index-1]][index-1];
	}
	for (int index = 0; index < graph[vertex].size(); ++index) {
		int toVertex = graph[vertex][index];
		if (!usedVerticies[toVertex]) {
			Dfs (toVertex, vertex);
		}
	}
	verticiesOutDFSTime[vertex] = ++timer;
}

bool Upper (int vertexA, int vertexB) {
	return (verticiesInDFSTime[vertexA] <= verticiesInDFSTime[vertexB] && verticiesOutDFSTime[vertexB] <= verticiesOutDFSTime[vertexA]);
}

int Lca (int vertexA, int vertexB) {
	if (Upper(vertexA, vertexB)) {
		return vertexA;
	}
	if (Upper(vertexB, vertexA)) {
		return vertexB;
	}
	for (int index = treeHeight; index >= 0; --index) {
		if (!Upper(ancestors[vertexA][index], vertexB)) {
			vertexA = ancestors[vertexA][index];
		}
	}
	return ancestors[vertexA][0];
}

void Input()
{
	int verticiesCount;
	cin >> verticiesCount;
	treeHeight = log(double(verticiesCount))/log(2.0) + 1;
	timer = 0;
	graph.resize(verticiesCount);
	edges.resize(verticiesCount);
	usedVerticies.resize(verticiesCount);
	verticiesInDFSTime.resize(verticiesCount);
	verticiesOutDFSTime.resize(verticiesCount);
	ancestors.resize(verticiesCount);
	verticiesHeights.resize(verticiesCount, 0);
	for ( int index = 0; index < verticiesCount; ++index) {
		ancestors[index].resize(treeHeight + 1);
	}
	for (int index = 0; index < verticiesCount - 1; ++index) {
		int edgeStart, edgeEnd, edgeWeight;
		cin >> edgeStart;
		cin >> edgeEnd;
		cin >> edgeWeight;
		graph[edgeStart - 1].push_back(edgeEnd - 1);
		graph[edgeEnd - 1].push_back(edgeStart - 1);
		edges[edgeStart - 1][edgeStart - 1] = 0;
		edges[edgeEnd - 1][edgeEnd - 1] = 0;
		edges[edgeStart - 1][edgeEnd - 1] = edgeWeight;
		edges[edgeEnd - 1][edgeStart - 1] = edgeWeight;
	}
	int queriesCount;
	cin >> queriesCount;
	for (int index = 0; index < queriesCount; ++index) {
		int vertexA, vertexB;
		cin >> vertexA;
		cin >> vertexB;
		queries.push_back(pair<int, int>(--vertexA, --vertexB));
	}
}

void Output()
{
	for (int index = 0; index < queries.size(); ++index) {
		int vertexA = queries.at(index).first;
		int vertexB = queries.at(index).second;
		int ancestor = Lca(vertexA, vertexB);
		cout << verticiesHeights.at(vertexA) + verticiesHeights.at(vertexB) - 2*verticiesHeights.at(ancestor) << endl;
	}
}

int main() {
	Input();
	Dfs(0);
	Output();
}