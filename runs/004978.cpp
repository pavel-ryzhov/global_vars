#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <exception>
//#include <cstdlib>

using namespace std;

const int maximum=40000;
int N=0, M=0;

vector<int>	tree, level, height;
map<int, vector<int> > kids;
map<int, vector<int> > dists;

vector<bool> used;

// gets LCA between 2 nodes in the graph, described by 'height', 'order', 'first'
int lca (int a, int b)
{
	int lca;
	int pra_a=a, lev_a = level[a];
	int pra_b=b, lev_b = level[b];
	int lev_aa;
	while (pra_a != pra_b)
	{
		lev_aa = lev_a;
		if(lev_a >= lev_b) 
		{	pra_a = tree[pra_a];
			lev_a--;
		}
		if(lev_b >= lev_aa)
			{	pra_b = tree[pra_b];
				lev_b--;
			}
	}
	lca = pra_b;
	return lca;
}

// gets distance between 2 nodes
int get_distance (int a, int b)
{
	return abs(-2*height[lca(a,b)] + height[a] + height[b]);
}

// sets height for 'nodes'.
vector<int> set_height_tree_level(vector<int> nodes, int lev)
{
	vector<int> new_nodes;
	vector<int> dists_node;
	int len = nodes.size();
	int parent = nodes[0];
	int node;
	for (int i=1; i<len; i++)
	{
		node = nodes[i];
		dists_node = dists[node];
		if(node!=-1)
		{	used[node] = true;
			new_nodes.push_back(node);
			int kids_num = kids[node].size();
			if (kids_num)
			{	for (int j=0; j<kids_num; j++)
				{	int kid = kids[node][j];
					if (!used[kid])
					{	level[kid] = lev+1;
						tree[kid] = node;
						height[kid] = height[node] + dists_node[j];
						new_nodes.push_back(kid);}
					else
					{	if(parent != kid) 
						{	cout << "circle detected!";	
							terminate();}
					}}
			}
			new_nodes.push_back(-1);}
		else
		{	if (i<(len-1)) {parent = nodes[i+1];}
			i++;
		}
	}
	return new_nodes;
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
		kids[p1-1].push_back(p2-1); // each node knows it's kids 
		kids[p2-1].push_back(p1-1); // data is duplicated :(
		dists[p1-1].push_back(d); // each node knows distance to it's kids
		dists[p2-1].push_back(d);
		reread[p1-1][p2-1] = true;
	}
	reread.clear();
	// sets additional arrays, recursive. Turns graph in a tree (0. node - root)
	used.assign(N,false);
	vector<int> nodes;
	tree.assign(N,-1);
	level.assign(N,0);
	height.assign(N,0);
	nodes.push_back(-1);
	nodes.push_back(0);
	int i=0;
	while (nodes.size()!=0)
	{
		nodes = set_height_tree_level(nodes, i);
		i++;
	}
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


