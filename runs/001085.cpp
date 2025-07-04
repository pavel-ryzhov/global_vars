#include <stdio.h>

#define MAXNUM 40000

bool search;
int nodeNum;
int finish;


void route(register int start, int ** nodes, register int lenght, int prev)
{
	int * node = *(nodes+start-1);
	if (*(node+finish-1) != -1)
	{

		printf("%d\n", lenght + *(node+finish-1));
		search = false;
		return;
	}

	for (register int i = 0; i < nodeNum; ++i)
		if (*(node+i) != -1)
			if (i+1 != prev)
				if (search) 
					 route(i+1, nodes, *(node+i)+lenght, start);
}

int main()
{
	scanf("%d", &nodeNum);

	int ** nodes  = new int *[nodeNum];
	for (int i = 0; i < nodeNum; ++i)
	{
		*(nodes+i)  = new int [nodeNum];
		for (int j = 0; j < nodeNum; ++j)
			nodes[i][j]  = -1;
	}

	int node1, node2, lenght;
	for (int i = nodeNum - 1; i; --i)
	{
		scanf("%d %d %d", &node1, &node2, &lenght);
		nodes[node1-1][node2-1] = lenght;
		nodes[node2-1][node1-1] = lenght;
	}

	int wayNum;
	scanf("%d", &wayNum);

	for (int i = 0; i < wayNum; ++i)
	{
		register int start;
		scanf("%d %d", &start, &finish);
		search = true;	
		
		if (start == finish)
			printf("0\n");
		else
			route(start, nodes, 0, 0);
	}
	return 0;
}

