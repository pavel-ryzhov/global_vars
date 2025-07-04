#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::swap;
using std::map;
using std::pair;

int dsu_get (int vertex, vector<int>& dsu) {
	return vertex == dsu.at(vertex) ? vertex : dsu.at(vertex) = dsu_get (dsu.at(vertex), dsu);
}

void dsu_unite (int vertexA, int vertexB, int new_ancestor, vector<int>& dsu, vector<int>& ancestors) {
	vertexA = dsu_get (vertexA, dsu);
	vertexB = dsu_get (vertexB, dsu);
	if (rand() & 1)  swap (vertexA, vertexB);
	dsu.at(vertexA) = vertexB,  ancestors.at(vertexB) = new_ancestor;
}

void dfs (int vertex, vector<map<int,int> >& queries, vector<int>& dsu, vector<bool>& usedVertexes,
	vector<int>& ancestors, vector<int>& vertexesHeights, const vector<vector<int> >& graph, const vector<int>& edgesWeights, int vertexWeight = 0) {
	dsu.at(vertex) = vertex;
	ancestors.at(vertex) = vertex;
	vertexesHeights.at(vertex) = vertexWeight;
	usedVertexes.at(vertex) = true;
	for (int index = 0; index < graph.at(vertex).size(); ++index) {
		if (!usedVertexes.at(graph.at(vertex).at(index))) {
			dfs(graph.at(vertex).at(index), queries, dsu, usedVertexes, 
				ancestors, vertexesHeights, graph, edgesWeights,  vertexWeight + edgesWeights.at(graph.at(vertex).at(index)));
			dsu_unite (vertex, graph.at(vertex).at(index), vertex, dsu, ancestors);
		}
	}
	map<int, int>::iterator queriesIterator;
	for (queriesIterator = queries.at(vertex).begin(); queriesIterator != queries.at(vertex).end(); ++queriesIterator) {
		if (usedVertexes.at((*queriesIterator).first)) {
			int ancestorVertex = ancestors.at(dsu_get((*queriesIterator).first, dsu));
			int pathLength = abs(vertexesHeights[vertex]-vertexesHeights[ancestorVertex])+abs(vertexesHeights[(*queriesIterator).first]-vertexesHeights[ancestorVertex]);
			int visitedVertex = (*queriesIterator).first;
			queries.at(vertex)[visitedVertex] = pathLength;
			queries.at(visitedVertex)[vertex] = pathLength;
		}
	}
}

void Input(vector<vector<int> >& graph, vector<map<int,int> >& queries, vector<int>& edgesWeights, 
	vector<pair<int,int> >& orderedQueries, vector<int>& vertexesHeights, vector<bool>& usedVertexes, vector<int>& ancestors, vector<int>& dsu)
{
	int vertexesCount;
	cin >> vertexesCount;
	graph.resize(vertexesCount);
	queries.resize(vertexesCount);
	edgesWeights.resize(vertexesCount,0);
	vertexesHeights.resize(vertexesCount);
	usedVertexes.resize(vertexesCount);
	ancestors.resize(vertexesCount);
	dsu.resize(vertexesCount);
	for (int index = 0; index < vertexesCount - 1; ++index) {
		int edgeStart, edgeEnd, edgeWeight;
		cin >> edgeStart;
		cin >> edgeEnd;
		cin >> edgeWeight;
		graph.at(edgeStart - 1).push_back(edgeEnd - 1);
		graph.at(edgeEnd - 1).push_back(edgeStart - 1);
		if (edgesWeights.at(edgeEnd - 1) == 0) {
			edgesWeights.at(edgeEnd - 1) = edgeWeight;
		}
		else if(edgesWeights.at(edgeStart - 1) == 0) {
			edgesWeights.at(edgeStart - 1) = edgeWeight;
		}
	}
	int queriesCount;
	cin >> queriesCount;
	for ( int index = 0; index < queriesCount; ++index) {
		int vertexA, vertexB;
		cin >> vertexA;
		cin >> vertexB;
		queries.at(--vertexA)[--vertexB] = 0;
		queries.at(vertexB)[vertexA] = 0;
		orderedQueries.push_back(pair<int, int>(vertexA, vertexB));
	}
}

void Output(const vector<pair<int,int> >& orderedQueries, const vector<map<int, int> >& queries)
{
	for (int index = 0; index < orderedQueries.size(); ++index) {
		map<int, int>::const_iterator queriesIterator = queries.at(orderedQueries.at(index).first).find(orderedQueries.at(index).second);
		if (queriesIterator != queries.at(orderedQueries.at(index).first).end()) {
			cout << (*queriesIterator).second << endl;
		}
	}
}

int main() {
	vector<vector<int> > graph;
	vector<map<int,int> > queries;
	vector<pair<int,int> > orderedQueries;
	vector<int> dsu;
	vector<int> edgesWeghts;
	vector<int> vertexesHeights;
	vector<int> ancestors;
	vector<bool> usedVertexes;

	Input(graph, queries, edgesWeghts, orderedQueries, vertexesHeights, usedVertexes, ancestors, dsu);
	dfs(0, queries, dsu, usedVertexes, ancestors, vertexesHeights, graph, edgesWeghts);
	Output(orderedQueries,queries);
}