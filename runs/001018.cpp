#include <iostream>
#include <vector>

using namespace std;

typedef unsigned short ushort;

struct edge
{
	ushort anotherNode;
	ushort lenght;
};

struct node
{
	vector <edge> edges;
};

struct way
{
	ushort start;
	ushort finish;
};

void route(ushort start, ushort finish, vector<node> nodes, ushort lenght, ushort prev)
{
	vector<edge> cur = nodes[start-1].edges;
	for (ushort i = 0; i<cur.size(); ++i)
	{
		if (cur[i].anotherNode != prev)
		{
			if (cur[i].anotherNode == finish)
			{
				cout<< lenght + cur[i].lenght<<endl;
			}
			else
			{
				prev = start;
				ushort templenght = cur[i].lenght + lenght;
				route(cur[i].anotherNode, finish, nodes, templenght, prev);
			}
		}
	}
}

int main()
{
	vector<node> nodes;
	
	ushort nodeNum;
	cin >> nodeNum;

	nodes.resize(nodeNum);
	ushort node1, node2, lenght;
	edge tempEdge;
	for (ushort i = nodeNum - 1; i; --i)
	{
		cin >> node1 >> node2 >> lenght;
		
		tempEdge.lenght = lenght;
		tempEdge.anotherNode = node2;
		nodes[node1-1].edges.push_back(tempEdge);
		tempEdge.anotherNode = node1;
		nodes[node2-1].edges.push_back(tempEdge);

	}

	ushort wayNum;
	cin >> wayNum;
	way tempWay;
	vector<way> ways;
	for (ushort i = wayNum; i; --i)
	{
		cin >> tempWay.start >> tempWay.finish;
		ways.push_back(tempWay);
	}

	for (ushort i = 0; i<ways.size(); ++i)
		route(ways[i].start, ways[i].finish, nodes, 0, 0);

	return 0;
}

