#include <iostream>
#include <vector>
using namespace std;
int n, l;
vector < vector<int> > g;
vector<bool> used;
vector<int> tin, tout;
int timer;
vector<vector<int> > up;
vector<vector<int> > gr;

void dfs (int v, int p = 0) {
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs (to, v);
	}
	tout[v] = ++timer;
}

bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int pathLength(int lcaAn, int vert)
{
	int len=0;
	while(vert != lcaAn)
	{
		for(vector<vector<int> >::iterator i=gr.begin(); i!=gr.end(); ++i)
		{
			if((i->at(0)==up[vert][0] && i->at(1)==vert) || (i->at(1)==up[vert][0] && i->at(0)==vert))
				len+=i->at(2);
		}
		vert=up[vert][0];
	}
	return len;
}

int findAnswer (int a, int b) 
{
	int oldA=a;
	if (upper (a, b))  
		return pathLength(a,b);
	if (upper (b, a))  
		return pathLength(b,a);
	for (int i=l; i>=0; --i)
		if (! upper (up[a][i], b))
			a = up[a][i];
	return pathLength(up[a][0],oldA) + pathLength(up[a][0],b);
}

int main()
{
	vector<vector<int> > graph;
	vector<vector<int> > query;
	vector<int> tmp;
	int n;
	cin>>n;
	used.resize (n);
	tin.resize (n);
	tout.resize (n);
	up.resize (n);
	g.resize(n);
	int x;
	for(int i=0; i<n-1; ++i)
	{
		for(int j=0; j<3; ++j)
		{
			cin>>x;
			tmp.push_back(x);
		}
		tmp[0]-=1;
		tmp[1]-=1;
		gr.push_back(tmp);
		tmp.clear();
	}
	graph=gr;
	for(vector<vector<int> >::iterator i=graph.begin(); i!=graph.end(); ++i)
	{
		i->pop_back();
	}
	int numOfPair;
	cin>>numOfPair;
	for(int i=0; i<numOfPair; ++i)
	{
		for(int j=0; j<2; ++j)
		{
			cin>>x;
			--x;
			tmp.push_back(x);
		}
		query.push_back(tmp);
		tmp.clear();
	}

	for(vector<vector<int> >::iterator i=graph.begin(); i!=graph.end(); ++i)
	{
		g[i->at(0)].push_back(i->at(1));
		g[i->at(1)].push_back(i->at(0));
	}

	l = 1;
	while ((1<<l) <= n)  ++l;
	for (int i=0; i<n; ++i)  up[i].resize (l+1);
	dfs (0);
	
	for(int i=0; i<numOfPair; ++i)
	{
		int ans=findAnswer(query[i][0],query[i][1]);
		cout<<ans<<endl;
	}
	return 0;
}
