#include <iostream>
#include <vector>
#include <stdlib.h>
///#include <fstream>
using namespace std;

int root(1), res(0);
vector < bool > used;
vector < int > dsu, ancestor, result, dist;
vector < vector < pair < int, int > > > tree, qq; 


int dsu_get (int v) {
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);
}

void dsu_unite (int a, int b, int new_ancestor) {
	a = dsu_get(a),  b = dsu_get(b);
	if (rand() & 1)  
		swap (a, b);
	dsu[a] = b,  ancestor[b] = new_ancestor;
}

void dfs (int v) {
	dsu[v] = v,  ancestor[v] = v;
	used[v] = true;
	for (size_t i = 0; i < tree[v].size(); ++i)
		if (!used[tree[v][i].first]) {
			dfs (tree[v][i].first);
			dsu_unite (v, tree[v][i].first, v);
		}
		for (size_t i = 0; i < qq[v].size(); ++i)
			result[qq[v][i].second] = dist[v] + dist[qq[v][i].first] - 2 * dist[ancestor[dsu_get(qq[v][i].first)]];					
}

void dfs_cost (int v) 
{
	used[v] = true;
	for (vector < pair < int, int > >::iterator iter = tree[v].begin(); iter != tree[v].end(); ++iter)
		if (!used[iter->first]) {
			res += iter->second;
			dist[iter->first] = res;
			dfs_cost (iter->first);
			res -= iter->second;				
		}
	used[v] = false;
}	

int main() 
{
	///ifstream cin("test.txt", ios::in | ios::app);
	int N, M, vertex_1, vertex_2, cost;
	cin >> N;
	unsigned int size = N + 1;
	dsu.resize(size);
	tree.resize(size);
	dist.resize(size);
	used.resize(size, false);
	ancestor.resize(size);

	for(int i = 1; i < N; ++i)
	{
		cin >> vertex_1 >> vertex_2 >> cost;
		tree[vertex_1].push_back(make_pair(vertex_2, cost));
		tree[vertex_2].push_back(make_pair(vertex_1, cost));
	}	
	
	cin >> M;
	qq.resize(size);
	result.resize(M);
	for(int i = 0; i < M; i++)
	{
		cin >> vertex_1 >> vertex_2;
		qq[vertex_1].push_back(make_pair(vertex_2, i));
		qq[vertex_2].push_back(make_pair(vertex_1, i));
	}
	
	///cin.close();	
	dfs_cost(root);
	//used.assign(size, false);
	dfs (root);

	for(int i = 0; i < M; i++)
		cout << result[i] << endl;
	return 0;
}

