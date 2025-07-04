#include <vector>
#include <stdio.h>
//#include <iostream>
//#include <conio.h>
using namespace std;

struct LINK
{
	int length;
	int to;
};

struct ZVENO
{
	int deep;
	LINK parent;
	vector<LINK> links;
};

ZVENO *tree;

int findL(int start, int end);
void process(int n, int anc);

int main()
{
	int N, s,e,l;
	scanf ("%d",&N);
	LINK temp;
	tree = new ZVENO [N];
	for (int i = 0; i<N-1; i++)
	{
		scanf ("%d%d%d",&s,&e,&l);
		temp.length = l;
		temp.to = e-1;
		tree[s-1].links.push_back(temp);
		temp.to = s-1;
		tree[e-1].links.push_back(temp);
	}
	tree[0].deep = 0;
	for (int i = 0; i < tree[0].links.size(); i++)
	{
		process(tree[0].links[i].to, 0);
	}
	scanf ("%d",&N);
	for (int i = 0; i<N; i++)
	{
		int s,e;
		scanf ("%d%d",&s,&e);
		printf("%ld\n",findL(s-1,e-1));
	}
	return 0;
}

int findL(int start, int end)
{
	int len = 0;
	if (start==end) return 0;
	while (tree[start].deep < tree[end].deep)
	{
		len += tree[end].parent.length;
		end = tree[end].parent.to;
	}
	while (tree[start].deep > tree[end].deep)
	{
		len += tree[start].parent.length;
		start = tree[start].parent.to;
	}
	while (start != end)
	{
		len += tree[start].parent.length;
		start = tree[start].parent.to;
		len += tree[end].parent.length;
		end = tree[end].parent.to;
	}
	return len;
}

void process (int n, int anc)
{
	tree[n].deep = tree[anc].deep + 1;
	for (vector<LINK>::iterator p = tree[n].links.begin(); p < tree[n].links.end(); p++)
	{
		if ((*p).to == anc)
		{
			tree[n].parent.to = anc;
			tree[n].parent.length = (*p).length;
		}
		else process((*p).to, n);
	}
}