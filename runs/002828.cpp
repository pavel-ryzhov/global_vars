#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef vector < vector<int> > graph;
typedef vector<int>::const_iterator const_graph_iter;
graph dist;


vector<int> lca_h, lca_dfs_list, lca_first, lca_tree, lca_dist;
vector<char> lca_dfs_used;

void lca_dfs (const graph & g, int v, int h , int myD)
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dist[v]=myD;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[*i])
		{
			lca_dfs (g, *i, h+1,dist[v][*i]+myD);
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
	lca_dist.resize(n);
	lca_dfs_list.reserve (n*2);
	lca_dfs_used.assign (n, 0);

	lca_dfs (g, root,1,0);

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
	graph g;	/*Граф*/
	int root;	/*Корень*/
	int max_n;	/*Количество вершин*/
	int x,y,l;	/*Параметры ребер*/
	int amt_q;
	
	/*Чтение количества вершин*/
	scanf("%d",&max_n);

	g.resize(max_n);

	dist.resize(max_n);
	for(int i=0;i<max_n;i++){
		dist[i].resize(max_n,-1);
	}

	/*Чтение параметров ребер*/
	for(int i = 0; i != max_n-1; i++){
		scanf("%d %d %d",&x,&y,&l);
		--x,--y;
		dist[x][y] = dist[y][x]= l;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	
	root=0;
	lca_prepare (g, root);
	/*Чтение количества запросов*/
	scanf("%d",&amt_q);
	for (int i = 0;i<amt_q;i++)
	{
		scanf("%d %d",&x,&y); // поступил запрос
		--x;--y;
		int v = lca (x, y); // ответ на запрос
		cout<<lca_dist[x]+lca_dist[y] - 2*lca_dist[v]<<endl;
	}
}