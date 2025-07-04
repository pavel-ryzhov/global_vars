#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector < set<int> > graph;
typedef vector< map<int, int> > edges_type;
typedef set<int>::const_iterator const_graph_iter;


vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;

void lca_dfs (const graph & g, const edges_type &e, int v, int h = 0)
{
	
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[*i])
		{
			map<int, int> buff = e[v];
			lca_dfs (g, e, *i, h + buff.find(*i)->second);
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

void lca_prepare (const graph & g, const edges_type &e, int root)
{
	int n = (int) g.size();
	lca_h.resize (n);
	lca_dfs_list.reserve (n*2);
	lca_dfs_used.assign (n, 0);

	lca_dfs (g, e, root);

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

void g_input(graph &g, edges_type &e, vector<int> &t)
{
	//чтение графа
/*		int init[42] = {9,
					1, 2, 0,
					2, 9, 5,
					3, 9, 0,
					4, 9, 8,
					5, 9, 7,
					6, 8, 2,
					7, 5, 0,
					8, 7, 1,
					8,
					6, 5,
					2, 3,
					3, 3,
					4, 1,
					3, 7,
					3, 6,
					5, 7,
					8, 2};
	vector<int> input(init, init+42);*/
	vector<int> input;
	vector<int>::iterator it_input;
	copy(istream_iterator<int>(cin),istream_iterator<int>(), back_inserter(input));
	
	int n =  *input.begin();
	g.resize(n);
	e.resize(n);

	for(int i=1; i<(n-1)*3; i=i+3) {
		int a = input.at(i)-1;
		int b = input.at(i+1)-1;
		g[a].insert(a); e[a].insert(pair<int,int>(a, 0));
		g[a].insert(b); e[a].insert(pair<int,int>(b, input.at(i+2)));
		g[b].insert(a); e[b].insert(pair<int,int>(a, input.at(i+2)));
	}
	
	t.resize(*(input.begin()+3*(n-1)+1)*2);
	copy(input.begin()+3*(n-1)+2, input.end(), t.begin());
}

int main()
{
	graph g;
	edges_type e;
	vector<int> t;

	int root = 0,
		v1 = 2, v2 = 3;
	g_input(g, e, t);

	lca_prepare (g, e, root);
	for(vector<int>::iterator i = t.begin(); i-t.begin() < t.size(); i=i+2) {
		cout << lca_h[*i-1] + lca_h[*(i+1)-1] - 2*lca_h[lca(*i-1, *(i+1)-1)] << endl;
	}
	return 0;
}