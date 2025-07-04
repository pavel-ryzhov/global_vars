#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

vector< vector<int> > graph;
vector<int> depth;
vector<int> parent;
vector<bool> used;
int numNodes;

void dfs(int v)
{
	used[v] = true;
	for(int i=1; i<=numNodes; i++)
		if(graph[v][i] != -1)
			if(!used[i])
			{
				depth[i] = depth[v] + 1;
				parent[i] = v;
				dfs(i);
			}
}

int slca(int a, int b)
{
	int h1 = depth[a];
	int h2 = depth[b];
	int r = 0;

	while(h1!=h2)
	{
		if(h1>h2)
		{
			r += graph[a][parent[a]];
			a = parent[a];
			h1--;
		}
		else
		{
			r += graph[b][parent[b]];
			b = parent[b];
			h2--;
		}
	}

	while(a!=b)
	{
		r += graph[a][parent[a]];
		r += graph[b][parent[b]];
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

	for(int i=1; i<=numNodes; i++)
		graph[i].resize(numNodes+1, -1);

	int a,b,r,N;
	for(int i=1; i<numNodes; i++)
	{
		cin>>a>>b>>r;
		graph[a][b] = r;
		graph[b][a] = r;
	}

	dfs(1);
		
	cin>>N;

	for(int i=1; i<=N; i++)
	{
		cin>>a>>b;
		cout<<slca(a, b)<<"\n";
	}

	return 0;
}
