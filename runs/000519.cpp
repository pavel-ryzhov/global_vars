#include <iostream>
#include <vector>
using namespace std;

//point in tree
class Tp{
public:
	int parent;
	int len_to_parent;
	vector<int> children;
	Tp(){len_to_parent=0;parent=0;};
};

typedef vector < Tp > graph;
typedef vector<int>::const_iterator const_graph_iter;
vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;

void lca_dfs (const graph & g, int v, int h = 1)
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].children.begin(); i != g[v].children.end(); ++i)
		if (!lca_dfs_used[*i])
		{
			lca_dfs (g, *i, h+1);
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
	if (root==-1) return;
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

const unsigned int MAXN = 40000;

graph g;
vector<int> freepoints;

void addchild(int par, int child, int plen){
	int len = g[par].children.size();
	g[par].children.resize(len+1);
	g[par].children[len] = child;
	g[child].len_to_parent = plen;
	g[child].parent = par;
}

void addfreepoints(int p1, int p2, int plen){
	int len=freepoints.size();
	freepoints.resize(len+3);
	freepoints[len] = p1;
	freepoints[len+1] = p2;
	freepoints[len+2] = plen;
}

void matchfreepoints(){
	for (int i=0; i<freepoints.size(); i=i+3){
		int p1, p2, len;
		p1 = freepoints[i];
		p2 = freepoints[i+1];
		len = freepoints[i+2];
		if (g[p1].parent == 0 && g[p2].parent == 0) continue;
		if (g[p1].parent == 0) swap(p1,p2);
		addchild(p1, p2, len);
		freepoints.erase(freepoints.begin()+i, freepoints.begin()+i+3);
		i=0;
	}
}

int main()
{
	int root=-1;
	int n;
	cin >> n;
	g.resize(MAXN+1);
	freepoints.resize(0);

	//reading data
	for (int i=0; i<n-1; i++)
	{
		int start, end, rlen;
		cin >> start >> end >> rlen;
		if (root==-1) root = start;
		bool hasroot = start==root || end==root;
		matchfreepoints();
		if (g[end].parent==0 && g[start].parent==0 && !hasroot){
			addfreepoints(start, end, rlen);
			continue;
		}
		if (g[start].parent == 0 && start!=root) swap(start, end);
		addchild(start, end, rlen);
	}
	matchfreepoints();
	int m;
	cin >> m;
	lca_prepare (g, root);
	
	//reading requests
	for (int i=0; i<m; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;

		if (v1==v2){//just in case
			cout << 0 << endl;
			continue;
		}

		int v = lca (v1, v2); // answer (min parent)
		int count=0; //count path length
		while (v1 != v){
			count += g[v1].len_to_parent;
			v1 = g[v1].parent;
		}
		while (v2 != v){
			count += g[v2].len_to_parent;
			v2 = g[v2].parent;
		}
		cout << count << endl; //answer
	}
}
