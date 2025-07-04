#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <utility>
using namespace std;

const int MAXN = 40000;
vector<unsigned short> g[MAXN], q[MAXN];
unsigned short ancestor[MAXN], minAncestor, minAncestors[MAXN],  request[MAXN][2], M;
bool u[MAXN];
pair<unsigned short, unsigned short> dsu[MAXN];


class Element
{
private:
	map<unsigned short, unsigned short> cost;
	unsigned short parent;
public:
	
	unsigned short getCost(int i)
	{
		return cost[i];
	}

	void setCost(unsigned short _cost, unsigned short i)
	{
		cost[i] = _cost;
	}

	unsigned short getParent()
	{
		return parent;
	}
	void setParent(unsigned short _parent)
	{
		parent = _parent;
	}
} elements[MAXN];
 
pair<unsigned short, unsigned short> dsu_get (unsigned short v) 
{
	if (v != dsu[v].first)
	{
		dsu[v].first = dsu_get(dsu[v].first).first;
	}
	return dsu[v];
}
 
void dsu_unite (unsigned short a, unsigned short b, unsigned short new_ancestor) 
{
	a = dsu_get (a).first;  b = dsu_get (b).first;
	swap (a, b);
	dsu[a] = make_pair(b, elements[a].getCost(b));
	elements[a].setParent(b);
	ancestor[b] = new_ancestor;
}
 
void dfs (unsigned short v) 
{
	dsu[v] = make_pair(v, 0);  ancestor[v] = v;
	u[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!u[g[v][i]]) 
		{
			dfs (g[v][i]);
			dsu_unite (v, g[v][i], v);
		}
	for (size_t i=0; i<q[v].size(); ++i)
		if (u[q[v][i]]) 
		{
			minAncestor =  ancestor[ dsu_get(q[v][i]).first ];
			for (int j = 0; j < M; j++)
				if ( ( (request[j][0] == v) && (request[j][1] == q[v][i]) ) || ( (request[j][0] == q[v][i]) && (request[j][1] == v) ) )
				{
					minAncestors[j] = minAncestor;
				}
		}
}

int main()
{
	int N, beg, end, cost, a, b, tempEl;
	unsigned results[MAXN], sum;

	cin >> N;
	if (N == 1) 
	{
		cin >> M;
		cin >> a >> b;
		cout << 0;
		return 0;
	}
	
	for (int i = 0; i < N - 1; i++)
	{
		cin >> beg >> end >> cost;
		--beg; --end;
		elements[beg].setCost(cost, end);
		elements[end].setCost(cost, beg);
		g[beg].push_back(end);
		g[end].push_back(beg);
	}
	
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		--a; --b;
		request[i][0] = a; request[i][1] = b;
		results[i] = 0;
		q[a].push_back(b);
		q[b].push_back(a);
	}
	
	dfs(0);
	
	for (int i = 0; i < M; i++)
	{
		sum = 0;
		tempEl = request[i][0];
		while (minAncestors[i] != tempEl)
		{
			sum += dsu[tempEl].second;
			tempEl = elements[tempEl].getParent();
		}
		
		tempEl = request[i][1];
		while (minAncestors[i] != tempEl)
		{
			sum += dsu[tempEl].second;
			tempEl = elements[tempEl].getParent();
		}	
		results[i] = sum;
	}
	
	for (int i = 0; i < M; i++)
	{
		cout << results[i] << '\n';
	}
	return 0;
}