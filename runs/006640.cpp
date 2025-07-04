#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ToCost
{
	int to;
	int cost;
    ToCost()
    {
		to = 0;
		cost = 0;
    }
    ToCost(int t, int c)
    {
		to = t;
		cost = c;
    }
};

struct edge
{
	int begin;
	int end;
	int cost;
	edge()
    {
		begin = 0;
		end = 0;
		cost = 0;
    }
    edge(int b, int e, int c)
    {
		begin = b;
		end = e;
		cost = c;
    }

};
const int MAXN = 40001;
vector<ToCost> graph[MAXN];
vector<edge> query;
int sets[MAXN];
bool u[MAXN];
int N = 0;


int set_get(int v)
{
	return v==sets[v]? v :sets[v] = set_get(sets[v]);
}


void dsu_unite(int a, int b, int cost)
{

	for(vector<edge>::iterator iter=query.begin(); iter!=query.end(); ++iter)
	{
		if ((b==set_get((*iter).begin)) && u[(*iter).begin])
		{
			(*iter).cost+=cost;
		}
		else if ((b==set_get((*iter).end)) && u[(*iter).end])
			{
				(*iter).cost+=cost;
			}
	}
	sets[b] = a;
}

int get_dist (int up, int down)
{
	if (up==down) return 0;
	for (int i=1; i!=MAXN; ++i)
	{
		for (vector<ToCost>::iterator iter=graph[i].begin(); iter!=graph[i].end(); ++iter)
		{
			if ((*iter).to==down)
			return (*iter).cost+get_dist(up, i);
		}
	}
	return 0;
}

void dfs(int v)
{
	sets[v] = v;
	u[v] = true;
	for(size_t i=0; i<graph[v].size(); ++i)
		if (!u[graph[v][i].to])
		{
			dfs(graph[v][i].to);
			dsu_unite(v, graph[v][i].to, graph[v][i].cost);
		}
	for(vector<edge>::iterator iter=query.begin(); iter!=query.end(); ++iter)
		if (u[(*iter).begin] && u[(*iter).end])
		{
			if (v==(*iter).begin)
			{
				(*iter).cost+=get_dist(set_get((*iter).end),(*iter).begin);
				(*iter).begin=0;
				(*iter).end=0;
			}
				else if	(v==(*iter).end)
				{
					(*iter).cost+=get_dist(set_get((*iter).begin),(*iter).end);
					(*iter).begin=0;
					(*iter).end=0;
				}
		}
};

void convert (size_t v)
{
	u[v] = true;
	for(size_t i=0; i<graph[v].size(); ++i)
		if (!u[graph[v][i].to])
		{
			convert(graph[v][i].to);
		}

	for(size_t i=1; i!=N; ++i)
	{
		for(int j = 0; j<graph[i].size(); j++)
			if ((graph[i][j].to==v) && (!u[i]))
			{
				graph[v].push_back(ToCost(i,graph[i][j].cost));
				graph[i].erase(graph[i].begin()+j);
				j--;
				convert(i);
			}
	}
}

int main()
{
	cin>>N;
	int begin, end, cost;
	for(int i = 1; i!=N; ++i)
	{
		cin>>begin>>end>>cost;
		graph[begin].push_back(ToCost(end,cost));
	}
	convert(1);
	int a;
	cin>>a;
	for(int i = 0; i!=a; ++i)
	{
		cin>>begin>>end;
		query.push_back(edge(begin, end, 0));
	}
	for(int i=0; i!=N+1; ++i){u[i] = false;}
	dfs(1);
	for(vector<edge>::iterator iter=query.begin(); iter!=query.end(); ++iter)
	{
		cout<<(*iter).cost<<endl;
	}
	return 0;
}


