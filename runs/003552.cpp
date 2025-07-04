#include <iostream>
#include <vector>
#include <algorithm> //sort
#include <map>

typedef struct _Edge {
	unsigned int parent, child, length;
} Edge;

typedef struct _Node {
	unsigned int parent, depth, distance;
} Node;

typedef std::vector< Node > TreeContainer;
typedef std::pair< unsigned int, unsigned int > Link;
typedef std::multimap< const unsigned int, Link > EdgesContainer;

class TreeD {
public:
	TreeD();
	TreeD(EdgesContainer* tree_edges);
	unsigned int Distance(unsigned int a, unsigned int b);
	void BuildTree(EdgesContainer* tree_edges);
private:
	void DFS(EdgesContainer* tree_edges, unsigned int node, unsigned int parent, unsigned int dist, unsigned int depth);
	TreeContainer tree_nodes;
};

typedef struct _Request {
	unsigned int a,b;
} Request;


// Fills the tree nodes while doing DFS. Can start with any node, depth > 0.
void TreeD::DFS(EdgesContainer* tree_edges, unsigned int node, unsigned int parent, unsigned int dist, unsigned int depth) {
	tree_nodes[node].parent = parent;
	tree_nodes[node].distance = dist;
	tree_nodes[node].depth = depth;
	
	++depth;
	
	std::pair<EdgesContainer::iterator, EdgesContainer::iterator> range;
	EdgesContainer::iterator it;
	range = tree_edges->equal_range(node);
	for (it = range.first; it != range.second; ++it) {
		if (tree_nodes[it->second.first].depth==0)
			DFS(tree_edges, it->second.first, node, it->second.second, depth);
	}
}

// Expects clear edges, doesn't check for ambiguous edges.
void TreeD::BuildTree(EdgesContainer* tree_edges) {
	Node current_node;
	
	tree_nodes.clear();
	tree_nodes.reserve(tree_edges->size()+2);	
	
	current_node.parent = 0;
	current_node.depth = 0;
	current_node.distance = 0;
	
	tree_nodes.insert(tree_nodes.begin(), tree_edges->size()+2, current_node);
	
	DFS(tree_edges, 1, 0, 0, 1);
}

// If one of the node's parent is the node itself, there's gonna be trouble. Should be ok, if the edges were ok.
unsigned int TreeD::Distance(unsigned int a, unsigned int b) {
	unsigned int height1, height2;
	unsigned int ancestor1, ancestor2;
	long int length = 0;
	height1 = tree_nodes.at(a).depth;
	height2 = tree_nodes.at(b).depth;
	ancestor1 = a;
	ancestor2 = b;
	
	// simple LCA without optimizations
	while (height1 != height2)
		if (height1 > height2) {
			length += tree_nodes.at(ancestor1).distance;
			ancestor1 = tree_nodes.at(ancestor1).parent; // potential inf loop
			height1 = tree_nodes.at(ancestor1).depth;
		}
		else {
			length += tree_nodes.at(ancestor2).distance;
			ancestor2 = tree_nodes.at(ancestor2).parent; // and here
			height2 = tree_nodes.at(ancestor2).depth;
		}
	
	while (ancestor1 != ancestor2) {
		length += tree_nodes.at(ancestor1).distance + tree_nodes.at(ancestor2).distance;
		ancestor1 = tree_nodes.at(ancestor1).parent; // and here
		ancestor2 = tree_nodes.at(ancestor2).parent; // and here
	}
	return length;
}

TreeD::TreeD() {
}

TreeD::TreeD(EdgesContainer* tree_edges) {
	BuildTree(tree_edges);
}

int main (int argc, char * const argv[]) {
	unsigned int tree_size = 0;
	unsigned int number_of_requests = 0;
	unsigned int i = 0;
	Request current_request;
	Edge current_edge;
	TreeD tree;
	EdgesContainer *tree_edges = new EdgesContainer;
	std::vector< Request > requests;
	
	std::cin >> tree_size;
	if (tree_size == 0) {
		return 0;
	}
	//tree_edges.reserve(tree_size-1);	
	std::pair< const unsigned int, std::pair< unsigned int, unsigned int > > *p;
	p = tree_edges->get_allocator().allocate((tree_size - 1) * 2);
	
	for (i = 0; i<tree_size-1; ++i) {
		std::cin >> current_edge.parent >> current_edge.child >> current_edge.length;
		tree_edges->insert(tree_edges->end(), std::pair< const unsigned int, Link >(current_edge.parent, Link(current_edge.child,
																											  current_edge.length)));
		std::swap(current_edge.child, current_edge.parent);
		tree_edges->insert(tree_edges->end(), std::pair< const unsigned int, Link >(current_edge.parent, Link(current_edge.child,
																											  current_edge.length)));
	}
	
	tree.BuildTree(tree_edges);
	tree_edges->get_allocator().deallocate(p, (tree_size - 1) * 2);
	delete tree_edges;
	
	std::cin >> number_of_requests;
	for (i = 0; i < number_of_requests; ++i) {
		std::cin >> current_request.a >> current_request.b;
		requests.push_back(current_request);
	}
	for (i = 0; i < number_of_requests; ++i) {
		std::cout << tree.Distance(requests.at(i).a, requests.at(i).b) << "\n";
	}
	return 0;
}