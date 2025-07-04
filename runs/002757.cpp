//============================================================================
// Name        : LCA.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

const unsigned int maxsize = 40000;
vector < vector <pair<unsigned int, unsigned int> > > g(maxsize);
vector <bool> used(maxsize);
unsigned int depth[maxsize], parent[maxsize], depth_bin[maxsize];
unsigned int way = 0, way_bin = 0;

void dfs (unsigned int v, unsigned int lastleng, unsigned int from)
{

	used[v] = true;

	parent[v] = from;
	depth[v] = way;
	depth_bin[v] = way_bin;

	for (size_t i=0; i<g[v].size(); i++){
		unsigned int CurrentNode = g[v][i].first;
		unsigned int CurrentLen = g[v][i].second;
		if (!used[CurrentNode]) {
			way += CurrentLen;
			way_bin++;
			dfs (CurrentNode, CurrentLen, v);
		}
	}
	way_bin--;
	way -= lastleng;
}

int main() {
	unsigned int n,m;
	cin >> n;
	unsigned int s,e,w;
	for (unsigned int i=0;i<n-1;i++)
	{

		cin >> s >> e >> w;
		pair <unsigned int,unsigned int> tmp;
		tmp.first=e;
		tmp.second=w;
		g[s].push_back(tmp);
		tmp.first=s;
		g[e].push_back(tmp);
	}
	cin >> m;
	dfs (1, 0, 0);
	for (unsigned int i=0;i<m;i++)
	{
		unsigned int v1,v2;
		cin >>v1 >>v2;
		unsigned int a,b;
		a=v1;b=v2;

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
		unsigned int lca = a;

		unsigned int way_ab = depth[v1] + depth[v2] - 2*depth[lca];
		cout << way_ab<<endl;

	}
	return 0;
}
