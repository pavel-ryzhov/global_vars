#include <iostream>
#include <vector>

#define MAXNUM 40000

using namespace std;

bool search;
int nodeNum;


void route(int start, int finish, int ** nodes, register int lenght, int prev)
{
	if (start == finish)
	{
		cout<<lenght<<endl;
		return;
	}

	if (nodes[start-1][finish-1] != -1)
	{

		cout<< lenght + nodes[start-1][finish-1]<<endl;
		search = false;
		return;
	}
	for (int i = 0; i < nodeNum; ++i)
	{
		if (nodes[start-1][i] != -1)
		{
			if (i+1 != prev)
			{
				int templenght = nodes[start-1][i] + lenght;

				if (search) 
					 route(i+1, finish, nodes, templenght, start);
			}
		}
	}
}

int main()
{
	
	cin >> nodeNum;

	int ** nodes  = new int *[nodeNum];
	for (int i = 0; i < nodeNum; ++i)
		nodes[i]  = new int [nodeNum];

	for (int i = 0; i < nodeNum; ++i)
		for (int j = 0; j < nodeNum; ++j)
			nodes[i][j]  = -1;

	int node1, node2, lenght;
	for (int i = nodeNum - 1; i; --i)
	{
		cin >> node1 >> node2 >> lenght;
		nodes[node1-1][node2-1] = lenght;
		nodes[node2-1][node1-1] = lenght;
	}

	int wayNum;
	cin >> wayNum;

	register int start, finish;

	for (int i = 0; i < wayNum; ++i)
	{
		cin >> start >> finish;
		search = true;	
		
		route(start, finish, nodes, 0, 0);
	}
	return 0;
}

