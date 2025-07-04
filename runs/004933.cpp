#include <stdio.h>
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

int minpos(int* arr, int len)
{
	int min = maximum, minpos=-1;
	for(int i=0; i<len; i++)
	{
		if (arr[i]<min) {min=arr[i]; minpos=i;}
	}
	return minpos;
}

int lca (int a, int b)
{
	int left = first[a], right = first[b];
	if (left > right)  swap (left, right);
	int *for_minpos, len=right-left+1;
	for_minpos = new int[len];
	for (int i=0; i<len; i++) for_minpos[i] = height[order[left+i]];
	return order[minpos(for_minpos,len)+left];
}

int get_distance (int a, int b)
{
	return -2*height[lca(a,b)] + height[a] + height[b];
}

int go_over(int& node_num, map<int, vector<int> >& overs, map<int, vector<int> >& o_dists, int dec)
{
	
	return 0;
}

int set_height_order_first(int node_num)
{
	order.push_back(node_num);
	first[node_num] = order.size()-1;
	used[node_num] = true;
	for (unsigned int j=0; j<kids[node_num].size(); j++)
	{
		int kid = kids[node_num][j];
		if(!used[kid]) 
		{
			height[kid] = height[node_num] + dists[node_num][j];
			if (set_height_order_first(kid)) return 1;
			order.push_back(node_num);
		}
	}
	return 0;
}

void map_assign(map<int, vector<int> >& map_, int key, int val)
{
	if (map_[key].size()==0) map_[key].reserve(1);
	map_[key].push_back(val);
}

int get_graph(int n)
{
	for (int i=1; i<n; i++)
	{
		int p1, p2, d;
		cin >> p1 >> p2 >> d;
		if (p1<0 || p2<0 || d<0) {printf("bad value for node or arc"); return 1;};
		map_assign(kids, p1-1, p2-1);
		map_assign(kids, p2-1, p1-1);
		map_assign(dists, p2-1, d);
		map_assign(dists, p1-1, d);
	}
	order.reserve(N*2);
	height.assign(N,0);
	first.assign(N,-1);
	used.assign(N, false);
	if (set_height_order_first(0)) return 1;
	return 0;
}


int main()
{
	cin >> N;
	if (N<=0) {cout << "bad N value"; return 1;}
	if (get_graph(N)) return 1;

	cin >> M;
	if (M<0) {{cout << "bad M value"; return 1;}}
	int* answer;
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


