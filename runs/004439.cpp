#include <vector>
using std::vector;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <utility>
using std::pair;
using std::make_pair;

#include <fstream>
using std::ifstream;


enum COLOR {WHITE = 0, GRAY, BLACK};


//ifstream infile( "dict.txt" );//////////////////////////////////////



struct Node
{
	vector<int> edgeEnd;
	vector<int> edgeLength;
	int ancestor;
	int distanceToRoot;
	COLOR color;
	int rank;
	vector<int> otherPairElement;
	vector<int> pairOrder;

	Node()
	{ 
		rank = 0;
		color = WHITE;
		distanceToRoot = -1;
		ancestor = -1;
	}
};

class DSF
{
public:
	//DSF(){};
	void input();
	void make_set(int elem);
	int find_set(int elem);
	void lca(int index, int fullDistance);
	void unite(int a, int b);
	void output();
	//~DSF();
private:
	vector<Node> tree;
	vector< vector<int> > pairs;
	vector<int> answers;
};


void DSF::input()
{
	int verticesNumber;
	//infile >> verticesNumber;///////////////////////////////////////////
	cin >> verticesNumber;
	
	tree.resize(verticesNumber + 1);

	for (int nextVertex = 0; nextVertex < verticesNumber - 1; nextVertex++)
	{
		int start, end, length;
		//infile >> start >> end >> length;//////////////////////////////////////
		cin >> start >> end >> length;

	/*	if (start > end)
		{
			start += end;
			end = start - end;
			start -= end;
		}*/

		tree.at(start).edgeEnd.push_back(end);
		tree.at(start).edgeLength.push_back(length);
		tree.at(end).edgeEnd.push_back(start);
		tree.at(end).edgeLength.push_back(length);
	}

	int pairsize;
	//infile >> pairsize;///////////////////////////////////////////////
	cin >> pairsize;
	pairs.resize(pairsize);
	answers.resize(pairsize);
	
	for (int nextPair = 0; nextPair < pairsize; nextPair++)
	{
		int first, second;
		//infile >> first >> second;//////////////////////////////////////////////////
		cin >> first >> second;
		pairs.at(nextPair).push_back(first);
		pairs.at(nextPair).push_back(second);
		tree.at(first).otherPairElement.push_back(second);
		tree.at(first).pairOrder.push_back(nextPair);
		tree.at(second).otherPairElement.push_back(first);
		tree.at(second).pairOrder.push_back(nextPair);
	}
}

void DSF::make_set(int elem)
{
	tree.at(elem).ancestor = elem;
	tree.at(elem).rank = 0;
}

int DSF::find_set(int elem)
{
	if (elem != tree.at(elem).ancestor)
	{
		tree.at(elem).ancestor = find_set( tree.at(elem).ancestor );
	}
	return tree.at(elem).ancestor;
}

void DSF::unite(int a, int b)
{
	a = find_set(a);
	b = find_set(b);
	/*
	if (tree.at(a).rank < tree.at(b).rank)
	{
		tree.at(a).ancestor = b;
	}
	else
	{
		tree.at(b).ancestor = a;
		
		if (tree.at(a).rank == tree.at(b).rank)
		{
			++tree.at(a).rank;
		}
	}	*/
	tree.at(b).ancestor = a;
}

void DSF::lca(int index, int fullDistance)
{
	tree.at(index).ancestor = index; //заменяет make_set
	tree.at(index).color = GRAY;
	tree.at(index).distanceToRoot = fullDistance;
	
	for (int nextEdge = 0; nextEdge < tree.at(index).edgeEnd.size(); ++nextEdge)
	{
		int otherVertex = tree.at(index).edgeEnd.at(nextEdge);

		if (tree.at(otherVertex).color == WHITE)
		{
			int newFullDistance = fullDistance + tree.at(index).edgeLength.at(nextEdge);
			lca (tree.at(index).edgeEnd.at(nextEdge), newFullDistance);
			unite (index, tree.at(index).edgeEnd.at(nextEdge));
			tree.at(find_set(index)).ancestor = index;
		}
	}

	tree.at(index).color = BLACK;

	if ( !tree.at(index).otherPairElement.empty() )
	{
		for (int nextElement = 0; nextElement < tree.at(index).otherPairElement.size(); ++nextElement)
		{
			int next = tree.at(index).otherPairElement.at(nextElement);
			if (tree.at(next).color == BLACK)
			{
				int lca = tree.at(find_set(next)).ancestor;
				int v = tree.at(next).distanceToRoot;
				int u = tree.at(index).distanceToRoot;
				int lcaDist = tree.at(lca).distanceToRoot;
				int res = u - lcaDist + v - lcaDist;
				int place = tree.at(index).pairOrder.at(nextElement);
				answers.at(place) = res;
			}
		}
	}
}

void DSF::output()
{
	for (int ans = 0; ans < answers.size(); ++ans)
	{
		cout << answers.at(ans) << endl;
	}
}

int main()
{
	DSF example;
	example.input();
	example.lca(1,0);
	example.output();

	return 0;
}