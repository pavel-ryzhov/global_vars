#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::pair;
using std::find;
using std::make_pair;
using std::endl;
using std::swap;

struct node_with_distance_to_her
{
	int node;
	int distance;
	node_with_distance_to_her (int node_, int distance_) :
	node(node_), distance(distance_)
	{
	}
};

struct node_of_tree
{
	vector <node_with_distance_to_her> adjacent_vertices;
	node_of_tree ( vector <node_with_distance_to_her> adjacent_vertices_) : 
	adjacent_vertices(adjacent_vertices_)
	{
	}
};

struct node_of_hang_up_tree
{
	node_with_distance_to_her ancestor;
	node_with_distance_to_her left_descendant;
	node_with_distance_to_her right_descendant;
	node_of_hang_up_tree (node_with_distance_to_her ancestor_,  node_with_distance_to_her left_descendant_, node_with_distance_to_her right_descendant_) :
	ancestor(ancestor_), left_descendant(left_descendant_), right_descendant(right_descendant_)
	{
	}
};

struct minimum_in_block
{
	int minimum;
	int right_border;
	minimum_in_block (int minimum_, int right_border_):
	minimum(minimum_), right_border(right_border_)
	{
	}
};

struct hang_up_tree_with_root 
{
	int root;
	vector <node_of_hang_up_tree> nodes;
	hang_up_tree_with_root (int root_, vector <node_of_hang_up_tree> nodes_):
	root(root_), nodes(nodes_)
	{
	}
};
void Read_tree (vector <node_of_tree> &tree)
{
	int number_nodes;
	cin >> number_nodes;
	vector <node_with_distance_to_her> empty_vector;
	for (int i = 0; i < number_nodes; ++i)
	{
		tree.push_back(node_of_tree (empty_vector));
	}

	for (int i = 0 ; i < number_nodes - 1; ++i)
	{
		int first_node;
		cin >> first_node;
		--first_node;
		int second_node;
		cin >> second_node;
		--second_node;
		int distance;
		cin >> distance;
		tree[first_node].adjacent_vertices.push_back(node_with_distance_to_her (second_node, distance) );
		tree[second_node].adjacent_vertices.push_back(node_with_distance_to_her (first_node, distance) );
	}
}


void Read_requests (vector <pair <int, int> >  &requests)
{
	int number_requests;
	cin >> number_requests;
	for (int i = 0; i < number_requests; ++i)
	{
		int first_node;
		cin >> first_node;
		--first_node;
		int second_node;
		cin >> second_node;
		--second_node;
		requests.push_back(pair <int, int> (first_node, second_node));
	}
}

void Read(vector <node_of_tree> &tree, vector <pair <int, int> >  &requests)
{
	Read_tree(tree);
	Read_requests (requests);
}

int Find_element_in_vector (int element, const vector<int> &my_vector)
{
	int number = -1;
	for (int i = 0; i < my_vector.size(); ++i)
	{
		if (my_vector[i] == element)
		{
			number = i;
		}
	}
	return number;
}

void Make_hang_up_node (vector <node_of_hang_up_tree> &nodes_of_hang_up_tree, int node, int ancestor,  
int distance_between_node_and_ancestor, const vector <node_of_tree> &tree)
{

	nodes_of_hang_up_tree[node].ancestor = node_with_distance_to_her (ancestor, distance_between_node_and_ancestor); 
	vector <int> number_adjacent_vertices;

	for (int i = 0; i < tree[node].adjacent_vertices.size(); ++i)
	{
		number_adjacent_vertices.push_back(tree[node].adjacent_vertices[i].node);
	}
	
	int position_ancestor = Find_element_in_vector(ancestor, number_adjacent_vertices);
	vector <node_with_distance_to_her> adjacent_vertices;
	adjacent_vertices  =  tree[node].adjacent_vertices;
	
	if (adjacent_vertices.size() == 2)
	{
	
		swap(adjacent_vertices[0], adjacent_vertices[position_ancestor]);
		nodes_of_hang_up_tree[node].left_descendant  =  adjacent_vertices[1];
		Make_hang_up_node (nodes_of_hang_up_tree,  nodes_of_hang_up_tree[node].left_descendant.node,
		 node,  nodes_of_hang_up_tree[node].left_descendant.distance, tree);
	}
	
	if (adjacent_vertices.size() == 3)
	{

		swap(adjacent_vertices[0], adjacent_vertices[position_ancestor]);
		nodes_of_hang_up_tree[node].left_descendant  =  adjacent_vertices[1];
		Make_hang_up_node (nodes_of_hang_up_tree,  nodes_of_hang_up_tree[node].left_descendant.node,
		  node,  nodes_of_hang_up_tree[node].left_descendant.distance, tree);
		nodes_of_hang_up_tree[node].right_descendant  =  adjacent_vertices[2];
		Make_hang_up_node (nodes_of_hang_up_tree,  nodes_of_hang_up_tree[node].right_descendant.node, 
		 node,  nodes_of_hang_up_tree[node].right_descendant.distance, tree);
	}
}
 
 int Find_root (const vector <node_of_tree> &tree)
 {
	 int node = 0;
	 while (tree[node].adjacent_vertices.size() == 3)
	 {
		 ++node;
	 }
	 return node;
 }
 
hang_up_tree_with_root  Make_hang_up_tree (vector <node_of_tree> &tree)
{
	int root = Find_root(tree);
	tree[root].adjacent_vertices.push_back(node_with_distance_to_her (-1, -1));
	vector <node_of_hang_up_tree> nodes_of_hang_up_tree;
	for (int i = 0; i < tree.size(); ++i)
	{
		nodes_of_hang_up_tree.push_back( node_of_hang_up_tree (node_with_distance_to_her(-1, -1),
	    node_with_distance_to_her(-1, -1),  node_with_distance_to_her(-1, -1) ));
	}
	Make_hang_up_node (nodes_of_hang_up_tree, root, -1, -1,  tree);
	return hang_up_tree_with_root  (root, nodes_of_hang_up_tree);
} 
 
 void Depth_first_search (vector <int> &high_nodes, vector <int> &order,  const hang_up_tree_with_root  &hang_up_tree, vector <int> &distances_to_root) 
 {
	 for (int i = 0; i < hang_up_tree.nodes.size(); ++i)
	 {
		 high_nodes.push_back(-1);
	 }
	 
	 for (int i = 0; i < hang_up_tree.nodes.size(); ++i)
	 {
		 distances_to_root.push_back(-1);
	 }
	 
	 int distance_to_root = 0;
	 int high = 0;
	 int number_passed_nodes = 0;
	 int node = hang_up_tree.root;
	 vector<bool> passed_nodes;
	 for (int i = 0; i < hang_up_tree.nodes.size(); ++i)
	 {
		 passed_nodes.push_back(false);
	 }
	for (;;)
	{
		if (passed_nodes[node] == false)
		{
			passed_nodes[node] = true;
			++number_passed_nodes;
		}	
		 order.push_back(node);
		 high_nodes[node] = high;
		 distances_to_root[node] = distance_to_root;
		 
		 if (number_passed_nodes == hang_up_tree.nodes.size())
		 {
			 return;
		 }

		 int l_d = hang_up_tree.nodes[node].left_descendant.node;

		 if (( l_d> -1 ) && (!passed_nodes[l_d] ))
		 {
			 distance_to_root = distance_to_root + hang_up_tree.nodes[node].left_descendant.distance;
			 node = hang_up_tree.nodes[node].left_descendant.node;	
			 ++high;
		 }
		 
		 else if ((hang_up_tree.nodes[node].right_descendant.node > -1 ) && 
		 ( !passed_nodes[ hang_up_tree.nodes[node].right_descendant.node]) )
		 {
			 distance_to_root = distance_to_root + hang_up_tree.nodes[node].right_descendant.distance;
			 node = hang_up_tree.nodes[node].right_descendant.node;
			 ++high;
		 }
		 
		 else
		 {
			 if (hang_up_tree.nodes[node].ancestor.node == -1) 
			 {
				 return;
			 }
			 distance_to_root = distance_to_root - hang_up_tree.nodes[node].ancestor.distance;
			 node = hang_up_tree.nodes[node].ancestor.node;
			 --high;
		 }
	 }
 } 
 
 void Make_first (vector <int> &first,  int  number_nodes, const vector <int> &order)
 {
	for (int i = 0; i < number_nodes; ++i)
	{
		first.push_back(-1);
	}
	
	 for (int i = 0; i < order.size(); ++i)
	 {
		 first[order[i]] = i;
	 }
 }
 
 void  Make_minimum_in_blocks (vector <minimum_in_block> &minimum_in_blocks, const vector <int> &order, const vector <int> &high_nodes)
 {
	 int number_in_block = 0;
	 const int size_of_block = sqrt (order.size()+ .0) + 1;
	 int minimum_in_block_now;
	 for (int i_order = 0; i_order < order.size(); ++i_order)
	 {
		 if (number_in_block == size_of_block)
		 {
			 minimum_in_blocks.push_back(minimum_in_block (minimum_in_block_now, i_order ));
			 number_in_block = 0;
		 }
		 
		 if (number_in_block == 0)
		 {
			 minimum_in_block_now = order[i_order];
		 }
		 
		 if (high_nodes[order[i_order]] < high_nodes[minimum_in_block_now])
		 {
			minimum_in_block_now = order[i_order];	
		 }
		 
		 ++number_in_block;
	 }
	 minimum_in_blocks.push_back(minimum_in_block (minimum_in_block_now, order.size() ));
 }
 
 int Find_node_minimum_high ( pair <int, int> &orders, const vector <int> &order, 
 const vector <int> &high_nodes, const vector <minimum_in_block> &minimum_in_blocks)
 {
		if (orders.first > orders.second)
		{
			swap(orders.first, orders.second);
		}
		
		int first_block = 0;
		
		while (minimum_in_blocks[first_block].right_border <= orders.first)
		{
			++first_block;
		}

		int second_block = first_block;
		
		while (minimum_in_blocks[second_block].right_border <= orders.second)
		{
			++second_block;
		}
	
		if (first_block == second_block)
		{
			int minimum_now = order[orders.first];
			for (int i_order = orders.first; i_order <= orders.second; ++i_order)
			{
				if (high_nodes[order[i_order]] < high_nodes[minimum_now])
				{
					minimum_now = order[i_order];
				}
			}
			
			return minimum_now;
		}
		
		else
		{
			int minimum_now = order[orders.first];
			for (int i_order = orders.first; i_order < minimum_in_blocks[first_block].right_border; ++i_order)
			{
				if (high_nodes[order[i_order]] < high_nodes[minimum_now])
				{
					minimum_now = order[i_order];
				}
			}
			
			for (int i = first_block + 1; i < second_block; ++i)
			{ 
				if ( high_nodes[minimum_in_blocks[i].minimum] < high_nodes[minimum_now])
				{
					minimum_now = minimum_in_blocks[i].minimum;
				}
			}
			
			for (int i_order = minimum_in_blocks[second_block -1].right_border; i_order < orders.second; ++i_order)
			{
				if (high_nodes[order[i_order]] < high_nodes[minimum_now])
				{
					minimum_now = order[i_order];
				}
			}
			
			return minimum_now;
		}
 }
 
 int Lowest_common_ancestor (const pair <int, int> &nodes,   const vector<int> &first, 
 const vector <int> &order, const vector <int> &high_nodes, const vector <minimum_in_block> &minimum_in_blocks)
 {
	 pair <int, int> orders  (first[nodes.first], first[nodes.second]);
	 return Find_node_minimum_high(orders, order, high_nodes,  minimum_in_blocks);
 }
 
 int Distance_between_descendant_and_ancestor (int descendant, int ancestor, const hang_up_tree_with_root  &hang_up_tree, const vector <int> &distances_to_root)
 {
	 return distances_to_root[descendant] - distances_to_root[ancestor];
 }
 
 int Minimal_distances_between_node (const pair <int, int> &request, const vector<int> &first, const vector <int> &order, const vector <int> &high_nodes,
  const vector <minimum_in_block> &minimum_in_blocks, const hang_up_tree_with_root &hang_up_tree, const vector <int> &distances_to_root)
 {
	 int lowest_common_ancestor = Lowest_common_ancestor (request, first, order, high_nodes, minimum_in_blocks);
	 return Distance_between_descendant_and_ancestor (request.first, lowest_common_ancestor, hang_up_tree, distances_to_root) + 
	 Distance_between_descendant_and_ancestor (request.second, lowest_common_ancestor, hang_up_tree, distances_to_root);
 }
 

vector <int>  Minimal_distances_between_nodes ( vector <node_of_tree> &tree, const vector <pair <int, int> >  &requests)
{ 

	hang_up_tree_with_root  hang_up_tree = Make_hang_up_tree (tree);
	vector <int> high_nodes;
	vector <int> order;
	vector <int> distances_to_root;
	
	Depth_first_search (high_nodes, order, hang_up_tree, distances_to_root);
	
	vector <int> first;
	
	Make_first (first,  hang_up_tree.nodes.size(), order);
	
	vector <minimum_in_block> minimum_in_blocks;

	Make_minimum_in_blocks(minimum_in_blocks, order, high_nodes);

	vector <int> minimal_distances_between_nodes;

	for (int i = 0; i < requests.size(); ++i)
	{
		minimal_distances_between_nodes.push_back(Minimal_distances_between_node (
		requests[i], first, order, high_nodes, minimum_in_blocks, hang_up_tree, distances_to_root));
	}
	
	return minimal_distances_between_nodes;
}

void Output_answer (const vector <int> &minimal_distances_between_nodes)
{
	for (int i = 0; i < minimal_distances_between_nodes.size(); ++i)
	{
		cout << minimal_distances_between_nodes[i] << endl;
	}
}

int main(void)
{
	vector <node_of_tree> tree;
	vector <pair <int, int> >  requests;
	Read(tree, requests);

	vector <int> minimal_distances_between_nodes = Minimal_distances_between_nodes (tree, requests);
	Output_answer(minimal_distances_between_nodes);

	return 0;
}

