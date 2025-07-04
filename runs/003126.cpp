#include <vector>
#include <iostream>

using namespace std;

typedef vector< vector<unsigned int*> > graph;
typedef vector<unsigned int *>::const_iterator const_graph_iter;

vector<unsigned int> lca_h, lca_dfs_list, lca_first, lca_tree, names;
vector<unsigned long> lca_hw;

vector<char> lca_used;

graph g;

void lca_dfs (unsigned int v, unsigned int h = 1, unsigned long hw = 0)
{
	lca_used[v] = 1;
	lca_h[v] = h;
	lca_hw[v] = hw;

	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
	{
		unsigned int index_of_child = (*i)[0];
		if(lca_used[index_of_child]==0)
		{
			lca_dfs ( (*i)[0] , h+1, hw + (*i)[1]);
			lca_dfs_list.push_back (v);
        }
	}
}

void lca_build_tree (unsigned int i, unsigned int l, unsigned int r)
{
	if (l == r)
		lca_tree[i] = lca_dfs_list[l];
	else
	{
		unsigned int m = (l + r) >> 1;
		lca_build_tree (i+i, l, m);
		lca_build_tree (i+i+1, m+1, r);
		if (lca_h[lca_tree[i+i]] < lca_h[lca_tree[i+i+1]])
			lca_tree[i] = lca_tree[i+i];
		else
			lca_tree[i] = lca_tree[i+i+1];
	}
}

void lca_prepare (unsigned int n)
{

	lca_h.resize (n);
	lca_hw.resize(n);
	lca_used.assign(n,0);
	lca_dfs_list.reserve (n*2);

	lca_dfs (0);

	unsigned int m = lca_dfs_list.size();
	lca_tree.assign (m * 4 + 1, 40001);
	lca_build_tree (1, 0, m-1);

	lca_first.assign (n, 40001);
	for (unsigned int i = 0; i < m; ++i)
	{
		unsigned int v = lca_dfs_list[i];
		if (lca_first[v] == 40001)
			lca_first[v] = i;
	}
}

int lca_tree_min (unsigned int i, unsigned int sl, unsigned int sr, unsigned int l, unsigned int r)
{
	if (sl == l && sr == r)
		return lca_tree[i];
	unsigned int sm = (sl + sr) >> 1;
	if (r <= sm)
		return lca_tree_min (i+i, sl, sm, l, r);
	if (l > sm)
		return lca_tree_min (i+i+1, sm+1, sr, l, r);
	unsigned int ans1 = lca_tree_min (i+i, sl, sm, l, sm);
	unsigned int ans2 = lca_tree_min (i+i+1, sm+1, sr, sm+1, r);
	return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

unsigned int lca (unsigned int a, unsigned int b)
{
	unsigned int left = lca_first[a], right = lca_first[b];
	if (left > right)  swap (left, right);
	unsigned int var = lca_dfs_list.size()-1;
	return lca_tree_min (1, 0, var , left, right);
}

unsigned long get_distance(unsigned int a, unsigned b)
{
	unsigned int lca_a_b = lca(a,b);
	return lca_hw[a] - lca_hw[lca_a_b] + lca_hw[b] - lca_hw[lca_a_b];
}

unsigned int get_index(unsigned int vertex)
{
	unsigned int index;
	for(index=0; index < names.size();index++)
		if(names[index]==vertex) break;

	if(index == names.size())
		names.push_back(vertex);

	return index;
}

void free_memory(unsigned int N)
{
	for(unsigned int i=0; i<N;i++)
	{
		for(unsigned int j=0; j<g[i].size();j++)
		{
			delete[] g[i][j];
			g[i][j]=0;
        }
	}
}

int main()
{
	 unsigned int N,a,b,w;
	 cin>>N;

	 for(unsigned int i=0; i<N; i++)
	 {
		vector<unsigned int *> edges_for_vertex;
		g.push_back(edges_for_vertex);
	 }

	 for(unsigned int i=0;i<N-1;i++)
	 {
		cin>>a>>b>>w;

		unsigned int first = get_index(a);
		unsigned int second = get_index(b);

		//if( first > second) swap(first,second);

		unsigned int * edge = new unsigned int[2];
		edge[0] = second;
		edge[1] = w;
		g[first].push_back(edge);

		unsigned int * edge2 = new unsigned int[2];
		edge2[0] = first;
		edge2[1] = w;
		g[second].push_back(edge2);
	 }
	 lca_prepare (N);

	 unsigned int M;
	 cin>>M;
	 for(unsigned int i=0; i< M;i++)
	 {
		unsigned int a,b;
		cin>>a>>b;

		unsigned int first = get_index(a);
		unsigned int second = get_index(b);

		cout<<get_distance (first, second)<<endl;
	 }

	 free_memory(N);
	 return 0;
}