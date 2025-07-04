#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
  Edge(int n = 0, int w = 0)
  {
    this->n = n;
    this->w = w;
  }

  int n;
  int w;
};

vector<int> tin, tout;
vector<bool> b;
vector < vector<int> > up;
vector < vector<Edge> > g;
vector<int> d;
int t;
int n, l;

void ReadData()
{
  cin >> n;
  t = 0;
  b.resize(n);
  up.resize(n);
  g.resize(n);
  tin.resize(n);
  tout.resize(n);
  d.resize(n);
  d[0] = 0;

  l = 1;
  while ((1 << l) <= n) 
    l++;
  for (int i = 0; i < n; i++)
    up[i].resize(l + 1);

  for (int i = 0; i < n - 1; i++)
  {
    int x, y, w;
    cin >> x >> y >> w;
    x--; 
    y--;
    g[x].push_back( Edge(y, w) );
    g[y].push_back( Edge(x, w) );
  }
}

void DFS(int v, int p)
{
  b[v] = true;
  tin[v] = t++;
  up[v][0] = p;

  for (int i = 1; i <= l; i++)
    up[v][i] = up[up[v][i - 1]][i - 1];

  for (int i = 0; i < g[v].size(); i++)
  {
    int next = g[v][i].n;
    if (!b[next])
    {
      d[next] = d[v] + g[v][i].w;
      DFS(next, v);
    }
  }

  tout[v] = t++;
}

bool Upper(int x, int y)
{
  return (tin[x] <= tin[y]) && (tout[y] <= tout[x]);
}

int GetLCA(int x, int y)
{
  if (Upper(x, y))
    return x;
  if (Upper(y, x))
    return y;

  for (int i = l; i >= 0; i--)
  {
    if ( !Upper(up[x][i], y) )
      x = up[x][i];
  }

  return up[x][0];
}

int GetDist(int x, int y)
{
  int lca = GetLCA(x, y);
  int dist = d[x] + d[y] - 2 * d[lca];
  return dist;
}

void Solve()
{
  DFS(0, 0);

  int m;
  cin >> m;
  for (int i  = 0; i < m; i++)
  {
    int x, y, dist;
    cin >> x >> y;
    x--;
    y--;
    dist = GetDist(x, y);
    cout << dist << endl;
  }
}

int main()
{
  //freopen("test.in", "r", stdin);
  //freopen("test.out", "w", stdout);
  ReadData();
  Solve();
	return 0;
}
