#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector < vector<int> > graph;
typedef map <set<int>, int> edges_type;
typedef vector<int>::const_iterator const_graph_iter;


vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;

void lca_dfs (const graph & g, edges_type &e, int v, int h = 0)
{
	
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[*i])
		{
			set<int> buff;
			buff.insert(*i);
			buff.insert(v);
			lca_dfs (g, e, *i, h + e.find(buff)->second);
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

void lca_prepare (const graph & g, edges_type &e, int root)
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
	vector<int> input;
	vector<int>::iterator it_input;
	copy(istream_iterator<int>(cin),istream_iterator<int>(), back_inserter(input));
	int i = 0;
	int n =  *input.begin();
	for(;i<n;i++)
		g.push_back(vector<int>());	
	
	for (i=1;i<=*(input.begin());i++) { //здесь точки заполняются связями
		g[i-1].push_back(i-1);

		set<int> buff;
		buff.insert(input.at((i-1)*3+1)-1);
		buff.insert(input.at((i-1)*3+2)-1);
		e.insert(pair<set<int>, int>(buff,
									 input.at((i-1)*3+3)));

		for (it_input = input.begin()+1; it_input < input.begin()+(n-1)*3; it_input = it_input + 3) {
			if (*it_input==i)
				g[i-1].push_back(*(it_input+1)-1);
			else
				if(*(it_input+1)==i)
					g[i-1].push_back(*it_input-1);
		}
	} //заполнились

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