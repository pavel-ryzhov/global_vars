#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

class Tree {
	struct Node {
		Node(int i, int d): id(i), dist(d) {}
		int id;
		int dist; // distance to the parent node
		list<Node*> children;
	};

	struct Link {
		int from;
		int to;
		int dist;
		Link(int f, int t, int d): from(f), to(t), dist(d) {}
	};

	void release_node(Node* node);
	Node* find_node(int id, Node* node);
	void rebuild_hash();
	void build_hash(Node* node, Node* parent = 0);

	vector<int> plain;
	map<int, int> plain_pos;
	map<int, int> root_dist;
	bool hash_valid; // indicates that three vectors above are valid
	
	Node* root;
	int ncount;

	list<Link> awaiting;
public:
	Tree(): root(0), ncount(1) {}
	~Tree()
	{ 
		if (root)
			release_node(root);
	}

	void add(int from, int to, int d);
	int get_dist(int n1, int n2);
};

Tree::Node* Tree::find_node(int id, Node* node)
{
	if (node->id == id) {
		return node;
	}
	
	list<Node*>::const_iterator i;
	
	for (i = node->children.begin(); i != node->children.end(); ++i) {
		if (Node* n = find_node(id, *i))
			return n;
	}
	return 0;
}

void Tree::release_node(Node* node)
{
	list<Node*>::iterator i;
	for (i = node->children.begin(); i != node->children.end(); ++i) {
		release_node(*i);
	}

	delete node;
}

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

	build_hash(root);
}

void Tree::add(int from, int to, int d)
{
	if (root == 0) {
		root = new Node(from, 0);
	}
	
	Node* node_start = 0;
	int new_node_id = to;
	if ((node_start = find_node(from, root)) == 0) {
		node_start = find_node(to, root);
		new_node_id = from;
	}

	if (node_start) {
		node_start->children.push_back(new Node(new_node_id, d));
		++ncount;
		hash_valid = false;

		// Can we insert any awaiting link?
		list<Link> can_be_added;
		list<Link>::iterator i = awaiting.begin();
		while(i != awaiting.end()) {
			if (i->from == from || i->from == to
				|| i->to == from || i->to == to) {
				can_be_added.push_back(*i);
				i = awaiting.erase(i);
			} else {
				++i;
			}
		}

		for (i = can_be_added.begin(); i != can_be_added.end(); ++i)
			add(i->from, i->to, i->dist);
	} else {
		awaiting.push_back(Link(from, to, d));
	}
}


int Tree::get_dist(int n1, int n2)
{
	if (ncount < 2)
		return 0;

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