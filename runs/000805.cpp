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
		void makeRound(unsigned int node, unsigned int rootNode);
};

Graph::Graph(std::vector<std::vector<Edge> >* g)
{
	tree = *g;
	round.reserve(3*tree.size());
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
	std::vector<bool> pathCostUsed;
	int n = tree.size();
	int m = round.size();
	int a,b,i;
	unsigned int result_cost = 0;
	pathCostUsed.resize(n);
	pathCostUsed.assign(n,false);
	//decide which node is first presented
	for(i = 0; i < m; i++)
	{
		if(round[i] == node1 - 1)
		{
			a = node1 - 1;
			b = node2 - 1;
			break;
		}
		if(round[i] == node2 - 1)
		{
			b = node1 - 1;
			a = node2 - 1;
			break;
		}
	}
	pathCostUsed[a] = true;
	int temp1, temp2;
	temp1 = a;
	for(i += 1; i < m; i++)
	{
		bool found = false;
		temp2 = round[i];
		/* going thru edges to find connecting temp1 and temp2
		 * if one of them hasn't been used before add edge's
		 * weight 
		 */
			for(unsigned int s = 0; s < tree[temp1].size(); s++)
			{
				if (temp2 == tree[temp1][s].getLast())
				{
					if(pathCostUsed[temp2] == false)
					{
						result_cost += tree[temp1][s].getWeight();
						pathCostUsed[temp2] = true;
					}
					else
						result_cost -= tree[temp1][s].getWeight();
					found = true;
					break;
				}
			}
		if (found != true)
		{
			for(unsigned int s = 0; s < tree[temp2].size(); s++)
			{
					if (temp1 == tree[temp2][s].getLast())
					{
						if(pathCostUsed[temp2] == false)
						{
							result_cost += tree[temp2][s].getWeight();
							pathCostUsed[temp2] = true;
						}
						else
							result_cost -= tree[temp2][s].getWeight();
						break;
					}
			}
		}
		if(temp2 == b)
			break;
		temp1 = round[i];
	}
	return result_cost;
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
		f = 0;
		l = 0;
		w = 0;
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
		int firstNode, lastNode;
		scanf("%d %d",&firstNode,&lastNode);
		costs.push_back(gr->getPathCost(firstNode,lastNode));
	}
	delete gr;
	//Outputting results
	for(unsigned int f = 0; f < costs.size(); f++)
	{
		printf("%d\n",costs[f]);
	}
	return 0;
}

