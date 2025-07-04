#include <stdio.h>
#include <vector>

using namespace std;

#define MAXNUM 40000
;
unsigned short nodeNum;


struct fork
{
	unsigned short node;
	unsigned short direct;
};

vector<vector<fork> > allForks;

void my_deixtra(unsigned short  start, unsigned short  ** source, int * dest, int lenght, unsigned short  prev, vector<fork> forks)
{
	allForks[start-1] = forks;
	int edges = 0;
	for (register unsigned short  i = 0; i < nodeNum; ++i)
		if (i+1 != prev)
		{
			if (*(*(source+start-1)+i) != 50000)
				edges++;
			if (edges > 1)
				break;
		}
	for (register unsigned short  i = 0; i < nodeNum; ++i)
		if (i+1 != prev)
		{
			if (*(*(source+start-1)+i) != 50000)
			{
				vector<fork> tempForks = forks;
				if (edges > 1)
				{
					fork tempFork;
					tempFork.node = start;
					tempFork.direct = i+1;
					
					tempForks.push_back(tempFork);
				}
				int templenght = (*(*(source+start-1)+i)+lenght);
				dest[i] = templenght;
				my_deixtra(i+1, source, dest, templenght, start, tempForks);	
			}
		}

}

int my_route(unsigned short  start, unsigned short  finish, int * lenghts)
{
	for (unsigned short  i = allForks[start-1].size()-1; i > -1; --i)
		for (unsigned short  j = allForks[finish-1].size()-1; j > -1; --j)
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

	scanf("%u", &nodeNum);

	unsigned short  ** nodes  = new unsigned short  *[nodeNum];
	for (unsigned short  i = 0; i < nodeNum; ++i)
	{
		*(nodes+i)  = new unsigned short  [nodeNum];
		for (unsigned short  j = 0; j < nodeNum; ++j)
			nodes[i][j]  = 50000;
	}

	unsigned short  node1, node2, lenght;
	for (unsigned short  i = nodeNum - 1; i; --i)
	{
		scanf("%u %u %u", &node1, &node2, &lenght);
		nodes[node1-1][node2-1] = lenght;
		nodes[node2-1][node1-1] = lenght;
	}

	int * nodes2  = new int [nodeNum];
	for (unsigned short  i = 0; i < nodeNum; ++i)
		nodes2[i]  = 50000;
	nodes2[0] = 0;

	allForks.resize(nodeNum);
	vector<fork> forks;
	my_deixtra(1, nodes, nodes2, 0, 0, forks);

	delete [] nodes;

	unsigned short  wayNum;
	scanf("%u", &wayNum);

	for (unsigned short  i = 0; i < wayNum; ++i)
	{
		register unsigned short  start;
		register unsigned short  finish;
		scanf("%u %u", &start, &finish);
		
		if (start == finish)
			printf("0\n");
		else
			printf("%d\n", my_route(start, finish, nodes2));

	}

	return 0;
}

