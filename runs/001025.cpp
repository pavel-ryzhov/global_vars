#include <iostream>
#include <vector>

using namespace std;

typedef unsigned short ushort;

bool search;

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

void route(ushort start, ushort finish, vector<node> nodes, ushort lenght, vector<ushort> prevs)
{
	if (start == finish)
	{
		cout<<lenght<<endl;
		return;
	}
	vector<edge> cur = nodes[start-1].edges;

	//for (int i=0; i<cur.size(); i++)
	//	cout<<cur[i].anotherNode<<" "<<cur[i].lenght<<" -n ";
	for (ushort i = 0; i<cur.size(); ++i)
	{
		bool isPrev = false;
		for (int p=0; p<prevs.size(); p++)
			if (cur[i].anotherNode == prevs[p])
				isPrev = true;
		if (!isPrev)
		{
			
			if (cur[i].anotherNode == finish)
			{
				cout<< lenght + cur[i].lenght<<endl;
				search = false;
				return;
			}
			else
			{
				prevs.push_back(start);
				ushort templenght = cur[i].lenght + lenght;
				if (search) 
					route(cur[i].anotherNode, finish, nodes, templenght, prevs);
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
/*
	for (int i = 0; i<nodes.size(); i++)
	{
		for (int j = 0; j<nodes[i].edges.size(); j++)
			cout<<nodes[i].edges[j].anotherNode<<" "<<nodes[i].edges[j].lenght<<endl;
		cout<<endl;
	}
*/
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
	{
		vector<ushort> prevs;
		search = true;
		route(ways[i].start, ways[i].finish, nodes, 0, prevs);
	}

	return 0;
}

