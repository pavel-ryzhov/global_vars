#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
void buildTree(int pnt, int distance);
class Vertex{
	public:
	int parent;
	int length;
	int distance;
	Vertex()
	{
		parent = -1;
		length = -1;
		distance = -1;
	}
};
vector<vector<int> > raw;
vector<Vertex> tree;
int vertex_count;
int getDistToRoot(int from)
{
	if(tree[from].distance == -1)
		return 0;
	return tree[from].distance;
}
int getLength(int from, int to)
{
	if(from == to)
		return 0;
	if(getDistToRoot(to) > getDistToRoot(from))
	{
		int c = to;
		to = from;
		from = c;
	}
	if(tree[from].length == -1)
	{
		cerr << "getLength: destination unattainable" << endl;
		return 0;
	}
	return getLength(tree[from].parent,to)+tree[from].length;
}

int main(int argc, char *argv[])
{
	scanf("%d",&vertex_count);
	raw = vector<vector<int> >(vertex_count);
	for(int i = 0; i<vertex_count; i++)
		raw[i] = vector<int>(vertex_count,-1);
	tree = vector<Vertex>(vertex_count);
	for(int i = 0; i<vertex_count-1; i++)
	{
		int from;
		int to;
		int len;
		scanf("%d %d %d",&from, &to, &len);
		from--;
		to--;
		if(from > to)
			raw[to][from] = len;
		else
			raw[from][to] = len;
	}
	buildTree(0, 1);
	int pairs_count;
	scanf("%d",&pairs_count);
	for(int i = 0; i<pairs_count; i++)
	{
		int from;
		int to;
		scanf("%d %d",&from,&to);
		from--;
		to--;
		cout << getLength(from, to) << endl;
	}
	return 0;
}
void buildTree(int pnt, int distance)
{
	list<int> nextPoints;
	for(int i = 0; i<vertex_count; i++)
	{
		if(i<pnt)
		{
			if(raw[i][pnt]!=-1)
			{
				tree[i].parent = pnt;
				tree[i].length = raw[i][pnt];
				tree[i].distance = distance;
				nextPoints.push_back(i);
				raw[i][pnt] = -1;
			}
		}
		else
		{
			if(raw[pnt][i]!=-1)
			{
				tree[i].parent = pnt;
				tree[i].length = raw[pnt][i];
				tree[i].distance = distance;
				nextPoints.push_back(i);
				raw[pnt][i] = -1;
			}
		}
	}
	for(list<int>::iterator it = nextPoints.begin(); it!=nextPoints.end(); it++)
		buildTree(*it, distance+1);
}
