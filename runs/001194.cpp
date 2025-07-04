#include <stdio.h>
#include <vector>

using namespace std;

#define MAXNUM 40000

int nodeNum;

struct fork
{
	unsigned short node;
	unsigned short direct;
};

vector<vector<fork> > allForks;

void my_deixtra(int start, unsigned short ** source, unsigned short * dest, unsigned short lenght, int prev, vector<fork> forks)
{
	allForks[start-1] = forks;
	unsigned short * node = *(source+start-1);
	int edges = 0;
	for (register int i = 0; i < nodeNum; ++i)
		if (i+1 != prev)
		{
			if (*(node+i) != 50000)
				edges++;
			if (edges > 1)
				break;
		}
	for (register int i = 0; i < nodeNum; ++i)
		if (i+1 != prev)
		{
			if (*(node+i) != 50000)
			{
				vector<fork> tempForks = forks;
				if (edges > 1)
				{
					fork tempFork;
					tempFork.node = start;
					tempFork.direct = i+1;
					
					tempForks.push_back(tempFork);
				}
				unsigned short templenght = *(node+i)+lenght;
				dest[i] = templenght;
				my_deixtra(i+1, source, dest, templenght, start, tempForks);	
			}
		}

}

int my_route(int start, int finish, unsigned short * lenghts)
{
	for (int i = allForks[start-1].size()-1; i > -1; --i)
		for (int j = allForks[finish-1].size()-1; j > -1; --j)
			if (allForks[start-1][i].node == allForks[finish-1][j].node)
			{
				if (allForks[start-1][i].direct == allForks[finish-1][j].direct)
				{
					if (lenghts[start-1]-lenghts[finish-1] > 0)
						return lenghts[start-1]-lenghts[finish-1];
					else
						return lenghts[finish-1]-lenghts[start-1];
				}
				else
					return lenghts[start-1]+lenghts[finish-1]-2*lenghts[allForks[start-1][i].node-1];
					
			}
	if (lenghts[start-1]-lenghts[finish-1] > 0)
		return lenghts[start-1]-lenghts[finish-1];
	else
		return lenghts[finish-1]-lenghts[start-1];
}

int main()
{

	scanf("%d", &nodeNum);

	unsigned short ** nodes  = new unsigned short *[nodeNum];
	for (int i = 0; i < nodeNum; ++i)
	{
		*(nodes+i)  = new unsigned short [nodeNum];
		for (int j = 0; j < nodeNum; ++j)
			nodes[i][j]  = 50000;
	}

	int node1, node2, lenght;
	for (int i = nodeNum - 1; i; --i)
	{
		scanf("%d %d %d", &node1, &node2, &lenght);
		nodes[node1-1][node2-1] = lenght;
		nodes[node2-1][node1-1] = lenght;
	}

	unsigned short * nodes2  = new unsigned short [nodeNum];
	for (int i = 0; i < nodeNum; ++i)
		nodes2[i]  = -1;
	nodes2[0] = 0;

	allForks.resize(nodeNum);
	vector<fork> forks;
	my_deixtra(1, nodes, nodes2, 0, 0, forks);

	delete [] nodes;

	int wayNum;
	scanf("%d", &wayNum);

	for (int i = 0; i < wayNum; ++i)
	{
		register int start;
		register int finish;
		scanf("%d %d", &start, &finish);
		
		if (start == finish)
			printf("0\n");
		else
			printf("%d\n", my_route(start, finish, nodes2));

	}

	return 0;
}

