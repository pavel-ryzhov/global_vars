#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>


using	 namespace std;



typedef vector < vector<pair <int, int> > > graph;
typedef vector<pair <int, int> >::const_iterator const_graph_iter;


vector<int>  lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;
vector<pair<int,int> > lca_h;

void lca_dfs (const graph & g, int v, pair <int,int> h = make_pair(1, 0))
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[(*i).first])
		{
			lca_dfs (g, (*i).first, make_pair(h.first+1,h.second+(*i).second));
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
	graph g;
	int root=1;
	int n;
	
	scanf("%d", &n);
	g.resize(n+1);
	
	for (int i = 0; i < (n-1); ++i)
	{
		int a, b, w = 0;
		scanf("%d %d %d", &a, &b, &w);
		g[a ].push_back(make_pair(b,w));
		g[b ].push_back(make_pair(a,w));
	}
	
	lca_prepare (g, root);
	cout << "lca_h" << endl;
	for (vector<pair<int,int> >::iterator i=lca_h.begin(); i!=lca_h.end(); ++i) {
		cout << "( " <<i->first <<" , "<< i->second<< " )" << " ; ";
	}
	cout << endl;
	
/*	cout << "lca_first" << endl;
	for (vector<int>::iterator i=lca_first.begin(); i!=lca_first.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	
	/*
	cout << "lca_tree" << endl;
	for (vector<int>::iterator i=lca_tree.begin(); i!=lca_tree.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	*/
/*	cout << "lca_dfs_list" << endl;
	for (vector<int>::iterator i=lca_dfs_list.begin(); i!=lca_dfs_list.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
*/	
	int m;
	scanf("%d", &m);
	for (int j=0; j<m; ++j) {
		int a, b; // текущий запрос
		scanf("%d %d", &a, &b);
		if (a==b) {
			cout << 0 << endl;
		}
		else {
			int res=lca(a,b);
			cout << lca_h[a].second+lca_h[b].second-2*lca_h[res].second << endl;
		}
	}
	return 0;
}