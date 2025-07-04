#include <iostream>
#include <vector>

#define MAXNUM 40000

using namespace std;

bool search;
int nodeNum;
vector<int> trueWay;


void route(int start, int finish, int ** nodes, int ** nodes2, register int lenght, vector<int> marshroute)
{
	if (start == finish)
	{
		cout<<lenght<<endl;
		return;
	}

	if (nodes[start-1][finish-1] != -1)
	{
		trueWay = marshroute;

		cout<< lenght + nodes[start-1][finish-1]<<endl;
		search = false;
		return;
	}
	if (nodes2[start-1][finish-1] != -1)
	{
		trueWay = marshroute;

		cout<< lenght + nodes2[start-1][finish-1]<<endl;
		search = false;
		return;
	}
	for (int i = 0; i < nodeNum; ++i)
	{
		if (nodes[start-1][i] != -1)
		{
			bool isPrev = false;
			for (int p=0; p<marshroute.size(); p++)
				if (i+1 == marshroute[p])
					isPrev = true;
			if (!isPrev)
			{
				vector<int> tempmarshroute = marshroute;
				tempmarshroute.push_back(start);

				int templenght = nodes[start-1][i] + lenght;

				if (search) 
					 route(i+1, finish, nodes, nodes2, templenght, tempmarshroute);
			}
		}
	}
}

int main()
{
	
	cin >> nodeNum;

	int ** nodes  = new int *[nodeNum];
	int ** nodes2 = new int *[nodeNum];
	for (int i = 0; i < nodeNum; ++i)
	{
		nodes[i]  = new int [nodeNum];
		nodes2[i] = new int [nodeNum];
	}

	for (int i = 0; i < nodeNum; ++i)
		for (int j = 0; j < nodeNum; ++j)
		{
			nodes[i][j]  = -1;
			nodes2[i][j] = -1;
		}

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
		route(start, finish, nodes, nodes2, 0, trueWay);

		if (trueWay.size()>2)
		{
			for (int j = 0; j<trueWay.size()-2; j++)
			{
				for (int k = j+2; k<trueWay.size(); k++)
				{
					nodes2[trueWay[j]-1][trueWay[k]-1] = 0;
					for (int p = j; p < k; p++)
						nodes2[trueWay[j]-1][trueWay[k]-1] += nodes[trueWay[p]-1][trueWay[p+1]-1];
				
					nodes2[trueWay[k]-1][trueWay[j]-1] = nodes2[trueWay[j]-1][trueWay[k]-1];

				}
			}
		}

		trueWay.clear();
	}
	return 0;
}

