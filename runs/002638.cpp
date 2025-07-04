// tree.cpp: определяет точку входа для консольного приложения.
//
//#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

const int maxsize = 40000;
vector < vector< pair< int, int > > > g;
vector < bool > used;
pair< int, int > nodes[maxsize];
int depth[maxsize]; 
int parent[maxsize];
int depth_bin[maxsize];
int way = 0, way_bin = 0;
int num, num_of_pairs;
int count = 0;
int nf, nt, dist;
bool run = true;

void dfs (int v, int lastleng, int from);

int main()
{
	cin >> num;
	g.resize(num);
	while (count != (num - 1))
	{
		cin >> nf;
		cin >> nt;
		cin >> dist;
		g[nf - 1].push_back(make_pair(nt - 1, dist));
		g[nt - 1].push_back(make_pair(nf - 1, dist));
		count++;
		nf = nt = dist = 0;
	}
	cin >> num_of_pairs;
	for (int i = 0; i < num_of_pairs; i++)
	{
		cin >> nf;
		cin >> nt;
		nodes[i] = make_pair(nf - 1, nt - 1);
		nf = nt = 0;
	}

	used.resize(num);
	for (int i =0; i < num; i++)
	{
		used[i] = false;
	}
	
	dfs(0, 0, 0);
	
	for (int i = 0; i < num_of_pairs; i++) 
	{
		int a = nodes[i].first;
		int b = nodes[i].second;
		int lca = a;
		int lcb = b;
		while (depth_bin[a] != depth_bin[b]) 
		{
			if (depth_bin[a] > depth_bin[b])
				a = parent[a];
			else
				b = parent[b];
		}

		while (a != b) 
		{
			a = parent[a];
			b = parent[b];
		}
		int way_ab = depth[lca] + depth[lcb] - 2 * depth[a];
		cout << way_ab << endl;
	}
	return 0;
}

void dfs (int v, int lastleng, int from)
{
	used[v] = true;
	parent[v] = from;
	depth[v] = way;
	depth_bin[v] = way_bin;

	for (size_t i = 0; i < g[v].size(); i++)
	{
		int CurrentNode = g[v][i].first;
		int CurrentLen = g[v][i].second;
		if (!used[CurrentNode]) 
		{
			way += CurrentLen;
			way_bin++;
			dfs (CurrentNode, CurrentLen, v);
		}
	}
	way_bin--;
	way -= lastleng;
}