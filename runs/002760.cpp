// LCA_Tarjan.cpp : Defines the entry point for the console application.
//

//Bolshakov A.N.

//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

//printf/scanf instead cout/cin - I tested: printf/scanf work faster
//slightly modified Trajan algorithm

#define MAXN  40000  
vector<int> g[MAXN], q[MAXN]; // graph and queries

struct t_res{   // r - result for query (a,b)
	int a,b,r;
};

t_res r[MAXN]; // results for queries
int dsu[MAXN], ancestor[MAXN];
bool u[MAXN];

map<pair<int, int>, int> mp_side,  mp_order; // for sides and order
vector<int> dfs_len; //to save length of path from root
vector<int>  dfs_list, dfs_first; // all steps and pointer to first

int dsu_get (int v) {
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);
}
 
void dsu_unite (int a, int b, int new_ancestor) {
	a = dsu_get (a),  b = dsu_get (b);
	if (rand() & 1)  swap (a, b);
	dsu[a] = b,  ancestor[b] = new_ancestor;
}


inline  int lca(int s){ return ancestor[dsu_get(s)];   } 

void dfs (int v, int l=0) {
	dsu[v] = v,  ancestor[v] = v;
	u[v] = true;

	dfs_list.push_back(v);
	dfs_len.push_back(l);
	for (size_t i=0; i<g[v].size(); ++i)
		if (!u[g[v][i]]) {
			dfs (g[v][i], l + mp_side[pair<int,int>(g[v][i], v)]);
			dsu_unite (v, g[v][i], v);
			
			dfs_list.push_back(v);
			dfs_len.push_back(l);
		}
	for (size_t i=0; i<q[v].size(); ++i)
		if (u[q[v][i]]) {
			t_res res ={v, q[v][i], lca(q[v][i])};
			r[ mp_order[pair<int,int>(v, q[v][i])] ] = res;
		}
}

 
int main() {
	int c,a,b, l; scanf("%d", &c);
	for(int i=0; i<c-1; ++i){
		scanf("%d %d %d", &a,&b,&l); 
		--a; --b;
		pair<int,int> p1(a,b), p2(b,a);
		mp_side[p1] = mp_side[p2] = l;
		
		g[a].push_back(b);
		g[b].push_back(a);
	}

	scanf("%d", &c);
	map<pair<int,int>, int>::iterator m_it;
	memset((void *)r, 0, sizeof(t_res)*MAXN);
	for (int i=0;i<c; ++i)
	{
		scanf("%d %d", &a, &b);
		--a; --b;
		q[a].push_back(b);
		q[b].push_back(a);

		
		pair<int,int> p1(a,b), p2(b,a);
		if(mp_order.find(p1) != mp_order.end() ){
			r[i].r = -1, r[i].a = mp_order[p1];
		}else mp_order[p1] = mp_order[p2] = i;
	
	}
	dfs (0);

	int m = (int) dfs_list.size();
	dfs_first.assign (MAXN, -1);
	for (int i = 0; i < m; ++i)
	{
		int v = dfs_list[i];
		if (dfs_first[v] == -1)
			dfs_first[v] = i;
	}

	for(int i=0; i<c; ++i){ //print results
		if(r[i].r == -1) r[i] = r[r[i].a];
		printf("%d\n", abs(dfs_len[dfs_first[r[i].a]] - dfs_len[dfs_first[r[i].r]]) + 
										   abs(dfs_len[dfs_first[r[i].b]] - dfs_len[dfs_first[r[i].r]]));
	}
	return 0;
}