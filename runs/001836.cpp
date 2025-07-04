#include <iostream>
#include <vector>

using namespace std;

typedef int vertex;
typedef int weight;
typedef pair<vertex, weight> edge;
typedef vector<edge> edge_list;

vector<edge_list> graph;
vector<bool> visited;
vector<vertex> order;
vector<int> first;
vector<weight> height;
const vertex undefined = -1;

vertex min_vertex(vertex u, vertex v)
{
	vertex res = u;
	if (v != undefined && height[v] < height[u])
		res = v;
	return res;
}

void make_rmq(vector<vertex>& a)
{
	int n = 1;
	while (n < a.size())
		n *= 2;
	a.insert(a.end(), n - a.size(), undefined);
	a.insert(a.begin(), n-1, undefined);
	for (int i = n-1; i >= 0; --i)
		a[i] = min_vertex(a[i+i+1], a[i+i+2]);
}

vertex rmq(const vector<vertex>& a, int l, int r)
{
	int shift = a.size() / 2;
	l += shift;
	r += shift;
	vertex res = a[l];
	while (l <= r)
	{
		res = min_vertex(res, a[l]);
		res = min_vertex(res, a[r]);
		l = l/2;
		r = r/2 - 1;
	}
	return res;
}

bool dfs(vertex v, weight h)
{
	if (visited[v])
		return false;

	visited[v] = true;
	height[v] = h;
	order.push_back(v);

	for (edge_list::iterator u = graph[v].begin(); u != graph[v].end(); ++u)
		if (dfs(u->first, h + u->second))
			order.push_back(v);
	
	return true;
}

void prepare_lca()
{
	visited.resize(graph.size());
	height.resize(graph.size());
	first.resize(graph.size());
	dfs(0, 0);
	for (int i = order.size() - 1; i >= 0; --i)
		first[order[i]] = i;
	make_rmq(order);
}

vertex lca(vertex u, vertex v)
{
	if (first[v] < first[u])
	{
		vertex tmp = u;
		u = v;
		v = tmp;
	}
	return rmq(order, first[u], first[v]);
}

int main()
{
	int n, m;
	vertex u, v;
	weight w;
	cin >> n;
	graph.resize(n);
	for (int i = 0; i < n-1; ++i)
	{
		cin >> u >> v >> w;
		--u; --v;
		graph[u].push_back(edge(v, w));
		graph[v].push_back(edge(u, w));
	}

	prepare_lca();

	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		--u; --v;
		cout << height[u] - 2*height[lca(u, v)] + height[v] << endl;
	}

	return 0;
}
