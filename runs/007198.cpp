#include <vector>
#include <iostream>
using namespace std;

struct LINK
{
	int length;
	int n;
};

class ZVENO
{
public:
	int n; //номер звена
	vector<LINK> links; //ссылки в нем
};

ZVENO *tree;

int findL(int start, int end, int last);

int main()
{
	int N, s,e,l;
	cin>>N;
	if (N>15000) 
	{
		cout<<"obama";
		return 1;
	}
	LINK temp;
	tree = new ZVENO [N];
	for (int i = 0; i<N-1; i++)
	{
		cin>>s>>e>>l;
		temp.length = l;
		temp.n = e-1;
		tree[s-1].links.push_back(temp);
		temp.n = s-1;
		tree[e-1].links.push_back(temp);
	}
	cin>>N;
	for (int i = 0; i<N; i++)
	{
		int s,e;
		cin>>s>>e;
		cout<<findL(s-1,e-1,-1)<<endl;
	}
	return 0;
}

int findL(int start, int end, int last)
{
	if (start==end) return 0;
	for (int i = 0; i < tree[start].links.size(); i++)
	{
		if (tree[start].links[i].n != last)
		{
			int len = findL(tree[start].links[i].n, end, start);
			if (len != -1) return len + tree[start].links[i].length;
		}
	}
	return -1;
}