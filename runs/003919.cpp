#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Edge
{
	int nodeNumber;
	int lenght;
public:
	Edge(int nodeNumber, int lenght);
	int GetNodeNumber() const;
	int GetLenght() const;
};

class Node
{
	vector<Edge> incidentList;
public:
	void AddEdge(int nodeNumber, int lenght);
	const vector<Edge> &GetIncidentList() const;
};

class Graph
{
	vector<Node> nodes;
public:
	Graph(int nodesCount);
	void AddEdge(int node1, int node2, int lenght);
	int NodesCount() const;
	const Node &GetNode(int nodeNumber) const;
};

class NodesPair
{
	int node1;
	int node2;
	int distance;
public:
	NodesPair(int node1, int node2);
	void SetDistance(int distance);
	int GetDistance() const;
	int GetFirst() const;
	int GetSecond() const;
	int GetPairNode(int nodeNumber) const;
};

class PathFinder
{
	vector<bool> visited;
	vector<int> ansectors;
	vector<int> depths;
	vector<int> disjointSetUnion;
	vector< vector<NodesPair *> > ownPairsArr;

	const Graph *graph;
	int getTopElement(int node);
	void unite(int node1, int node2, int newAncestor);
	void depthFirstSearch(int currentNode, int parentNode, int edgeLenght);

public:
	PathFinder(const Graph *graph, vector<NodesPair> &nodesPairs);
	void FindPathLens();
};


Edge::Edge(int nodeNumber, int lenght)
{
	this->nodeNumber = nodeNumber;
	this->lenght = lenght;
}

int Edge::GetNodeNumber() const
{
	return this->nodeNumber;
}

int Edge::GetLenght() const
{
	return this->lenght;
}


void Node::AddEdge(int nodeNumber, int lenght)
{
	Edge edge(nodeNumber, lenght);
	this->incidentList.push_back(edge);
}

const vector<Edge> &Node::GetIncidentList() const
{
	return this->incidentList;
}


Graph::Graph(int nodesCount) : nodes(nodesCount)
{
}

int Graph::NodesCount() const
{
	return this->nodes.size();
}

void Graph::AddEdge(int node1, int node2, int lenght)
{
	this->nodes[node1-1].AddEdge(node2, lenght);
	this->nodes[node2-1].AddEdge(node1, lenght);
}

const Node &Graph::GetNode(int nodeNumber) const
{
	return this->nodes[nodeNumber - 1];
}


NodesPair::NodesPair(int node1, int node2)
{
	this->node1 = node1;
	this->node2 = node2;
}

void NodesPair::SetDistance(int distance)
{
	this->distance = distance;
}

int NodesPair::GetDistance() const
{
	return this->distance;
}

int NodesPair::GetFirst() const
{
	return this->node1;
}

int NodesPair::GetSecond() const
{
	return this->node2;
}

int NodesPair::GetPairNode(int nodeNumber) const
{
	if (nodeNumber == this->node1)
		return this->node2;
	else
		return this->node1;
}


PathFinder::PathFinder(const Graph *graph, vector<NodesPair> &nodesPairs) : visited(graph->NodesCount(), false), 
																			ansectors(graph->NodesCount()), 
																			depths(graph->NodesCount()),
																			ownPairsArr(graph->NodesCount()),
																			disjointSetUnion(graph->NodesCount())
{
	this->graph = graph;
	int nodesCount = graph->NodesCount();
	for (int i = 0; i < nodesPairs.size(); i++)
	{
		NodesPair *currentPair = &nodesPairs[i];
		int node1 = currentPair->GetFirst();
		int node2 = currentPair->GetSecond();
		this->ownPairsArr[node1 - 1].push_back(currentPair);
		this->ownPairsArr[node2 - 1].push_back(currentPair);
	}
	srand(time(0));
}

void PathFinder::FindPathLens()
{
	depthFirstSearch(1, 0, 0);
}

int PathFinder::getTopElement(int node)
{
	int nodeParent = this->disjointSetUnion[node - 1];
	if (nodeParent == node)
	{
		return node;
	}
	else
	{
		int ancestor = getTopElement(nodeParent);
		return ancestor;
	}
}

void PathFinder::unite(int node1, int node2, int newAncestor)
{
	node1 = this->getTopElement(node1);
	node2 = this->getTopElement(node2);

	if (rand() % 2 == 0)
	{
		int tmp = node1;
		node1 = node2;
		node2 = tmp;
	}

	this->disjointSetUnion[node1 - 1] = node2;
	this->ansectors[node2 - 1] = newAncestor;
}

void PathFinder::depthFirstSearch(int currentNode, int parentNode, int edgeLenght)
{
	if (parentNode != 0)
	{
		this->depths[currentNode - 1] = this->depths[parentNode - 1] + edgeLenght;
	}

	this->visited[currentNode - 1] = true;
	this->ansectors[currentNode - 1] = currentNode;
	this->disjointSetUnion[currentNode - 1] = currentNode;
	
	const vector<Edge> &incidentList = graph->GetNode(currentNode).GetIncidentList();
	int incidentCount = incidentList.size();
	for (int i = 0; i < incidentCount; i++)
	{
		const Edge &childEdge = incidentList[i];
		int childNode = childEdge.GetNodeNumber();
		if (!this->visited[childNode - 1])
		{
			depthFirstSearch(childNode, currentNode, childEdge.GetLenght());
			unite(currentNode, childNode, currentNode);
		}
	}

	vector<NodesPair *> &ownPairs = this->ownPairsArr[currentNode - 1];
	for (int i = 0; i < ownPairs.size(); i++)
	{
		int pairNode = ownPairs[i]->GetPairNode(currentNode);
		if (this->visited[pairNode - 1])
		{
			int LCA = this->ansectors[this->getTopElement(pairNode) - 1];
			int LCADepth = this->depths[LCA - 1];
			int currentNodeDepth = this->depths[currentNode - 1];
			int pairNodeDepth = this->depths[pairNode - 1];
			ownPairs[i]->SetDistance(currentNodeDepth + pairNodeDepth - 2 * LCADepth);
		}
	}
}			


int main()
{
	int nodesCount;
	int pairsCount;
	int node1;
	int node2;
	int edgeLenght;
	
	cin >> nodesCount;

	Graph graph(nodesCount);

	for (int edgeNumber = 1; edgeNumber <= nodesCount - 1; edgeNumber++)
	{
		cin >> node1;
		cin >> node2;
		cin >> edgeLenght;
		graph.AddEdge(node1, node2, edgeLenght);
	}

	cin >> pairsCount;
	vector<NodesPair> nodesPairs;

	for (int pairIndex = 0; pairIndex < pairsCount; pairIndex++)
	{
		cin >> node1;
		cin >> node2;
		NodesPair pair(node1, node2);
		nodesPairs.push_back(pair);
	}

	PathFinder pathFinder(&graph, nodesPairs);
	pathFinder.FindPathLens();

	for (int pairIndex = 0; pairIndex < pairsCount; pairIndex++)
	{
		int distance = nodesPairs[pairIndex].GetDistance();
		cout << distance << endl;
	}
	return 0;
}