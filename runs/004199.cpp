#include <iostream>
#include <vector>
#include <list>

using std::cout;
using std::cin;
using std::vector;
using std::list;

struct Node
{
	int x;
	int r;
};

vector< list<Node> > graph;
vector<char> used;
vector<int> parent;
vector<int> depth;
int numNodes;

void dfs(int v)
{
	used[v] = 1;
	for(list<Node>::iterator i=graph[v].begin(); i!=graph[v].end(); i++)
		if(!used[(*i).x])
		{
			parent[(*i).x] = v;
			depth[(*i).x] = depth[v] + 1;
			dfs((*i).x);
		}
}

int getR(int a)		//возвращает расстояние до родителя
{
	int r;
	for(list<Node>::iterator i=graph[a].begin(); i!=graph[a].end(); i++)
		if ((*i).x==parent[a])
		{
			r = (*i).r;
			break;
		}
	return r;
}

int slca(int a, int b)
{
	int h1 = depth[a];
	int h2 = depth[b];
	int r=0;

	while(h1!=h2)
	{
		if(h1>h2)
		{
			r += getR(a);
			a = parent[a];
			h1--;
		}
		else
		{
			r += getR(b);
			b = parent[b];
			h2--;
		}
	}

	while(a!=b)
	{
		r += getR(a);
		r += getR(b);
		a = parent[a];
		b = parent[b];
	}
	return r;
}

int main()
{
	cin>>numNodes;

	graph.resize(numNodes+1);
	used.resize(numNodes+1);
	parent.resize(numNodes+1);
	depth.resize(numNodes+1);

	int a,b,r,N;
	Node t;
	for(int i=1; i<numNodes; i++)
	{
		cin>>a>>b>>r;
		t.x = b;
		t.r = r;
		graph[a].push_back(t);
		t.x = a;
		graph[b].push_back(t);
	}

	dfs(1);

	cin>>N;

	for(int i=1; i<=N; i++)
	{
		cin>>a>>b;
		cout<<slca(a,b)<<"\n";
	}

	return 0;
}
