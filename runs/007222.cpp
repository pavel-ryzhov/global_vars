#include <vector>
#include <stdio.h>
using namespace std;

struct WAY
{
	int to;
	long length;
};

struct LINK
{
	int length;
	int to;
	vector<WAY> ways;
};

struct ZVENO
{
	int n; //����� �����
	vector<LINK> links; //������ � ���
};



ZVENO *tree;

long findL(int start, int end, int last, int *nearstart, int *nearend);

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
		int s,e, t1, t2;
		scanf ("%d%d",&s,&e);
		printf("%ld\n",findL(s-1,e-1,-1,&t1,&t2));
	}
	return 0;
}

long findL(int start, int end, int last, int *nearstart, int *nearend)
{
	if (start==end) return 0;
	for (int i = 0; i < tree[start].links.size(); i++)
		if (tree[start].links[i].to == end) 
		{
			*nearend = start;
			*nearstart = end;
			return tree[start].links[i].length;
		}
	for (int i = 0; i<tree[start].links.size(); i++)
	{
		if (tree[start].links[i].to != start)
		{
			for (int j = 0; j<tree[start].links[i].ways.size(); j++)
				if (tree[start].links[i].ways[j].to == end) 
				{
					return tree[start].links[i].ways[j].length;
				}
		}
	}
	for (int i = 0; i < tree[start].links.size(); i++)
	{
		if (tree[start].links[i].to != last)
		{
			int ns, ne;
			long len = findL(tree[start].links[i].to, end, start, &ns, &ne);
			if (len != -1) 
			{
				WAY temp;
				*nearstart = tree[start].links[i].to;
				temp.to = end;
				temp.length = len + (long)tree[start].links[i].length;
				tree[start].links[i].ways.push_back(temp);
				*nearend   = ne;
				temp.to = start;
				for (int j = 0; j<tree[end].links.size(); j++)
				{
					if (tree[end].links[j].to == ne) tree[end].links[j].ways.push_back(temp);
				}
				return len + (long)tree[start].links[i].length;
			}
		}
	}
	return -1;
}