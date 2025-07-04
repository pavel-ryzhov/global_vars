#include <vector>
#include <iostream>
#include <string.h>

using std::cin;
using std::vector;
using std::swap;
using std::cout;
using std::endl;

typedef vector< vector<int*> > graph;

const int MAXN = 40001;
int lca_h[MAXN];
int lca_first[MAXN];
int lca_hw[MAXN];
vector<int> lca_dfs_list, lca_tree;

graph Graph;

void lca_dfs (int v, int h = 0, int hw = 0)
{
	lca_h[v] = h;
	lca_hw[v] = hw;

	lca_first[v] = lca_dfs_list.size();
	lca_dfs_list.push_back (v);

	for (size_t i=0; i<Graph[v].size(); ++i)
		if (lca_h[Graph[v][i][0]] == -1)
		{
			lca_dfs (Graph[v][i][0], h+1, hw + Graph[v][i][1]);
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

void lca_prepare (int n)
{
	memset( lca_h, -1, MAXN*sizeof(int));

	lca_dfs_list.reserve (n*2);
	lca_dfs (1);

	int m = lca_dfs_list.size();
	lca_tree.assign (m * 4 + 1, -1);
	lca_build_tree (1, 0, m-1);
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
	int left = lca_first[a], right = lca_first[b];
	if (left > right)  swap (left, right);
	int var = lca_dfs_list.size()-1;
	return lca_tree_min (1, 0, var , left, right);
}

int get_distance(int a, int b)
{
	int lca_a_b = lca(a,b);
	return lca_hw[a] - lca_hw[lca_a_b] + lca_hw[b] - lca_hw[lca_a_b];
}

void free_memory(int N)
{
	for(int i=0; i<=N;i++)
	{
		for(int j=0; j<Graph[i].size();j++)
		{
			delete[] Graph[i][j];
			Graph[i][j]=0;
		}
	}
}

int main()
{
	 int N,a,b,w;
	 cin>>N;

	 for(int i=0; i<=N; i++)
	 {
		vector<int *> edges_for_vertex;
		Graph.push_back(edges_for_vertex);
	 }

	 int num_of_edges = N-1;

	 for(int i=0; i<num_of_edges; i++)
	 {
		cin>>a>>b>>w;

		int * edge = new int[2];
		edge[0] = b;
		edge[1] = w;
		Graph[a].push_back(edge);

		int * edge2 = new int[2];
		edge2[0] = a;
		edge2[1] = w;
		Graph[b].push_back(edge2);
	 }
	 lca_prepare(N);

	 int M;
	 cin>>M;

	 for(int i=0; i< M;i++)
	 {
		cin>>a>>b;
		cout<<get_distance(a, b)<<endl;
	 }

	 free_memory(N);
	 return 0;
}