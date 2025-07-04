#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

struct edge
{
	int v,d;
	edge(int v,int d)
	{
		this->v=v;
		this->d=d;
	}
};

const int NMAX=40000;

int n,m;
vector<edge> g[NMAX];
int dist[NMAX];
vector< pair<int,int> > tests[NMAX];
int ans[NMAX];
char color[NMAX];
int Element[NMAX];

void read_data()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		u--;
		v--;
		g[u].push_back(edge(v,d));
		g[v].push_back(edge(u,d));
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		u--;
		v--;
		tests[u].push_back(make_pair(v,i));
		tests[v].push_back(make_pair(u,i));
	}
	memset(color,0,sizeof(char)*n);
}

int lca(int v)
{
	if(color[v]==1)
		return v;
	Element[v]=lca(Element[v]);
	return Element[v];
}

void dfs(int v,int d,int last)
{
	color[v]=1;
	dist[v]=d;
	for(int i=0;i<tests[v].size();i++)
	{
		int u=tests[v][i].first;
		if(color[u]!=0)
			ans[tests[v][i].second]=d+dist[u]-2*dist[lca(u)];
	}
	for(int i=0;i<g[v].size();i++)
		if(g[v][i].v!=last)
			dfs(g[v][i].v,d+g[v][i].d,v);
	Element[v]=last;
	color[v]=2;
}

void write_ans()
{
	for(int i=0;i<m;i++)
		printf("%d\n",ans[i]);
}

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read_data();
	dfs(0,0,-1);
	write_ans();
	return 0;
}