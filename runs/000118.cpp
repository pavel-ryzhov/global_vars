#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

class Segment_tree {
	int n;
	vector<int> tree;

	void build_tree(const vector<int>& v, int i, int l, int r);
	int _get(int i, int l, int r, int b1, int b2);

public:
	Segment_tree(): n(0) {}
	Segment_tree(vector<int>& v){
		build(v);
	}

	int get(int n1, int n2) {
		if (n > 0 && n1 >= 0 && n2 < n)
			return _get(1, 0, n-1, n1, n2);
		return 0;
	};

	void build(const vector<int>& v) {
		n = v.size();
		tree.resize(n*4+1);
		build_tree(v, 1, 0, n-1);
	}
};

int Segment_tree::_get(int i, int l, int r, int b1, int b2)
{
	if (l == b1 && r == b2) {
		return tree[i];
	}
	
	int m = (l + r)/2;
	
	if (l <= b1 && b2 <= m)
		return _get(i*2, l, m, b1, b2);
	
	if (m+1 <= b1 && b2 <= r)
		return _get(i*2+1, m+1, r, b1, b2);
	
	return min(_get(i*2, l, m, b1, m), _get(i*2+1, m+1, r, m+1, b2));
}

void Segment_tree::build_tree(const vector<int>& v, int i, int l, int r)
{
	if (l == r) {
		tree[i] = v[l];
	} else {
		int m = (l+r)/2;
		build_tree(v, i*2, l, m);
		build_tree(v, i*2+1, m+1, r);
		tree[i] = min(tree[i*2], tree[i*2+1]);
	}
}

class Tree {
	struct Link {
		Link(int i, int d): id(i), dist(d) {}
		int id;
		int dist;
	};

	Segment_tree seg_tree;
	vector<int> plain;
	map<int, int> plain_pos;
	map<int, int> root_dist;
	bool hash_valid; // indicates that the above arrays are valid

	map<int, list<Link> > nodes;
	int root;

	void build_hash(int node, int exclude = -1);
public:
	Tree(): hash_valid(false) {}
	void add(int from, int to, int d);
	int get_dist(int n1, int n2);
};

void Tree::add(int from, int to, int d)
{
	if (nodes.size() == 0) {
		root = from;
	}

	nodes[from].push_back(Link(to, d));
	nodes[to].push_back(Link(from, d));
	hash_valid = false;
}

void Tree::build_hash(int node, int exclude)
{
	plain.push_back(root_dist[node]);
	plain_pos[node] = plain.size()-1;

	list<Link>& children = nodes[node];
	for (list<Link>::iterator i = children.begin(); i != children.end(); ++i) {
		if (i->id == exclude)
			continue;

		root_dist[i->id] = root_dist[node] + i->dist;
		build_hash(i->id, node);
		plain.push_back(root_dist[node]);
	}
}

int Tree::get_dist(int n1, int n2)
{
	if (nodes.size() < 2)
		return 0;

	if (!hash_valid) {
		build_hash(root);
		seg_tree.build(plain);
		hash_valid = true;
	}
	
	if (plain_pos[n2] < plain_pos[n1])
		swap(n1, n2);

	int min = seg_tree.get(plain_pos[n1], plain_pos[n2]);
	return (root_dist[n1] - min) + (root_dist[n2] - min);
}

int main()
{
	Tree tree;

	int no_nodes;
	cin >> no_nodes;

	for (int i = 0; i < no_nodes-1; ++i) {
		int from, to, dist;
		cin >> from >> to >> dist;
		tree.add(from, to, dist);
	}
	
	int no_paths;
	cin >> no_paths;
	
	for (int i = 0; i < no_paths; ++i) {
		int from, to;
		cin >> from >> to;
		cout << tree.get_dist(from, to) << '\n';
	}

	return 0;
}