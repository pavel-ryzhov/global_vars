#include <cstdio>
#include <vector>
using namespace std;

int n;
typedef pair<int,int> vertex;
vector<vector<int> > up;
vector<vector<long long> > dist;
vector<vector<vertex> > adj;
vector<int> in,out;
int h;
int timer;

void Input()
{
	scanf("%d", &n);
	int from, to, value;
	adj = vector<vector<vertex> > (n);
	in.resize(n);
	out.resize(n);
	h = 1;
	while((1<<h) <= n) h++;
	up = vector<vector<int> > (n, vector<int>(h + 1, 0));
	dist = vector<vector<long long> > (n + 1, vector<long long>(h + 1,0));

	for(int i = 0; i < n - 1; ++i)
	{
		scanf("%d %d %d", &from, &to, &value);
		-- from; -- to;
		adj[from].push_back(vertex(to, value));
		adj[to].push_back(vertex(from, value));
	}
}

void Dfs(int vert, int prev, int d)
{
	in[vert] = ++ timer;
	up[vert][0] = prev;
	dist[vert][0] = d;
	for (int i = 1; i <= h; ++i)
	{
		up[vert][i] = up[up[vert][i-1]][i-1];
		dist[vert][i] = dist[vert][i-1] + dist[up[vert][i-1]][i-1];
	}

	for (int i=0; i<adj[vert].size(); ++i) 
	{
		vertex nextVert = adj[vert][i];
		if (!in[nextVert.first])
			Dfs (nextVert.first, vert, nextVert.second);
	}
	out[vert] = ++ timer;
}

bool upper(int a, int b)
{
	return in[a] <= in[b] && out[a] >= out[b];
}


int Lca (int a, int b) 
{
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=h; i>=0; --i)
		if (! upper (up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

long long Distance(int from, int common)
{
	if (upper(from, common)) swap(from, common);
	long long res = 0;
	for(int i = h;i >= 0; --i)
	{
		if (up[from][i] == common)
		{
			res += dist[from][i];
			break;
		}
		else if (!upper(up[from][i], common))
		{
			res += dist[from][i];
			from = up[from][i];
		}
	}
	return res;
}

void ReadQueries()
{
	int m;
	scanf("%d", &m);
	int from, to;
	for(int i = 0; i < m; ++i)
	{
		scanf("%d %d", &from, &to);
		--from; --to;
		int common = Lca(from, to);
		printf("%ld\n", Distance(from,common) + Distance(to,common));
	}
}

int main()
{
	Input();
	Dfs(0,0,0);
	ReadQueries();
	return 0;
}