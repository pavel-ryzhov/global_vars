#include <vector>
#include <stdio.h>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
using std::vector;
using std::pair;
using std::multimap;
typedef vector < vector<int> > graph;
typedef std::pair<int,int> pairint;
typedef vector<int>::const_iterator const_graph_iter;

const int maxsize = 500;
vector < vector <pair<int, int> > > g;
vector <bool> used(maxsize);
int depth[maxsize]; int parent[maxsize]; int depth_bin[maxsize];
int way = 0, way_bin = 0;

void dfs (int v, int lastleng, int from)
{
    used[v] = true;
    parent[v] = from;
	depth[v] = way;
	depth_bin[v] = way_bin;

	for (size_t i=0; i<g[v].size(); i++)
	{
		int CurrentNode = g[v][i].first;
		int CurrentLen = g[v][i].second;
		if (!used[CurrentNode]) {
			way += CurrentLen;
			way_bin++;
			dfs (CurrentNode, CurrentLen, v);
		}
	}
	way_bin--;
	way -= lastleng;
}


int main()
{
	graph g2;
	int root;

    multimap<int,int> keyleft;
	std::pair<int,int> rib;
	std::pair<std::pair<int,int>,int> weight;
	std::map<std::pair<int,int>,int> w;
	
	int N;
	scanf("%d",&N);
	g2.resize(N);
	for(int i=1;i<=N-1;++i)
	{
		scanf("%d%d%d",&rib.first,&rib.second,&weight.second);
		--rib.first;--rib.second;
		weight.first=rib;
		keyleft.insert(rib);
		w.insert(weight);

		std::swap(rib.first,rib.second); 
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
            g2[i].resize(k+1);
			g2[i][k]=iter->second;
			++k;
		}
	}
     
	g= vector < vector <pair<int, int> > >(N);
	for(int i=0;i<=N-1;i++)
	{
		g[i].resize(g2[i].size());
		for(int k=0;k<g2[i].size();++k)
		{
            pairint pair_w=pair<int,int>(i,g2[i][k]);
			pairint pair_g=pair<int,int>(g2[i][k],w[pair_w]);
			g[i][k]=pair_g;
		}
	}



	int NumOfPairs;
	scanf("%d",&NumOfPairs);
	vector<pairint> Nodes(NumOfPairs);
	for (int i=0;i<=NumOfPairs-1;++i)
	{
		scanf("%d%d",&Nodes[i].first,&Nodes[i].second);
		--Nodes[i].first;--Nodes[i].second;
	}


	dfs(rib.first,0,rib.second);
for (int i=0; i<NumOfPairs; i++) {                                                             
	int a = Nodes[i].first;                                                                      
	int b = Nodes[i].second;                                     
                                                         
	while (depth_bin[a] != depth_bin[b]) {                       
		if (depth_bin[a] > depth_bin[b])                           
			a = parent[a];                                           
		else                                                       
			b = parent[b];                                           
	}                                                            
                                                         
		while (a != b) {                                           
			a = parent[a];                                           
			b = parent[b];                                           
		}                                                          
		int lca = a;                                               
                                                         
		int way_ab = depth[Nodes[i].first] + depth[Nodes[i].second] - 2*depth[lca];           
		printf("%d",way_ab);
		printf("%s","\n");
}

}
