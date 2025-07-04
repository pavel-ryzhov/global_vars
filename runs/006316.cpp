#include <stdio.h>
#include <vector>

using namespace std;

struct out_edge
{
	int dst_vertex;
	int length;
	out_edge(int _dst_vertex = -1, int _length = -1) :
		dst_vertex(_dst_vertex),
		length(_length)
	{}
};

typedef vector< vector<out_edge> > graph;

vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<bool> lca_dfs_visited;

void lca_dfs(const graph& g, int v, int h = 1)
{
	lca_dfs_visited[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back(v);
	for (int i = 0; i < g[v].size(); ++i)
		if (!lca_dfs_visited[g[v][i].dst_vertex])
		{
			lca_dfs (g, g[v][i].dst_vertex, h + g[v][i].length);
			lca_dfs_list.push_back(v);
		}
}

void lca_build_tree(int i, int l, int r)
{
	if (l == r)
		lca_tree[i] = lca_dfs_list[l];
	else
	{
		int m = (l + r) >> 1;
		lca_build_tree(i+i, l, m);
		lca_build_tree(i+i+1, m+1, r);
		if (lca_h[lca_tree[i+i]] < lca_h[lca_tree[i+i+1]])
			lca_tree[i] = lca_tree[i+i];
		else
			lca_tree[i] = lca_tree[i+i+1];
	}
}

void lca_prepare(const graph& g, int root)
{
	int n = (int) g.size();
	lca_h.resize(n);
	lca_dfs_list.reserve(n*2);
	lca_dfs_visited.assign(n, false);

	lca_dfs(g, root);

	int m = (int) lca_dfs_list.size();
	lca_tree.assign(m*4 + 1, -1);
	lca_build_tree(1, 0, m-1);

	lca_first.assign(n, -1);
	for (int i = 0; i < m; ++i)
	{
		int v = lca_dfs_list[i];
		if (lca_first[v] == -1)
			lca_first[v] = i;
	}
}

int lca_tree_min(int i, int sl, int sr, int l, int r)
{
	if (sl == l && sr == r)
		return lca_tree[i];
	int sm = (sl + sr) >> 1;
	if (r <= sm)
		return lca_tree_min(i+i, sl, sm, l, r);
	if (l > sm)
		return lca_tree_min(i+i+1, sm+1, sr, l, r);
	int ans1 = lca_tree_min(i+i, sl, sm, l, sm);
	int ans2 = lca_tree_min(i+i+1, sm+1, sr, sm+1, r);
	return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca(int a, int b)
{
	int left = lca_first[a],
		right = lca_first[b];
	if (left > right)  swap (left, right);
	return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int min_length(int a, int b)
{
	return lca_h[a] + lca_h[b] - 2*lca_h[lca(a, b)];
}

int main()
{
	graph g;
	int n;
	scanf("%i\n", &n);
	g.resize(n);
	for (int i = 0; i < n-1; ++i)
	{
		int src, dst, len;
		scanf("%i %i %i\n", &src, &dst, &len);
		g[src-1].push_back(out_edge(dst-1, len));
		g[dst-1].push_back(out_edge(src-1, len));
	}
	lca_prepare(g, 0);

	int m;
	scanf("%i\n", &m);
	for (int i = 0; i < m; ++i)
	{
		int src, dst;
		scanf("%i %i\n", &src, &dst);
		printf("%i\n", min_length(src-1, dst-1));
	}
}
