#include <vector>
#include <stdio.h>
#include <string>
#include <map>
#include <algorithm>
using std::vector;
using std::multimap;
typedef vector < vector<int> > graph;
typedef std::pair<int,int> pairint;
typedef vector<int>::const_iterator const_graph_iter;


vector<int> lca_h, lca_dfs_list, lca_first, lca_tree, lca_dfs_list2;
vector<int> lca_dfs_used;

void lca_dfs (const graph & g, int v, int h = 1)
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[*i])
		{
			lca_dfs (g, *i, h+1);
			lca_dfs_list.push_back (v);
		}
	
	lca_dfs_list2=vector<int>(lca_dfs_list.begin(),lca_dfs_list.end());
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
	if (left > right)  std::swap (left, right);
	return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int main()
{
	graph g;
	int root;

    multimap<int,int> keyleft,keyright;
	std::pair<int,int> rib;
	std::pair<std::pair<int,int>,int> weight;
	std::map<std::pair<int,int>,int> w;
	
	int N;
	scanf("%d",&N);
	g.resize(N);
	for(int i=1;i<=N-1;++i)
	{
		scanf("%d%d%d",&rib.first,&rib.second,&weight.second);
		--rib.first;--rib.second;
		weight.first=rib;
		keyleft.insert(rib);
		w.insert(weight);

		int k;
		k=rib.first;
		rib.first=rib.second;
		rib.second=k;
		keyright.insert(rib);
	}

	for(int i=0;i<=N-1;i++)
	{
		multimap<int,int>::iterator iter=keyleft.lower_bound(i);
		int k=0;
		for(;iter!=keyleft.upper_bound(i);iter++)
		{
            g[i].resize(k+1);
			g[i][k]=iter->second;
			++k;
		}

		iter=keyright.lower_bound(i);
		for(;iter!=keyright.upper_bound(i);iter++)
		{
			g[i].resize(k+1);
			g[i][k]=iter->second;
			++k;
		}
	}

	int M;
	scanf("%d",&M);
	vector<pairint> vpair(M);
	for (int i=0;i<=M-1;++i)
	{
		scanf("%d%d",&vpair[i].first,&vpair[i].second);
		--vpair[i].first;--vpair[i].second;
	}


	for(int i=0;i<=M-1;++i)
	{
		int v1, v2;
		v1=vpair[i].first;
		v2=vpair[i].second;
		root=v1;
        lca_prepare (g, root);

		int v = lca (v1, v2);
		
		int vv1 = lca_first[v1];
		int vv2 = lca_first[v2];
	    if (vv1 > vv2)  std::swap (vv1, vv2); 
		int sum=0;

		lca_dfs_list2.erase(lca_dfs_list2.begin()+vv2+1,lca_dfs_list2.end());
		lca_dfs_list2.erase(lca_dfs_list2.begin(),lca_dfs_list2.begin()+vv1);
        vector<int>::iterator iter=lca_dfs_list2.begin();

		while(iter!=lca_dfs_list2.end())
		{
			vector<int>::iterator x1 = std::find(lca_dfs_list2.begin(),lca_dfs_list2.end(),*iter);
			int x1_index = x1-lca_dfs_list2.begin();
			vector<int>::reverse_iterator x2 = std::find(lca_dfs_list2.rbegin(),lca_dfs_list2.rend()-x1_index,*iter);
			int x2_index = lca_dfs_list2.size()-1-(x2-lca_dfs_list2.rbegin());
			if(x1_index!=x2_index){lca_dfs_list2.erase(lca_dfs_list2.begin()+x1_index+1,lca_dfs_list2.begin()+x2_index+1);}
			else ++iter;
		}
		
		for(vector<int>::iterator iter=lca_dfs_list2.begin();iter<lca_dfs_list2.end()-1;++iter)
		{
             int x=*iter;
			 int y=*(iter+1);
			 std::pair<int,int> pair=std::pair<int,int>(x,y);
			 if(w.find(pair)!=w.end()) sum+=w[pair];
			 else
			 {
                 pair=std::pair<int,int>(y,x);
				 sum+=w[pair];
			 }
		}
		printf("%d",sum);
		printf("%s","\n");
	}

}