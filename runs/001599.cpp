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

vector<int> lca_dfs_list;
vector<int> lca_dfs_used;
int v2;
bool endflag;
void lca_dfs (const graph & g, int v)
{
	lca_dfs_used[v] = true;
	lca_dfs_list.push_back (v);
	if (v==v2){endflag=true;return;}
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[*i])
		{
			lca_dfs (g, *i);
			if(endflag)return;
			lca_dfs_list.erase(lca_dfs_list.end()-1);
		}
}

void lca_prepare (const graph & g, int root)
{
	int n = (int) g.size();
	lca_dfs_list.clear();
	lca_dfs_list.reserve (n*2);
	lca_dfs_used.assign (n, 0);

	endflag=false;
	lca_dfs (g, root);

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
		keyleft.insert(rib);
		weight.first=rib;
		w.insert(weight);
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
		int v1;
		v1=vpair[i].first;
		v2=vpair[i].second;
		root=v1;
        lca_prepare (g, root);
		int sum=0;
		
		for(vector<int>::iterator iter=lca_dfs_list.begin();iter<lca_dfs_list.end()-1;++iter)
		{
             int x=*iter;
			 int y=*(iter+1);
			 std::pair<int,int> pair=std::pair<int,int>(x,y);
			 sum+=w[pair];
		}
		printf("%d",sum);
		printf("%s","\n");
	}

}
