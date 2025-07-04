// YandeB.cpp : main project file.

#include <iostream>
#include <vector>

using namespace std;

struct LPoint
{
	int l;
	int point;
};

typedef vector <LPoint> neighbours;
typedef vector <neighbours> graph;
typedef vector <LPoint>::const_iterator const_graph_iter;


vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;

void lca_dfs (const graph & g, int v, int h = 1)
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[(*i).point])
		{
			lca_dfs (g, (*i).point, h+(*i).l);
			lca_dfs_list.push_back (v);
		}
}

void lca_build_tree (int i, int l, int r)
{
	if (l == r)
		lca_tree[i] = lca_dfs_list[l];
	else
	{
		int m = (l + r) >> 1;
		lca_build_tree (i+i, l, m);
		lca_build_tree (i+i+1, m+1, r);
		if (lca_h[lca_tree[i+i]] < lca_h[lca_tree[i+i+1]])
			lca_tree[i] = lca_tree[i+i];
		else
			lca_tree[i] = lca_tree[i+i+1];
	}
}

void lca_prepare (const graph & g, int root)
{
	int n = (int) g.size();
	lca_h.resize (n);
	lca_dfs_list.reserve (n*2);
	lca_dfs_used.assign (n, 0);

	lca_dfs (g, root);

	int m = (int) lca_dfs_list.size();
	lca_tree.assign (lca_dfs_list.size() * 4 + 1, -1);
	lca_build_tree (1, 0, m-1);

	lca_first.assign (n, -1);
	for (int i = 0; i < m; ++i)
	{
		int v = lca_dfs_list[i];
		if (lca_first[v] == -1)
			lca_first[v] = i;
	}
}

int lca_tree_min (int i, int sl, int sr, int l, int r)
{
	if (sl == l && sr == r)
		return lca_tree[i];
	int sm = (sl + sr) >> 1;
	if (r <= sm)
		return lca_tree_min (i+i, sl, sm, l, r);
	if (l > sm)
		return lca_tree_min (i+i+1, sm+1, sr, l, r);
	int ans1 = lca_tree_min (i+i, sl, sm, l, sm);
	int ans2 = lca_tree_min (i+i+1, sm+1, sr, sm+1, r);
	return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca (int a, int b)
{
	int left = lca_first[a],
		right = lca_first[b];
	if (left > right)  swap (left, right);
	return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int main()
{
//	freopen("input.txt", "rt", stdin);
//	freopen("output.txt", "wt", stdout);

	graph g;
	LPoint tpoint;
	int root=1;
	int n,i,x1,x2,l;
	cin >> n;
	g.resize(n+1);
	for (i=1; i<n; i++)
	{
		cin >>x1;
		cin >>x2;
		cin >>l;
		tpoint.l=l;
		tpoint.point=x2;
		g[x1].push_back(tpoint);
		tpoint.point=x1;
		g[x2].push_back(tpoint);
	}

	lca_prepare (g, root);
	int m;
	cin >>m;
	int v,v1,v2,ans;
	for (i=0;i<m;i++)
	{
		cin >>v1 >>v2; // поступил запрос
		v = lca (v1, v2); // ответ на запрос
		ans=lca_h[v1]+lca_h[v2]-2*lca_h[v];
		cout <<ans <<endl;
	}
	return 0;
}
