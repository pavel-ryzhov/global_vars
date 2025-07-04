#include <stdio.h>
#include <vector>

class Edge {
	// Egde class represents edge of graph
	public:
		unsigned int getFirst(){
			return first;
		};
		unsigned int getLast(){
			return last;
		};
		unsigned int getWeight(){
			return weight;
		};
		Edge(unsigned int f,unsigned int l,unsigned int w);
	private:
		unsigned int first;
		unsigned int last;
		unsigned int weight;
};



Edge::Edge(unsigned int f, unsigned int l, unsigned int w){
	first = f - 1;
	last = l - 1;
	weight = w;
}

class Graph 
{
	//Graph class represents graph structure
	public:
		unsigned int getPathCost(unsigned int node1, unsigned int node2);
		Graph(std::vector<std::vector<Edge> > *g);
		//~Graph();
	private:
		std::vector<std::vector<Edge> > tree;
		std::vector<unsigned int> round;
		std::vector<bool> roundUsed;
		std::vector<unsigned int> path;
		void makeRound(unsigned int node, unsigned int rootNode);
		std::pair<unsigned int, unsigned int> getPath(unsigned int node1, unsigned int node2);
};

Graph::Graph(std::vector<std::vector<Edge> >* g)
{
	tree = *g;
	round.reserve(3*tree.size());
	path.reserve(tree.size());
	roundUsed.resize(tree.size(),false);
	const unsigned int root = 0;
	makeRound(root,root);

}

/*
Graph::~Graph()
{
	tree.clear();
	round.clear();
	//roundUsed.clear();
};
*/

void Graph::makeRound(unsigned int node, unsigned int rootNode)
{
	//makeRound function makes round thru the graph,
	//going recursively
	round.push_back(node);
	roundUsed[node] = true;
	for (unsigned int i = 0; i < tree[node].size(); i++)
	{
		if (roundUsed[tree[node][i].getLast()] != true && tree[node][i].getLast() != rootNode)
		{
			makeRound(tree[node][i].getLast(),rootNode);
			round.push_back(node);
		}
	}
}

unsigned int Graph::getPathCost(unsigned int node1, unsigned int node2)
{
	//getPathCost function computes path cost from node1
	//to node2
	if (node1 == node2)
		return 0;

	int n = tree.size();
	unsigned int result_cost = 0;
	unsigned int a,b;
	std::pair<unsigned int, unsigned int> arrangedNodes = getPath(node1,node2);
	int m = path.size();
	a = arrangedNodes.first;
	b = arrangedNodes.second;
	int temp1, temp2;
	temp1 = a;
	for(int i = 1; i < m; i++)
	{
		temp2 = path[i];
		/* going thru edges to find connecting temp1 and temp2
		 * if one of them hasn't been used before add edge's
		 * weight 
		 */
			for(unsigned int s = 0; s < tree[temp1].size(); s++)
			{
				if (temp2 == tree[temp1][s].getLast())
				{
						result_cost += tree[temp1][s].getWeight();
						break;
				}
			}
		if(temp2 == b)
			break;
		temp1 = path[i];
	}
	return result_cost;
}

std::pair<unsigned int,unsigned int> Graph::getPath(unsigned int node1, unsigned int node2)
{

	int a,b,i;
	int m = round.size();
	//decide which node is first presented
	for (i = 0; i < m; i++)
	{
		if (round[i] == node1 - 1)
		{
			a = node1 - 1;
			b = node2 - 1;
			break;
		}
		if (round[i] == node2 - 1)
		{
			b = node1 - 1;
			a = node2 - 1;
			break;
		}
	}
	path.clear();
	path.push_back(a);
	path.push_back(round[i + 1]);
	if (path[1] == b)
		return std::make_pair<unsigned int, unsigned int>(a,b);
	for (i += 2; i < m; i++)
	{
		if (round[i] == path[path.size() - 2])
			path.pop_back();
		else
		{
			path.push_back(round[i]);
			if (round[i] == b)
				break;
		}
	}
	return std::make_pair<unsigned int, unsigned int>(a,b);
}

int main()
{
	int N,M;
	std::vector<std::vector<Edge> > tempTree;
	std::vector<Edge> children;
	std::vector<unsigned int> costs;

	//Scanning input for graph definition
	scanf("%d\n",&N);
	children.clear();
	for (int i = 0; i < N; i++)
	{
		tempTree.push_back(children);
	}
	for(int i = 1; i < N; i++)
	{
		unsigned int f,l,w;
		scanf("%u %u %u\n",&f,&l,&w);
		Edge* tempNode = new Edge(f,l,w);
		tempTree[f - 1].push_back(*tempNode);
		delete tempNode;
		tempNode = new Edge(l,f,w);
		tempTree[l - 1].push_back(*tempNode);
		delete tempNode;
	}
	Graph* gr = new Graph(&tempTree);

	//Scanning input for nodes
	
	scanf("%d",&M);
	for(int j = 0; j < M; j++)
	{
		unsigned int firstNode, lastNode;
		scanf("%u %u",&firstNode,&lastNode);
		costs.push_back(gr->getPathCost(firstNode,lastNode));
	}
	delete gr;
	//Outputting results
	for(unsigned int f = 0; f < costs.size(); f++)
	{
		printf("%u\n",costs[f]);
	}
	return 0;
}

