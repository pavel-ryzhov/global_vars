#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int maximum=40000;
int N=0, M=0;

map<int, vector<int> > kids;
map<int, vector<int> > dists;

vector<int> order, height, first;
vector<bool> used;

// gets position of minimum value in arr
int minpos(int* arr, int len)
{
	int min = maximum, minpos=-1;
	for(int i=0; i<len; i++)
	{
		if (arr[i]<min) {min=arr[i]; minpos=i;}
	}
	return minpos;
}

// gets LCA between 2 nodes in the graph, described by 'height', 'order', 'first'
int lca (int a, int b)
{
	int left = first[a], right = first[b];
	if (left > right)  swap (left, right);
	int *for_minpos, len=right-left+1;
	for_minpos = new int[len];
	for (int i=0; i<len; i++) for_minpos[i] = height[order[left+i]];
	return order[minpos(for_minpos,len)+left];
}

// gets distance between 2 nodes
int get_distance (int a, int b)
{
	return abs(-2*height[lca(a,b)] + height[a] + height[b]);
}

// sets additional arrays, recursive.
int set_height_order_first(int node)
{
	order.push_back(node);
	first[node] = order.size()-1;
	used[node] = true;
	int kids_num = kids[node].size();
	if (kids_num)
	{
	for (int j=0; j<kids_num; j++)
	{
		int kid = kids[node][j];
		if(!used[kid]) 
		{
			height[kid] = height[node] + dists[node][j];
			if (set_height_order_first(kid)) return 1;
			order.push_back(node);
		}
	}}
	return 0;
}

void map_assign(map<int, vector<int> >& map_, int key, int val)
{
	if (map_[key].size()==0) map_[key].reserve(1);
	map_[key].push_back(val);
}

int get_graph()
{
	cin >> N;
	//if (N<=0) {err = "bad N value"; return 1;}
	
	for (int i=1; i<N; i++)
	{
		int p1, p2, d;
		cin >> p1 >> p2 >> d;
		//if (p1<0 || p2<0 || d<0) {err = "bad value for node or arc"; return 1;};
		map_assign(kids, p1-1, p2-1); // each node knows it's kids 
		map_assign(kids, p2-1, p1-1); // data is duplicated :(
		map_assign(dists, p2-1, d); // each node knows distance to it's kids
		map_assign(dists, p1-1, d);
	}
	order.reserve(N*2);
	height.assign(N,0);
	first.assign(N,-1);
	used.assign(N, false);
	// sets additional arrays, recursive. Turns graph in a tree (0. node - root)
	if (set_height_order_first(0)) return 1; 
	kids.clear();
	dists.clear();
	return 0;
}


int main()
{
	// gets graph, assigns arrays ('height', 'order', 'first')
	//if (get_graph(N)) return 1;
	get_graph();

	cin >> M;
	if (M<0) {{cout << "bad M value"; return 1;}}
	int* answer; //stores answer till output
	answer = new int[M];
	int A=0,B=0;
	for (int i=0; i<M; i++)
	{
		cin >> A >> B;
		if (A<=0 || B <=0){cout<<"bad value A or B"; return 1;}
		answer[i] = get_distance(A-1, B-1);
	}
	for (int i=0; i<M; i++)
	{
		cout << answer[i] << '\n';
	}
	return 0;
}


