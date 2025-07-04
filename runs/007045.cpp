#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector< vector<int> > g, q, edge, ans, pairs;
vector<int> dsu, ancestor, length;
vector<bool> u;

int dsu_get(int v)
{
	return v == dsu[v] ? v : dsu[v] = dsu_get(dsu[v]);
}

void dsu_unite(int a, int b, int new_ancestor)
{
	a = dsu_get(a);
	b = dsu_get(b);
	if (rand() & 1)
		swap(a, b);
	dsu[a] = b;
	ancestor[b] = new_ancestor;
}

void dfs(int v)
{
	dsu[v] = v;
	ancestor[v] = v;
	u[v] = true;
	for(size_t i = 0; i < g[v].size(); ++i)
	{
		if (!u[g[v][i]])
		{
			length[g[v][i]] = length[v] + edge[v][i];
			dfs(g[v][i]);
			dsu_unite(v, g[v][i], v);
		}
	}
	for (size_t i = 0; i < q[v].size(); ++i)
	{
		if (u[q[v][i]])
		{
			ans[v][i] = length[v] + length[q[v][i]] - 
				2 * length[ancestor[dsu_get(q[v][i])]];
		}
	}
}

int main()
{
	int n, a, b, c;
	cin >> n;
	g.resize(n);
	edge.resize(n);
	u.resize(n);
	dsu.resize(n);
	ancestor.resize(n);
	length.resize(n);
	q.resize(n);
	ans.resize(n);
	for (int i = 0; i < n - 1; i++)
	{
		cin >> a >> b >> c;
		--a;
		--b;
		g[a].push_back(b);
		edge[a].push_back(c);
	}
	cin >> n;
	pairs.resize(n);
	for (int i = 0; i < n; i++)
	{
		pairs[i].resize(4);
		cin >> a >> b;
		a--;
		b--;
		q[a].push_back(b);
		q[b].push_back(a);
		ans[a].push_back(0);
		ans[b].push_back(0);
		pairs[i][0] = a;
		pairs[i][1] = b;
		pairs[i][2] = ans[a].size() - 1;
		pairs[i][3] = ans[b].size() - 1;
	}
	dfs(0);
	for (int i = 0; i < n; i++)
	{
		cout << (ans[pairs[i][0]][pairs[i][2]] == 0 ? 
			ans[pairs[i][1]][pairs[i][3]] : 
		ans[pairs[i][0]][pairs[i][2]]) << endl;
	}
	return 0;
}