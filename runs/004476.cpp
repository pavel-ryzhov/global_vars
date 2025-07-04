#include <iostream>
#include <list>
#include <limits.h>

struct Node
{
	int nestingLevel;
	int distanceFromParent;
	std::list<std::pair<Node*, int> > neighbor;
	Node *parent;
};

int searchDistance(Node *node1, Node *node2)
{
	int firstDistance = 0, secondDistance = 0;
	Node *firstNode, *secondNode;

	firstNode = node1;
	secondNode = node2;

	for(;;)
	{
		if(firstNode == secondNode) return firstDistance + secondDistance;

		if(firstNode->nestingLevel > secondNode->nestingLevel)
		{
			firstDistance += firstNode->distanceFromParent;
			firstNode = firstNode->parent;
		}
		else if(secondNode->nestingLevel > firstNode->nestingLevel)
		{
			secondDistance += secondNode->distanceFromParent;
			secondNode = secondNode->parent;
		}
		else if(firstNode->nestingLevel == secondNode->nestingLevel)
		{
			firstDistance += firstNode->distanceFromParent;
			secondDistance += secondNode->distanceFromParent;
			firstNode = firstNode->parent;
			secondNode = secondNode->parent;
		}
	}
}

void initTree(Node *node)
{
	for(std::list<std::pair<Node*, int> >::iterator index = node->neighbor.begin(); index!=node->neighbor.end(); index++)
	{
		if(index->first->nestingLevel > node->nestingLevel)
		{
			index->first->nestingLevel = node->nestingLevel + 1;
			index->first->parent = node;
			index->first->distanceFromParent = index->second;
			initTree(index->first);
		}
	}
}

int main()
{
	int treeSize, beginEdge, endEdge, lengthEdge, numberOfPairs, firstElement, secondElement;

	std::cin >> treeSize;
	
	if(treeSize == 1)
	{
		std::cout << 0;
		return 0;
	}

	Node *tree = new Node[treeSize];

	for(int i = 0; i < treeSize; i++)
	{
		tree[i].parent = 0;
		tree[i].nestingLevel = INT_MAX;
	}

	for(int i = 0; i < treeSize-1; i++)
	{
		std::cin >> beginEdge >> endEdge >> lengthEdge;
		tree[beginEdge-1].neighbor.push_back(std::pair<Node*, int>(&tree[endEdge-1], lengthEdge));
		tree[endEdge-1].neighbor.push_back(std::pair<Node*, int>(&tree[beginEdge-1], lengthEdge));
	}

	tree[0].nestingLevel = 0;
	tree[0].distanceFromParent = 0;

	initTree(&tree[0]);

	std::cin >> numberOfPairs;

	if(numberOfPairs < 1) return -1;

	int *replies = new int[numberOfPairs];
	int distance;

	for(int i = 0; i < numberOfPairs; i++)
	{
		std::cin >> firstElement >> secondElement;
		distance = searchDistance(&tree[firstElement-1], &tree[secondElement-1]);
		replies[i] = distance;
	}

	for(int i = 0; i < numberOfPairs; i++)
	{
		std::cout << replies[i] << std::endl;
	}

	delete []tree;
	delete []replies;

	return 0;
}