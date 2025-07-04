#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <math.h>
#include <fstream>

using std::ifstream;
using std::istream;
using std::vector;
using std::list;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::stack;
using std::min;
using std::max;

ifstream fin;

const int NOT_DEFINED_YET = -1, MAX_INT_VALUE = 40001;
const int WHITE = 0, GREY = 1, BLACK = 2;

int get_minimal_index_in_vector (const vector<int>& input_vector, int first, int second) {
	return input_vector[first] <= input_vector[second] ? first : second;
}

class Tree {
private:
	class TreeNode {
	public:
		list<pair<int, int> > connected;
		int first_occurence, depth, height; //depth - path price
		TreeNode() : depth(NOT_DEFINED_YET), height(NOT_DEFINED_YET), first_occurence(NOT_DEFINED_YET){}
	};

	int size_of_block, number_of_blocks;
	vector<TreeNode> nodes;

	vector<int> order, heights;

	vector<int> index_of_maximal_powers_of_two;

	vector<int> mins_for_blocks_positions;
	vector< vector <int> > sparse_table_for_blocks;

	vector< vector< vector <int> > > mins_positions_for_masks;
	vector<int> masks_numbers_for_blocks;

	void count_maximal_powers_of_two ();
	void lca_precounting();
	void lca_depth_first_search();
	void count_mins_for_each_block ();
	void build_sparse_table_for_blocks ();
	void count_mins_positions_for_masks ();
	void count_masks_numbers_for_blocks();
	int get_minimum_in_inside_blocks (int first_block, int second_block);
	int rmq_in_heights (int l, int r);
public:	
	int getMinimalWay (int l, int r);
	void create_tree (istream& in);
};

void Tree::create_tree(istream& in) {
	int nodes_number;
	in >> nodes_number;
	nodes.resize(nodes_number);
	for (int i = 0; i < nodes_number - 1; ++i) {
		int edge_begin, edge_end, edge_value;
		in >> edge_begin >> edge_end >> edge_value;
		nodes[edge_begin - 1].connected.push_back(make_pair(edge_end - 1, edge_value));
		nodes[edge_end - 1].connected.push_back(make_pair(edge_begin - 1, edge_value));
	}
	lca_precounting();
}

void Tree::lca_precounting(){
	order.reserve(2 * nodes.size() - 1);
	lca_depth_first_search();
	heights.resize(order.size());
	for (int i = 0; i < order.size(); ++i) {
		heights[i] = nodes[order[i]].height;
	}
	size_of_block = max(1.0, ceil(0.5 * log ((double)order.size()) / log(2.0)));
	number_of_blocks = ceil((double)order.size() / size_of_block);
	count_mins_for_each_block();
	build_sparse_table_for_blocks();
	count_mins_positions_for_masks();
	count_masks_numbers_for_blocks();
	count_maximal_powers_of_two();
}

void Tree::lca_depth_first_search() {
	const int WHITE = 0, GREY = 1, BLACK = 2;
	vector<int> colors (nodes.size(), WHITE);
	stack<int> pending_nodes;
	colors[0] = GREY;
	pending_nodes.push(0);
	nodes[0].depth = (nodes[0].height = (nodes[0].first_occurence = 0));
	while (!pending_nodes.empty()) {
		int current_node = pending_nodes.top();
		if (order.empty() || (order[order.size() - 1] != current_node) ) { //current_node - не лист, листы встречаются в pendind_nodes два раза подряд
			order.push_back(current_node);
			if (nodes[current_node].first_occurence == NOT_DEFINED_YET) {
				nodes[current_node].first_occurence = order.size() - 1;
			}
		}
		if (colors[current_node] == BLACK) {
			pending_nodes.pop();
		}
		else {
			for (list<pair <int, int> >::reverse_iterator it = nodes[current_node].connected.rbegin(); 
				it != nodes[current_node].connected.rend(); ++it) {
					if (colors[(*it).first] == WHITE) {
						if (it != nodes[current_node].connected.rbegin()) {
							pending_nodes.push(current_node);
						}
						colors[(*it).first] = GREY;
						nodes[(*it).first].depth = nodes[current_node].depth + (*it).second;
						nodes[(*it).first].height = nodes[current_node].height + 1;
						pending_nodes.push((*it).first);
					}
			}
			colors[current_node] = BLACK;
		}
	}
}

void Tree::count_mins_for_each_block () {
	vector<int> mins_for_blocks (number_of_blocks, MAX_INT_VALUE);
	mins_for_blocks_positions.resize(number_of_blocks, 0);
	for (int i = 0; i < heights.size(); ++i) {
		if (heights[i] < mins_for_blocks[i / size_of_block]) {
			mins_for_blocks[i / size_of_block] = heights[i];
			mins_for_blocks_positions [i / size_of_block] = i;
		}
	}
}

void Tree::build_sparse_table_for_blocks () {
	int max_index = log((double) number_of_blocks)/log(2.0) + 1; //мин. показатель степени двойки, покрывающий массив минимумов в блоках
	sparse_table_for_blocks.resize(number_of_blocks, vector<int>(max_index));
	for (int i = 0; i < sparse_table_for_blocks.size(); ++i) {
		sparse_table_for_blocks[i][0] = mins_for_blocks_positions[i];
	}
	for (int length_index = 1; length_index < max_index; ++length_index) {
		for (int start = 0; start < mins_for_blocks_positions.size(); ++start) {
			sparse_table_for_blocks[start][length_index] = get_minimal_index_in_vector(heights,
					sparse_table_for_blocks[start][length_index - 1],
					sparse_table_for_blocks[
					min(start + (int)pow(2.0, length_index - 1) , ((int)sparse_table_for_blocks.size() - 1))]
					[length_index - 1]);
		}
	}
}

void Tree::count_mins_positions_for_masks () {
	mins_positions_for_masks.resize(pow(2.0, size_of_block - 1));
	for (int mask_number = 0; mask_number < mins_positions_for_masks.size(); ++mask_number) {
		vector<int> current_mask_array (size_of_block);
		current_mask_array[0] = 0;
		for (int i = 1; i < size_of_block; ++i) {
			if ((mask_number & (1 << size_of_block - i - 1)) == 0) {
				current_mask_array[i] = current_mask_array[i - 1] - 1;
			}
			else {
				current_mask_array[i] = current_mask_array[i - 1] + 1;
			}
		}
		vector< vector <int> > current_mask_table (size_of_block, vector<int> (size_of_block));
		for (int begin = 0; begin < size_of_block; ++begin) {
			current_mask_table[begin][begin] = begin;
			for (int end = begin + 1; end < size_of_block; ++end) {
				current_mask_table[begin][end] = (current_mask_array[current_mask_table[begin][end - 1]] <= 
					current_mask_array[end]) ? current_mask_table[begin][end - 1] : end;
			}
		}
		mins_positions_for_masks[mask_number] = current_mask_table;
	}
}

void Tree::count_masks_numbers_for_blocks() {
	masks_numbers_for_blocks.resize(number_of_blocks);
	for (int current_block = 0; current_block < number_of_blocks; ++current_block) {
		vector<int> current_mask (size_of_block);
		int first_element_in_current_block = size_of_block * current_block;
		current_mask[0] = 0;
		for (int i = 1; i < size_of_block; ++i) {
			current_mask[i] = current_mask[i - 1] + heights[min(i + first_element_in_current_block, (int)heights.size() - 1)] 
			- heights[min(i - 1 + first_element_in_current_block, (int)heights.size() - 1)];
		}
		int mask_number = 0;
		for (int bit_number = 1; bit_number < current_mask.size(); ++bit_number) {
			mask_number = mask_number << 1;
			if(current_mask[bit_number] - current_mask[bit_number - 1] == 1) {
				++mask_number;
			}
		}
		masks_numbers_for_blocks[current_block] = mask_number;
	}
}

int Tree::rmq_in_heights (int l, int r) {
	int left_index = min (nodes[l - 1].first_occurence, nodes[r - 1].first_occurence);
	int right_index = max (nodes[l - 1].first_occurence, nodes[r - 1].first_occurence);
	int first_block_number = left_index / size_of_block;
	int second_block_number  = right_index / size_of_block;
	int index_in_first_block = left_index % size_of_block;
	int index_in_second_block = right_index % size_of_block;
	switch(second_block_number - first_block_number) {
	case 0:
		return first_block_number * size_of_block + 
			mins_positions_for_masks[masks_numbers_for_blocks[first_block_number]][index_in_first_block][index_in_second_block];
	case 1:
		return get_minimal_index_in_vector(heights,
			first_block_number * size_of_block + 
			mins_positions_for_masks[masks_numbers_for_blocks[first_block_number]][index_in_first_block][size_of_block - 1],
			second_block_number * size_of_block + 
			mins_positions_for_masks[masks_numbers_for_blocks[second_block_number]][0][index_in_second_block]);
	default:
		int min_in_edges = get_minimal_index_in_vector(heights,
			first_block_number * size_of_block + 
			mins_positions_for_masks[masks_numbers_for_blocks[first_block_number]][index_in_first_block][size_of_block - 1],
			second_block_number* size_of_block + 
			mins_positions_for_masks[masks_numbers_for_blocks[second_block_number]][0][index_in_second_block]);
		int min_in_inside_blocks = get_minimum_in_inside_blocks(first_block_number + 1, second_block_number - 1);
		return get_minimal_index_in_vector(heights, min_in_edges, min_in_inside_blocks);
	}	
}

int Tree::get_minimum_in_inside_blocks (int first_block, int second_block) {	
	int max_binary_length = index_of_maximal_powers_of_two[second_block - first_block];
	return heights[sparse_table_for_blocks[first_block][max_binary_length]] <= 
		heights[sparse_table_for_blocks[second_block - pow(2.0, max_binary_length) + 1][max_binary_length]] ?
			sparse_table_for_blocks[first_block][max_binary_length] :
			sparse_table_for_blocks[second_block - pow(2.0, max_binary_length) + 1][max_binary_length];		
}

int Tree::getMinimalWay (int l, int r)  {
	int min_v = rmq_in_heights(l,r);
	return nodes[l - 1].depth + nodes[r - 1].depth - 2 * nodes[order[min_v]].depth;
}

void Tree::count_maximal_powers_of_two () {
	index_of_maximal_powers_of_two.resize(number_of_blocks + 1);
	index_of_maximal_powers_of_two[0] = 0;
	int number = 1;
	while (number < index_of_maximal_powers_of_two.size()) {
		if (pow (2.0, index_of_maximal_powers_of_two[number - 1] + 1) > number) {
			index_of_maximal_powers_of_two[number] = index_of_maximal_powers_of_two[number - 1];
		}
		else {
			index_of_maximal_powers_of_two[number] = index_of_maximal_powers_of_two[number - 1] + 1;
		}
		++number;
	}
}

void input (Tree* t) {
	t->create_tree(cin);
}

int main() {
	Tree t;
	input(&t);
	int number_of_tests;
	cin >> number_of_tests;
	for (int i = 0; i < number_of_tests; ++i) {
		int l, r;
		cin >> l >> r;
		cout << t.getMinimalWay(l,r) << endl;
	}
	return 0;
}