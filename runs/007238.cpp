#include <vector>
#include <stdio.h>
//#include <iostream>
using namespace std;

struct LINK
{
	int length;
	int to;
};

vector<LINK> *tree;

int findL(int start, int end, int last);

int main()
{
	int N, s,e,l;
	scanf ("%d",&N);
	LINK temp;
	tree = new vector<LINK> [N];
	for (int i = 0; i<N-1; i++)
	{
		scanf ("%d%d%d",&s,&e,&l);
		temp.length = l;
		temp.to = e-1;
		tree[s-1].push_back(temp);
		temp.to = s-1;
		tree[e-1].push_back(temp);
	}
	scanf ("%d",&N);
	for (int i = 0; i<N; i++)
	{
		int s,e;
		scanf ("%d%d",&s,&e);
		printf("%ld\n",findL(s-1,e-1,-1));
	}
	return 0;
}

int findL(int start, int end, int last)
{
	if (start==end) return 0;
	if (tree[end].size()==1) 
	{
		return (tree[end])[0].length + findL((tree[end])[0].to, start, end);
	}
	for (int i = 0; i < tree[start].size(); i++)
		if ((tree[start])[i].to == end) 
			return (tree[start])[i].length;
	for (int i = 0; i < tree[start].size(); i++)
	{
		if ((tree[start])[i].to != last)
		{
			int len = findL((tree[start])[i].to, end, start);
			if (len != -1) 
			{
				return len + (tree[start])[i].length;
			}
		}
	}
	return -1;
}