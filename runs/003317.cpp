#include <stdio.h>
#include <vector>
typedef unsigned short int rast;
typedef unsigned int puti;
std::vector < std::vector <std::pair<rast, rast> > > Graf;
std::vector <bool> used_flags;
puti *depth, *parent, * depth_bin;
puti way = 0, way_bin = 0;

void dfs (rast v, rast lastleng, rast from)
{
	used_flags[v] = true;
	parent[v] = from;
	depth[v] = way;
	depth_bin[v] = way_bin;

	for (puti i=0; i<Graf[v].size(); i++)
	{
		int CurrentNode = Graf[v][i].first;
		int CurrentLen = Graf[v][i].second;
		if (!used_flags[CurrentNode]) {
			way += CurrentLen;
			way_bin++;
			dfs (CurrentNode, CurrentLen, v);
		}
	}
	way_bin--;
	way -= lastleng;
}

int main(void)
{
	int i, n, xn, xk, M;
	int beg, en, len; //начало конец и длина ребра

	scanf("%d\n",&n);
	Graf.resize(n);
	used_flags.resize(n);
	used_flags[0]=false;
	depth = new puti[n];//путь от корня до вершины
	depth_bin = new puti[n];//уровень текущей вершины относительно корня
	parent = new puti[n];//вершину, из которой мы пришли (родительскую вершину)
	for(i=1;i<n;i++)
	{	
	    scanf("%d %d %d\n", &beg, &en, &len); 
		beg--; 	en--;
		Graf[beg].push_back(std::make_pair(en, len));
		Graf[en].push_back(std::make_pair(beg,len));
		used_flags[i]=false;
	}
	 //препроцессинг
	if (n>1) dfs(Graf[0][0].first,0,0);
	else {
		printf("%d\n", 0); return 0;
	}
	scanf("%d\n",&M);
	for (rast nz = 0; nz<M; nz++)
	{
		scanf("%d %d\n", &xn, &xk);
		if(xn==xk){
			printf("%d\n", 0);
			continue;
		}
		xk--;	xn--;
		int lca = xn, lcb = xk;
		while (depth_bin[xn] != depth_bin[xk]) 
			if (depth_bin[xn] > depth_bin[xk])
				xn = parent[xn];
			else
				xk = parent[xk];

		while (xn != xk) {
			xn = parent[xn];
			xk = parent[xk];
		}
		
		printf("%d\n", depth[lca] + depth[lcb] - 2*depth[xn]);

	}

	return 0;
}

