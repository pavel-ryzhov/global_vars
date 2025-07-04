#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
	int name;
	int parent_pos;
	int length;
	int depth;
};

int build_tree(map<int,vector<pair<int,int> >*>& arcs, vector<Node>& tree,
			   int cur_vertex, int prev_vertex, int pos, int ppos, int dst);

int main () {
	string s;
	int N;
	int M;
	cin >> s;
	N = atoi(s.c_str());
	int v1, v2, len;
	int count = 0;
	int root = -1;
	map<int,vector<pair<int,int> >*>arcs;
	while (count < (N-1)) {
		cin >> s;
		v1 = atoi(s.c_str());
		cin >> s;
		v2 = atoi(s.c_str());
		cin >> s;
		len = atoi(s.c_str());
		if (count == 0)
			root = v1;
		count++;
		if (arcs[v1]==NULL)
			arcs[v1] = new vector<pair<int,int> >;
		arcs[v1][0].push_back(make_pair(v2,len));
		if (arcs[v2]==NULL)
			arcs[v2] = new vector<pair<int,int> >;
		arcs[v2][0].push_back(make_pair(v1,len));
	}
	cin >> s;
	M = atoi(s.c_str());
	vector<pair<int,int> >pairs(M);
	count = 0;
	while (count < M) {
		cin >> s;
		pairs[count].first = atoi(s.c_str());
		cin >> s;
		pairs[count].second = atoi(s.c_str());
		count++;
	}
	// create tree
	vector<Node>tree(N);
	// recursive tree build
	int pos = 0;
	build_tree(arcs,tree,root,-1,pos,-1,0);
	map<int,int>v;
	for(int i = 0; i<int(tree.size());i++)
		v[tree[i].name]=i;
	// calc distance
	int dep1, dep2;
	int tmp_pos1, tmp_pos2;
	int pos1, pos2;
	for(int i = 0; i<int(pairs.size());i++) {
		v1 = pairs[i].first;
		v2 = pairs[i].second;
		if (v1 == v2)
			cout << 0 << endl;
		else if (v1 == root)
			cout << tree[v[v2]].length << endl;
		else if (v2 == root)
			cout << tree[v[v1]].length << endl;
		else {
			pos1 = v[v1];
			pos2 = v[v2];
			dep1 = tree[pos1].depth;
			dep2 = tree[pos2].depth;
			tmp_pos1 = pos1;
			tmp_pos2 = pos2;
			while (dep1 > dep2) {
				tmp_pos1 = tree[tmp_pos1].parent_pos;
				dep1--;
			}
			while (dep1 < dep2) {
				tmp_pos2 = tree[tmp_pos2].parent_pos;
				dep2--;
			}
			while (1) {
				if (tree[tmp_pos1].name == tree[tmp_pos2].name) {
					cout << (tree[pos1].length+tree[pos2].length - 
							2*tree[tmp_pos1].length) << endl;
					break;
				}
				tmp_pos1 = tree[tmp_pos1].parent_pos;
				tmp_pos2 = tree[tmp_pos2].parent_pos;
			}
		}
	}
	return 0;
}

int build_tree(map<int,vector<pair<int,int> >*>& arcs, vector<Node>& tree,
			   int cur_vertex, int prev_vertex, int pos, int ppos, int dst) {
	vector<pair<int,int> >* vp;
	int len;
	vp = arcs[cur_vertex];
	len = int(vp->size());
	// add vertex;
	if (ppos == -1) {
		tree[pos].length = 0;
		tree[pos].depth = 0;
	}
	else {
		tree[pos].length = tree[ppos].length + dst;
		tree[pos].depth = tree[ppos].depth + 1;
	}
	tree[pos].name = cur_vertex;
	tree[pos].parent_pos = ppos;
	ppos = pos;
	pos++;
	for (int i=0; i<len; i++) {
		if (vp[0][i].first == prev_vertex)
			continue;
		pos = build_tree(arcs,tree,vp[0][i].first,cur_vertex, pos, ppos, vp[0][i].second);
	}
	return pos;
}
