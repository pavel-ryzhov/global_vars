#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::min;
using std::max;

struct edge {
	int end_node;
	int weight;

	edge()
		: end_node(0),
		weight(0) {}

	edge(int _end_node, int _weight)
		: end_node(_end_node),
		weight(_weight) {}
};

struct segment {
	int begin;
	int end;

	segment()
		: begin(0),
		end(0) {}

	segment(int _begin, int _end)
		: begin(_begin),
		end(_end) {}
};

class segment_tree {
	public:
		static const int ROOT_INDEX;
		static const int HAS_NO_CHILD;
		struct segment_tree_node;
	
	private:
		vector<segment_tree_node> nodes;
		vector<int> first_occurrence;

	private:
		void decompose(const segment& parent_segment, 
					   segment* left_child_segment,
					   segment* right_child_segment) const;
		int init_node(const std::vector<int>& eulerian_traversal, int parent);
		int get_distance_from_root_to_ancestor(const segment& request_segment, int node_index) const;

	public:
		void init_segment_tree(const vector<int>& eulerian_traversal, 
							   const vector<int>& _first_occurrence);
		int get_distance_between_nodes(const segment& request) const;
};

const int segment_tree::HAS_NO_CHILD = -1;
const int segment_tree::ROOT_INDEX = 0;

struct segment_tree::segment_tree_node {
	segment current_segment;
	int distance_from_ancestor_to_root;

	int left_child;
	int right_child;

	segment_tree_node()
		: current_segment(0, 0),
		distance_from_ancestor_to_root(0),
		left_child(HAS_NO_CHILD),
		right_child(HAS_NO_CHILD) {}

	segment_tree_node(const segment& _current_segment)
		: current_segment(_current_segment),
		distance_from_ancestor_to_root(0),
		left_child(HAS_NO_CHILD),
		right_child(HAS_NO_CHILD) {}
};

void segment_tree::decompose(const segment& parent_segment,
							 segment* left_child_segment,
							 segment* right_child_segment) const {
	int parent_segment_middle = (parent_segment.end + parent_segment.begin) / 2;
	*left_child_segment = segment(parent_segment.begin, parent_segment_middle);
	*right_child_segment = segment(parent_segment_middle, parent_segment.end);
}

int segment_tree::init_node(const std::vector<int>& eulerian_traversal, int parent) {
	if (nodes[parent].current_segment.end - nodes[parent].current_segment.begin == 1) {
		nodes[parent].left_child = HAS_NO_CHILD;
		nodes[parent].right_child = HAS_NO_CHILD;
	
		int simple_segment_index = nodes[parent].current_segment.begin;
		nodes[parent].distance_from_ancestor_to_root = eulerian_traversal[simple_segment_index];
		return nodes[parent].distance_from_ancestor_to_root;
	}

	segment left_child_segment, right_child_segment;
	decompose(nodes[parent].current_segment, &left_child_segment, &right_child_segment);

	nodes.push_back(segment_tree_node(left_child_segment));
	int left_child = nodes.size() - 1;
	nodes[parent].left_child = left_child;
	nodes[left_child].distance_from_ancestor_to_root = 
		init_node(eulerian_traversal, nodes[parent].left_child); 

	nodes.push_back(segment_tree_node(right_child_segment));
	int right_child = nodes.size() - 1;
	nodes[parent].right_child = right_child;
	nodes[right_child].distance_from_ancestor_to_root = 
		init_node(eulerian_traversal, nodes[parent].right_child);

	nodes[parent].distance_from_ancestor_to_root = 
		min(nodes[left_child].distance_from_ancestor_to_root, 
			nodes[right_child].distance_from_ancestor_to_root);

	return nodes[parent].distance_from_ancestor_to_root;
}

void segment_tree::init_segment_tree(const std::vector<int>& eulerian_traversal, 
									 const std::vector<int>& _first_occurrence) {
	first_occurrence = _first_occurrence;
	nodes.reserve(2 * eulerian_traversal.size());

	segment root_segment(0, eulerian_traversal.size());
	nodes.push_back(segment_tree_node(root_segment));
	init_node(eulerian_traversal, ROOT_INDEX);
}

int segment_tree::get_distance_from_root_to_ancestor(const segment& request_segment, 
													 int node_index) const {
	
	if (request_segment.end == nodes[node_index].current_segment.end &&
		request_segment.begin == nodes[node_index].current_segment.begin) {
		return nodes[node_index].distance_from_ancestor_to_root;
	}

	int left_child = nodes[node_index].left_child;
	int right_child = nodes[node_index].right_child;

	if (request_segment.end <= nodes[left_child].current_segment.end) {
		return get_distance_from_root_to_ancestor(request_segment, left_child);
	}

	if (request_segment.begin >= nodes[left_child].current_segment.end) {
		return get_distance_from_root_to_ancestor(request_segment, right_child);
	}
	
	segment left_part(request_segment.begin, nodes[left_child].current_segment.end);
	segment right_part(nodes[left_child].current_segment.end, request_segment.end);

	return min(get_distance_from_root_to_ancestor(left_part, left_child),
			   get_distance_from_root_to_ancestor(right_part, right_child));
}

int segment_tree::get_distance_between_nodes(const segment& request) const {

	int begin = min(first_occurrence[request.begin], first_occurrence[request.end]);
	int end = max(first_occurrence[request.begin], first_occurrence[request.end]);

	int distance_from_root_to_left_node =
		get_distance_from_root_to_ancestor(segment(begin, begin + 1), ROOT_INDEX);

	int distance_from_root_to_right_node =
		get_distance_from_root_to_ancestor(segment(end, end + 1), ROOT_INDEX);

	int distance_from_root_to_ancestor_node =
		get_distance_from_root_to_ancestor(segment(begin,end + 1), ROOT_INDEX);
	
	return distance_from_root_to_left_node + distance_from_root_to_right_node -
		2 * distance_from_root_to_ancestor_node;
}

void get_tree_edges(vector<vector<edge> >* tree_edges) {
	int number_of_nodes;
	cin >> number_of_nodes;
	(*tree_edges).resize(number_of_nodes);

	for (int edge_index = 0; edge_index < number_of_nodes - 1; ++edge_index) {
		int start_node, end_node, weight;
		cin >> start_node >> end_node >> weight;
		(*tree_edges)[start_node - 1].push_back(edge(end_node - 1, weight));
		(*tree_edges)[end_node - 1].push_back(edge(start_node - 1, weight));
	}
}

void get_requests(vector<segment>* requests) {
	int number_of_requests;
	cin >> number_of_requests;
	(*requests).resize(number_of_requests);

	for (int request_index = 0; request_index < number_of_requests; ++request_index) {
		int begin, end;
		cin >> begin >> end;
		(*requests)[request_index] = segment(begin - 1, end - 1);
	}
}

void compute_eulerian_traversal(const vector<vector<edge> >& tree_edges, 
								int current_node, int distance_from_root,
								vector<int>* eulerian_traversal,
								vector<int>* first_occurance) {

	(*eulerian_traversal).push_back(distance_from_root);
	if ((*first_occurance)[current_node] == -1) {
		(*first_occurance)[current_node] = (*eulerian_traversal).size() - 1;
	}

	for (int child = 0; child < tree_edges[current_node].size(); ++child) {
		int next_node = tree_edges[current_node][child].end_node;
		if ((*first_occurance)[next_node] == -1) {
			compute_eulerian_traversal(tree_edges, tree_edges[current_node][child].end_node, 
				distance_from_root + tree_edges[current_node][child].weight, 
				eulerian_traversal, first_occurance);

			(*eulerian_traversal).push_back(distance_from_root);
			if ((*first_occurance)[current_node] == -1) {
				(*first_occurance)[current_node] = (*eulerian_traversal).size() - 1;
			}
		}
	}
}

void compute_distances_between_nodes(const vector<segment>& requests, 
									 const vector<vector<edge> >& tree_edges,
									 vector<int>* distances_between_nodes) {
	vector<int> eulerian_traversal;
	vector<int> first_occurrence(tree_edges.size(), -1);
	compute_eulerian_traversal(tree_edges, 0, 0, &eulerian_traversal, &first_occurrence);

	segment_tree min_distance_tree;
	min_distance_tree.init_segment_tree(eulerian_traversal, first_occurrence);
	(*distances_between_nodes).resize(requests.size());

	for (int request_index = 0; request_index < requests.size(); ++request_index) {
		(*distances_between_nodes)[request_index] = 
			min_distance_tree.get_distance_between_nodes(requests[request_index]);
	}
}

void print_distances_between_nodes(const vector<int>& distances_between_nodes) {
	for (int request_index = 0; request_index < distances_between_nodes.size(); ++request_index) {
		cout << distances_between_nodes[request_index] << endl;
	}
}

int main() {
	vector<vector<edge> > tree_edges;
	get_tree_edges(&tree_edges);
	
	vector<segment> requests;
	get_requests(&requests);

	vector<int> distances_between_nodes;
	compute_distances_between_nodes(requests,tree_edges, &distances_between_nodes);
	
	print_distances_between_nodes(distances_between_nodes);

	return 0;
}
