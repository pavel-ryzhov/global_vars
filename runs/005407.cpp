#include <stdio.h>
#include <malloc.h>

struct Node;

struct ChildLink
{
	Node* Child;
	ChildLink* NextChild;
};

struct Node
{
	int number;
	int distToParent;
	int height;

	int time_in;
	int time_out;

	Node* ParentLink;
	ChildLink* FirstChild;
};


int FindNode(int, Node*, int);
void FillNodes(Node*, int);
int FillTimes(int, Node*);
int TestAncestor(Node, Node);
Node FindLCA(Node, Node);
void CreateLink(Node*,int,int,int);

int main()
{
	int NodesAmount;
	int LinksToCalc;
	int buff[2];

	Node* Nodes;
	ChildLink* Temp1, *Temp2;
	
	scanf("%d", &NodesAmount);

	Nodes = new Node[NodesAmount];

	FillNodes(Nodes, NodesAmount);

	scanf("%d", &LinksToCalc);

	for (int i = 0; i < LinksToCalc; i++)
	{
		scanf("%d %d", &buff[0], &buff[1]);

		buff[0] = FindNode(buff[0], Nodes, NodesAmount);
		buff[1] = FindNode(buff[1], Nodes, NodesAmount);	

		printf ("%d\n", Nodes[buff[0]].height + Nodes[buff[1]].height - 2 * FindLCA(Nodes[buff[0]], Nodes[buff[1]]).height);
	}

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

	return 0;
}

int FindNode (int NodeNumber, Node* Nodes, int NodesAmount)
{
	int res = -1;

	for (int i = 0; i < NodesAmount; i++)
		if ( Nodes[i].number == NodeNumber )
			res = i;
	
	return res;
}

void FillNodes(Node* Nodes, int NodesAmount)
{
	int i;
	int* node1 = new int[NodesAmount-1];
	int* node2 = new int[NodesAmount-1];
	int* dist = new int[NodesAmount-1];
	int NodesWrote;
	int buff[3];

	for (i = 0; i < NodesAmount; i++)
	{
		Nodes[i].distToParent = -1;
		Nodes[i].number = -1;
		Nodes[i].height = 0;

		Nodes[i].ParentLink = NULL;
		Nodes[i].FirstChild = NULL;
	}


	for (NodesWrote = 0, i = 0; i < NodesAmount-1; i++)
	{
		scanf("%d %d %d", &buff[0], &buff[1], &buff[2]);
	
		if ( (node1[i] = FindNode(buff[0], Nodes, NodesWrote)) == -1 )
		{
			Nodes[NodesWrote].number = buff[0];
			node1[i] = NodesWrote++;
		}

		if ( (node2[i] = FindNode(buff[1], Nodes, NodesWrote)) == -1 )
		{
			Nodes[NodesWrote].number = buff[1];
			node2[i] = NodesWrote++;
		}

		dist[i] = buff[2];
	}

	Nodes[0].ParentLink = &Nodes[0];

	if ( NodesAmount > 1 )
		CreateLink(Nodes, 0, 1, dist[0]);

	for (NodesWrote = 1; NodesWrote < NodesAmount-1;)
		for (i = 1; i < NodesAmount-1; i++)
		{
			if ( Nodes[node1[i]].ParentLink != NULL && Nodes[node2[i]].ParentLink != NULL )
				continue;

			else if ( Nodes[node1[i]].ParentLink != NULL || Nodes[node2[i]].ParentLink != NULL )
			{
				( Nodes[node1[i]].ParentLink != NULL ) ? 
					CreateLink(Nodes, node1[i], node2[i], dist[i]) : CreateLink(Nodes, node2[i], node1[i], dist[i]);

				NodesWrote++;
			}
		}

/*		Fill time_in, time_out		*/
	FillTimes(0, &Nodes[0]);

	delete[] node1;
	delete[] node2;
	delete[] dist;
}

void CreateLink(Node* Nodes, int parent, int child, int dist)
{
	ChildLink* Temp;

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

int FillTimes(int time, Node* StartNode)
{
	Node* Temp = StartNode;
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
	for (; Temp->number != StartNode->number; Temp = Temp->ParentLink)
		Temp->time_out = time++;

	Temp->time_out = time;
	
	return time;
}

int TestAncestor(Node Node1, Node Node2)
{
	if ( Node1.number == Node2.number)
		return 1;

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