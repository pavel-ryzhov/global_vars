#include <vector>
#include <stdio.h>
//#include <iostream>
using namespace std;

struct LINK
{
	int length;
	int to;
};

struct ZVENO
{
	int n; //номер звена
	vector<LINK> links; //ссылки в нем
};



ZVENO *tree;

int findL(int start, int end, int last);

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
	if (tree[end].links.size()==1) 
	{
		return tree[end].links[0].length + findL(tree[end].links[0].to, start, end);
	}
	for (int i = 0; i < tree[start].links.size(); i++)
		if (tree[start].links[i].to == end) 
			return tree[start].links[i].length;
	for (int i = 0; i < tree[start].links.size(); i++)
	{
		if (tree[start].links[i].to != last)
		{
			int len = findL(tree[start].links[i].to, end, start);
			if (len != -1) 
			{
				return len + tree[start].links[i].length;
			}
		}
	}
	return -1;
}