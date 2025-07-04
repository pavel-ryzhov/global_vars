#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <memory.h>

struct Node;

struct ChildLink
{
	Node *Child;
	ChildLink *NextChild;
};

struct Node
{
	int distToParent;
	int height;
	int number;

	int time_in;
	int time_out;

	Node *ParentLink;
	ChildLink *FirstChild;
};

void FillNodes(Node*, int);
int FillTimes(int, Node*);
int TestAncestor(Node*, Node*);
Node FindLCA(Node, Node);
Node FindLCABinary(int, int, Node*, int**, int);
void CreateLink(Node*,int,int,int);
void FillMap(int**, Node*, int, int);

int main()
{
	int NodesAmount;
	int LinksToCalc;
	int buff[2];
	int	**TreeMap;
	int size;
	Node *Nodes;
	ChildLink *Temp1, *Temp2;
	
	scanf("%d", &NodesAmount);

	Nodes = new Node[NodesAmount];
	TreeMap = new int *[NodesAmount];

	size = (int)( log((double)NodesAmount) / log(2.0) ) + 1;

	for (int i = 0; i < NodesAmount; i++)
	{
		TreeMap[i] = new int[size];
		memset(TreeMap[i], -1, size*4);
	}

	FillNodes(Nodes, NodesAmount);

	FillMap(TreeMap, Nodes, NodesAmount, size);

/*	Search	*/
	scanf("%d", &LinksToCalc);

	for (int i = 0; i < LinksToCalc; i++)
	{
		scanf("%d %d", &buff[0], &buff[1]);

		buff[0]--;
		buff[1]--;

		if ( buff[0] == buff[1] )	printf("0\n");
		
		else	printf ("%d\n",
			Nodes[buff[0]].height + Nodes[buff[1]].height - 2 * FindLCABinary(buff[0], buff[1], Nodes, TreeMap, size).height);
	}

/*	Free memory	*/
	for (int i = 0; i < NodesAmount; i++)
		delete[] TreeMap[i];

	for (int i = 0; i < NodesAmount; i++)
		if ( Nodes[i].FirstChild )
		{
			for (Temp1 = Nodes[i].FirstChild; Temp1->NextChild != NULL;)
			{
				Temp2 = Temp1;
				Temp1 = Temp1->NextChild;

				delete Temp2;
			}

			delete Temp1;
		}

	delete[] Nodes;
	delete[] TreeMap;

	return 0;
}

void FillMap(int **TreeMap, Node *Nodes, int NodesAmount, int size)
{
	Node Temp;

	for (int i = 0; i < NodesAmount; i++)
		for (int j = 0; j < size; j++)
		{
			Temp = Nodes[i];

			for (int k = 0; k < (int)pow(2.0, j) && Temp.ParentLink != NULL; k++, Temp = *Temp.ParentLink);

			TreeMap[i][j] = Temp.number;
		}
}

void  FillNodes(Node *Nodes, int NodesAmount)
{
	int i;
	int *node1 = new int[NodesAmount];
	int *node2 = new int[NodesAmount];
	int *dist = new int[NodesAmount];
	int LinksWrote;
	int buff[3];

	for (i = 0; i < NodesAmount; i++)
	{
		Nodes[i].distToParent = -1;
		Nodes[i].height = 0;
		Nodes[i].number = i;

		Nodes[i].ParentLink = NULL;
		Nodes[i].FirstChild = NULL;
	}

	for (i = 0; i < NodesAmount-1; i++)
		scanf("%d %d %d", &node1[i], &node2[i], &dist[i]);

	if ( NodesAmount > 1 )
		Nodes[node1[0]-1].ParentLink = &Nodes[node1[0]-1];

	else	node1[0] = 1;

	for (LinksWrote = 0; LinksWrote < NodesAmount-1;)
		for (i = 0; i < NodesAmount-1; i++)
		{
			if ( Nodes[node1[i]-1].ParentLink != NULL && Nodes[node2[i]-1].ParentLink != NULL )
				continue;

			else if ( Nodes[node1[i]-1].ParentLink != NULL || Nodes[node2[i]-1].ParentLink != NULL )
			{
				( Nodes[node1[i]-1].ParentLink != NULL ) ? 
					CreateLink(Nodes, node1[i]-1, node2[i]-1, dist[i]) : CreateLink(Nodes, node2[i]-1, node1[i]-1, dist[i]);

				LinksWrote++;
			}
		}

	FillTimes(0, &Nodes[node1[0]-1]);

	delete[] node1;
	delete[] node2;
	delete[] dist;
}

void CreateLink(Node *Nodes, int parent, int child, int dist)
{
	ChildLink *Temp;

	Nodes[child].ParentLink = &Nodes[parent];
	Nodes[child].distToParent = dist;

	if ( !Nodes[parent].FirstChild )
	{
		Nodes[parent].FirstChild = new ChildLink;
		Nodes[parent].FirstChild->Child = &Nodes[child];
		Nodes[parent].FirstChild->NextChild = NULL;
	}

	else
	{
		for (Temp = Nodes[parent].FirstChild; Temp->NextChild != NULL; Temp = Temp->NextChild);

		Temp->NextChild = new ChildLink;
		Temp->NextChild->Child = &Nodes[child];
		Temp->NextChild->NextChild = NULL;
	}
}

int FillTimes(int time, Node *StartNode)
{
	Node *Temp = StartNode;
	ChildLink Child;
	bool flag;

/*	In depth cycle	*/
	do	{
		if (Temp->ParentLink != NULL)
			Temp->height = Temp->ParentLink->height + Temp->distToParent;

		if (Temp->FirstChild == NULL)
		{
			Temp->time_in = time;
			Temp->time_out = time++;
			flag = 0;
		}

		else if (Temp->FirstChild->NextChild == NULL)
		{
			Temp->time_in = time;
			Temp = Temp->FirstChild->Child;
			
			time++;
			flag = 1;
		}

		else
		{
			Temp->time_in = time++;

			for (Child = *Temp->FirstChild; Child.NextChild != NULL; Child = *Child.NextChild, time++)
				time = FillTimes(time, Child.Child);

			time = FillTimes(time, Child.Child);

			time++;
			flag = 0;
		}
	} while (flag);

/*		High cycle		*/
	for (; Temp != StartNode; Temp = Temp->ParentLink)
		Temp->time_out = time++;


	Temp->time_out = time;
	
	return time;
}

int TestAncestor(Node Node1, Node Node2)
{
	if ( (Node1.time_in < Node2.time_in) && (Node1.time_out > Node2.time_out) )
		return 1;

	else if ( (Node1.time_in > Node2.time_in) && (Node1.time_out < Node2.time_out) )
		return 2;

	else
		return 0;
}

Node FindLCA(Node Node1, Node Node2)
{
	int LCA;
	Node Temp;

	if ( LCA = TestAncestor(Node1, Node2) )
		return ( LCA == 1 ? Node1 : Node2 );

	for (Temp = Node1; !TestAncestor(Temp, Node2); Temp = *Temp.ParentLink);

	return Temp;
}

Node FindLCABinary(int Node1, int Node2, Node *Nodes, int **TreeMap, int size)
{
	Node Temp;
	int I = size-1;
	int LCA;

	if ( LCA = TestAncestor(Nodes[Node1], Nodes[Node2]) )
		return ( LCA == 1 ? Nodes[Node1] : Nodes[Node2] );

	LCA = Node1;

	while ( I > -1 )
	{
		Temp = Nodes[TreeMap[LCA][I]];

		if ( TestAncestor(Temp, Nodes[Node2]) )
			I--;

		else
		{
			LCA = Temp.number;
			I--;
		}
	}

	return *Nodes[LCA].ParentLink;
}