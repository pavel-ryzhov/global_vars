#include <iostream>
#include <vector>

using namespace std;

typedef pair<int,int> intpair;
typedef vector< vector<intpair> > graph;
typedef vector<intpair>::const_iterator const_graph_iter;


vector<int> lca_h, lca_dfs_list, lca_first, lca_tree, lca_w_list;
vector<char> lca_dfs_used;
int wh=0;

void lca_dfs (const graph & g, int v, int h = 1) //поиск в глубину
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[i->first])
		{
		    wh+=i->second;
		    lca_w_list[i->first]=wh;
			lca_dfs (g, i->first, h+1);
			wh-=i->second;
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
	lca_w_list.resize(n); //массив с расстояниями до корня
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

int main(int argc, char* argv[]){
	graph g;
    int N=0,M=0,root=1;
    cin >> N;
    int beg, end, weight;
    
    g.resize(N+1);
    for(int i=0;i<N-1;i++){
        cin >> beg >> end >> weight;
        if(i==0) root=beg;
        g[beg].push_back(intpair(end,weight));
        g[end].push_back(intpair(beg,weight));
    }
    lca_prepare (g, root);
    cin >> M;
    for(int i=0;i<M;i++){
        cin >> beg >> end;
        cout << (lca_w_list[beg]+lca_w_list[end]-2*lca_w_list[lca (beg,end)])<<endl;
    }
    return 0;
}

