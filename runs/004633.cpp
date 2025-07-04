#include <iostream>
#include <vector>
#include <list>
using namespace std;

vector <vector <int> > graph;
vector <int> depth;
int N;

vector <vector <int> > up; 	// Массив 1го, 2го, 4го,... предков для каждой вершины
int l; 						// log(N)

vector <bool> used;
vector <int> time_in, time_out; // Время входа и выхода из вершины
int timer;

struct edge 
{
	int parent;
	int child;
	int length;
};

// Обходит дерево в глубину
void dfs(int v, int p = 0) 
{
	used[v] = true;
	time_in[v] = timer++;
	
	up[v][0] = p;
	for (int i = 1; i <= l; i++)
		up[v][i] = up[up[v][i-1]][i-1];
	
	for (int i = 0; i < graph[v].size(); i++) 
	{
		if (!used[graph[v][i]])
			dfs(graph[v][i], v);
	}
	time_out[v] = timer++;
}

// Возвращает true если v1 является предком v2
bool upper(int v1, int v2)
{
	return time_in[v1] <= time_in[v2] && time_out[v1] >= time_out[v2];
}

// Находит наименьшего общего предка методом двоичного подъема
int lca(int v1, int v2) 
{
	if (upper(v1, v2)) return v1;
	if (upper(v2, v1)) return v2;
	for (int i = l; i >= 0; i--)
		if (!upper(up[v1][i], v2))
			v1 = up[v1][i];
	return up[v1][0];
}

int find_shortest_path(int v1, int v2)
{
	return depth[v1]+depth[v2]-2*depth[lca(v1, v2)];
}

int main()
{
	cin >> N;
	graph.resize(N);
	depth.resize(N);
	used.resize(N);
	time_in.resize(N);
	time_out.resize(N);
	up.resize(N);
	
	l = 1;
	while ((1<<l) <= N) l++;
	for (int i = 0; i < N; i++) 
		up[i].resize(l+1);
	
	vector<int> added;
	added.resize(N);
	list<edge> unknown;
	
	int temp;
	edge e;
	int parent, child, length;	
	if (N > 1)
	{
		cin >> parent >> child >> length;
		added[parent-1] = 1;
		added[child-1] = 1;
		graph[parent-1].push_back(child-1);
		depth[parent-1] = 0;
		depth[child-1] = depth[parent-1]+length;
	}
	for (int i = 0; i < N-2; i++)
	{
		cin >> parent >> child >> length;
		if (added[child-1] == 1)
		{
			temp = parent;
			parent = child;
			child = temp;
		}
		else if (added[parent-1] == 0)
		{
			e.parent = parent-1;
			e.child = child-1;
			e.length = length;
			unknown.push_back(e);
			continue;
		}		
		added[child-1] = 1;
		graph[parent-1].push_back(child-1);
		depth[child-1] = depth[parent-1]+length;
	}
	while (unknown.size())
	{
		for (list<edge>::iterator it = unknown.begin(); it != unknown.end(); ++it)
		{
			if (added[it->child] == 1)
			{
				temp = it->parent;
				it->parent = it->child;
				it->child = temp;
			}
			else if (added[it->parent] == 0)
				continue;
			added[it->child] = 1;
			graph[it->parent].push_back(it->child);
			depth[it->child] = depth[it->parent]+it->length;
			it = unknown.erase(it);
			--it;
		}
	}
	dfs(0);
	
	int k;
	cin >> k;
	int v1, v2;
	while (k--)
	{
		cin >> v1 >> v2;
		cout << find_shortest_path(v1-1, v2-1) << endl;
	}
}