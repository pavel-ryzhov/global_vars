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
	//cout << "enter number of nodes: ";
	cin >> num;
	g.resize(num);
	//считываем из файла данные и заносим в g
	while (count != (num - 1))
	{
		//cout << "\nenter node from: "; 
		cin >> nf;
		//cout << "enter node to: "; 
		cin >> nt;
		//cout << "enter distance: "; 
		cin >> dist;
		g[nf - 1].push_back(make_pair(nt - 1, dist));
		g[nt - 1].push_back(make_pair(nf - 1, dist));
		count++;
		nf = nt = dist = 0;
	}
	//считываем число пар и заносим все пары в nodes[]
	//cout << "enter number of pairs: ";
	cin >> num_of_pairs;
	for (int i = 0; i < num_of_pairs; i++)
	{
		//cout << "\nenter node from: ";
		cin >> nf;
		//cout << "enter node to: ";
		cin >> nt;
		nodes[i] = make_pair(nf - 1, nt - 1);
		nf = nt = 0;
	}
	//cout << "\n++++++++++++++++++++++++++++++++++\n";
	
	
	/*альтернативная инициализация
	g[0].push_back(make_pair(1, 1)); g[0].push_back(make_pair(2, 2)); g[0].push_back(make_pair(3, 3));
	g[1].push_back(make_pair(4, 4)); g[1].push_back(make_pair(5, 5));
	g[2].push_back(make_pair(6, 6));
	g[3].push_back(make_pair(7, 7)); g[3].push_back(make_pair(8, 8));
	g[5].push_back(make_pair(9, 9)); g[5].push_back(make_pair(10, 10));
	g[7].push_back(make_pair(11, 11)); g[7].push_back(make_pair(12, 12));

	int num_of_pairs = 5;
	nodes[0] = make_pair(0, 12);
	nodes[1] = make_pair(1, 3);
	nodes[2] = make_pair(4, 6);
	nodes[3] = make_pair(9, 8);
	nodes[4] = make_pair(8, 11);*/
	
	//инициализируем used
	used.resize(13);
	for (int i =0; i < 13; i++)
	{
		used[i] = false;
	}
	//препроцессинг
	dfs(0, 0, 0);
	//результат работы dfs(0, 0, 0)
	/*for (int i = 0; i < 13; i++)
		{
			cout << "depth_bin[" << i << "] = " << depth_bin[i];//глубина элемента
			cout << ". depth[" << i << "] = " << depth[i];//длина пути от корня дерева
			cout << ". parent[" << i << "] = " << parent[i] << endl;//предок элемента
		}*/
	//вычисление длины пути для всех введенных пар
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
		//cout << "Way from " << lca + 1 << " to " << lcb + 1 << " = " << way_ab << endl;
		cout << way_ab << endl;
	}
	//cin.get();
	//cin.get();
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