#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Tree {
	struct Node {
		Node(int i, int d): id(i), dist(d) {}
		int id;
		int dist; // distance to the parent node
		list<Node*> children;
	};

	class FindNode {
		static Node* match;
		int id;
	public:
		FindNode(int i): id(i) {}
		Node* get_match()
		{
			return match;
		}

		bool operator()(Node* node)
		{
			if (node->id == id) {
				match = node;
				return true;
			}
			if (find_if(node->children.begin(), node->children.end(), FindNode(id)) != node->children.end()) {
				return true;
			}
			return false;
		}
	};

	Node* root;

	void rebuild_hash();
	void build_hash(Node* node, Node* parent = 0);

	vector<int> plain;
	vector<int> plain_pos;
	vector<int> root_dist;
	bool hash_valid; // indicates that three vectors above are valid

	int ncount;
public:
	Tree(): root(0), ncount(1) {}
	void add(int from, int to, int d);
	int get_dist(int n1, int n2);

};

Tree::Node* Tree::FindNode::match = 0;

void Tree::build_hash(Node* node, Node* parent)
{
	plain.push_back(node->id);
	plain_pos[node->id] = plain.size()-1;
	if (parent)
		root_dist[node->id] = root_dist[parent->id] + node->dist;
	
	list<Node*>::const_iterator i;
	for (i = node->children.begin(); i != node->children.end(); ++i)
		build_hash(*i, node);

	if (parent)
		plain.push_back(parent->id);
}

void Tree::rebuild_hash()
{
	plain.clear();
	plain_pos.clear();
	root_dist.clear();

	plain_pos.resize(ncount+1); // indexing from 1
	root_dist.resize(ncount+1); // indexing from 1
	build_hash(root);
}

void Tree::add(int from, int to, int d)
{
	if (root == 0) {
		root = new Node(from, 0);
	}

	Node* node_start = 0;
	if (root->id == from) {
		node_start = root;
	} else {
		FindNode fn(from);
		if (find_if(root->children.begin(), root->children.end(), fn) != root->children.end()) {
			node_start = fn.get_match();
		}
	}

	if (node_start) {
		node_start->children.push_back(new Node(to, d));
		++ncount;
		hash_valid = false;
	}
}


int Tree::get_dist(int n1, int n2)
{
	if (!hash_valid) {
		rebuild_hash();
		hash_valid = true;
	}
	
	if (plain_pos[n2] < plain_pos[n1])
		swap(n1, n2);

	int min, pos;
	for (pos = plain_pos[n1], min = root_dist[plain[pos]]; pos <= plain_pos[n2]; ++pos) {
		if (min > root_dist[plain[pos]])
			min = root_dist[plain[pos]];
	}
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