#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
//#include <cstdlib>

using namespace std;

const int maximum=40000;
int N=0, M=0;

map<int, vector<int> > kids;
map<int, vector<int> > dists;

vector<int> order, height, first;
vector<bool> used;


// makes test files
//int maketest()
//{
//	fstream out;
//	int N=20, M=10;
//	vector<bool> redo;
//	redo.assign(N,false);
//	out.open("test");
//	out << N << "\n";
//	int i=1;
//	while(i<N)
//	{
//		int node1 = rand() % (N);
//		int node2 = rand() % (N);
//		int dist = rand() % 10;
//		while(redo[node1] && redo[node2])
//		{
//			node1 = rand() % (N);
//			node2 = rand() % (N);
//		}
//		out << node1+1 << " " << node2+1 << " " << dist << std::endl;
//		cout << node1+1 << " " << node2+1 << " " << dist << std::endl;
//		redo[node1] = true;
//		redo[node2] = true;
//		i++;
//	}
//	redo.assign(N,false);
//	out << M << "\n";
//	i=0;
//	while(i<M)
//	{
//		int node1 = rand() % (N);
//		int node2 = rand() % (N);
//		while(redo[node1] && redo[node2])
//		{
//			node1 = rand() % (N);
//			node2 = rand() % (N);
//		}
//		out << node1+1 << " " << node2+1 << std::endl;
//		cout << node1+1 << " " << node2+1 << std::endl;
//		redo[node1] = true;
//		redo[node2] = true;
//		i++;
//	}
//	out.close();
//	return 0;
//}

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
int set_height_order_first(int node, int parent)
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
			if (!used[kid])
			{
				height[kid] = height[node] + dists[node][j];
				if (set_height_order_first(kid, node)) {return 1;}
				order.push_back(node);
			}
			else
			{
				if(parent != kid) {cout << "circle detected!"; return 1;}
			}
		}
	}
	return 0;
}

void map_assign(map<int, vector<int> >& map_, int key, int val)
{
	if (map_[key].size()==0) map_[key].reserve(1);
	map_[key].push_back(val);
}

int get_graph(istream& input)
{
	input >> N;
	vector< vector<bool> > reread;
	vector<bool> reread_line;
	reread_line.assign(N, false);
	reread.assign(N, reread_line);
	reread_line.clear();

	//if (N<=0) {err = "bad N value"; return 1;}
	
	for (int i=1; i<N; i++)
	{
		int p1, p2, d;
		input >> p1 >> p2 >> d;
		//if (p1<0 || p2<0 || d<0) {cout << "bad value for node or arc"; return 1;};
		if (reread[p1-1][p2-1] || reread[p2-1][p1-1])
		{
			cout << "redefinition of an arc detected. Distances are not unambiguous. \nThe graph bids fair being disconnected."; 
			return 1;
		} 
		map_assign(kids, p1-1, p2-1); // each node knows it's kids 
		map_assign(kids, p2-1, p1-1); // data is duplicated :(
		map_assign(dists, p2-1, d); // each node knows distance to it's kids
		map_assign(dists, p1-1, d);
		reread[p1-1][p2-1] = true;
	}
	reread.clear();
	order.reserve(N*2);
	height.assign(N,0);
	first.assign(N,-1);
	used.assign(N, false);
	// sets additional arrays, recursive. Turns graph in a tree (0. node - root)
	if (set_height_order_first(0,-1)) return 1; 
	kids.clear();
	dists.clear();
	return 0;
}


int main(int argc, char* argv[])
{
	//sets, if input is from cin, or file.
	string tmp = "test", tmp2="make";
	std::istream* in = &cin;
	fstream fin;	
	if (argc > 1)
	{
		// sets, if it's test making mode
		//if (string(argv[1]) == tmp2) {maketest(); return 0;}
		tmp = string(argv[1]);
		std::cout << "file reading..." << std::endl;
		fin.open(tmp.c_str());
		in = &fin;
		std::cout << "file reading...OK" << std::endl;
	}
	
	// gets graph, assigns arrays ('height', 'order', 'first')
	if (get_graph(*in)) {return 1;}

	*in >> M;
	if (M<0) {{cout << "bad M value"; return 1;}}
	int* answer; //stores answer till output
	answer = new int[M];
	int A=0,B=0;
	for (int i=0; i<M; i++)
	{
		*in >> A >> B;
		if (A<=0 || B <=0){cout<<"bad value A or B"; return 1;}
		answer[i] = get_distance(A-1, B-1);
	}
	for (int i=0; i<M; i++)
	{
		cout << answer[i] << '\n';
	}
	return 0;
}


