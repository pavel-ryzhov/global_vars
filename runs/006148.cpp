//#include "stdafx.h"
#include <iostream>
#include <vector>
#include "math.h"

using std::pair;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

typedef vector<vector<vector<int> > > BlockMatrix;
struct Node {
	vector<int> children;
	int parent;
	int distance_from_parent;
	int distance_from_root;
};

struct Edge {
	int parent;
	int child;
	int weight;
};

class TreeProcessor {
	vector<int> dfs_order;
	vector<int> nodes_height;
	vector<int> first_appear;
	vector<pair<int, int> > minimums_positions;
	vector<vector<int> > sparse_matrix;			// в ячейках - индексы - номера блоков, из которых надо брать мин.знач.
	BlockMatrix block_matrix;					// хранит все виды разреж.матриц для блоков (2^(k-1))
	vector<int> types_for_blocks;				// каждому блоку присвоен индекс по которому надо искать его матрицу в block_matrix
	vector<int> bin_degrees;
	int tree_size;
	int block_size;

	// Для предварительной обработки:
	void FindDfsOrder(vector<Node>& tree, int start);
	void FindNodesHeight();
	void FindNodesFirstAppear();
	void FindMinimumsInBlocks();
	void CreateSparseMatrixForMinimumVector();
	void PrepareBlockDescriptors();
	void BuildSparseMatrix(vector<int>& first_column, vector<vector<int> >* result_matrix);
	void DescribeBlockTypes();
	void CountBinDegrees();

	// Для обработки запроса
	int FindLCA(int v1, int v2);				// Вернули индекс LCA
	int GetAnswerFromSparseTable(int left, int right, vector<int>& values, vector<vector<int> >& table);
public:
	void GetInformationOffline(vector<Node>& tree);
	void ProcessInformationOffline();	
	int CountDistanceBetweenNodes(int v1, int v2, vector<Node>& tree);
};


void TreeProcessor::FindDfsOrder(vector<Node>& tree, int start) {
	
	for (int i_child = 0; i_child < tree[start].children.size(); ++i_child) {
		dfs_order.push_back(tree[start].children[i_child]);
		FindDfsOrder(tree, tree[start].children[i_child]);
		dfs_order.push_back(start);
		
	}
}

void TreeProcessor::FindNodesHeight() {
	nodes_height.resize(dfs_order.size());
	int current_height = 0;
	nodes_height[0] = current_height;
	for (int i = 1; i < dfs_order.size(); ++i) {
		if (dfs_order[i] > dfs_order[i - 1]) {
			++current_height;
		} else {
			--current_height;
		}
		nodes_height[i] = current_height;
	}
}

void TreeProcessor::FindNodesFirstAppear() {
	first_appear.resize(tree_size);
	for (int i = 0; i < first_appear.size(); ++i) {
		first_appear[i] = -1;
	}
	for (int i = 0; i < dfs_order.size(); ++i) {
		if (first_appear[dfs_order[i]] == -1) {
			first_appear[dfs_order[i]] = i;
		}
	}
}

void TreeProcessor::FindMinimumsInBlocks() {
	block_size = ceil(0.5*log((double)nodes_height.size())/log(2.0));
	int block_minimum = nodes_height[0];
	int minimum_position = 0;
	int current_block_size = 0;
	for (int i_order = 0; i_order < nodes_height.size(); ++i_order) {
		if (nodes_height[i_order] < block_minimum) {
			block_minimum = nodes_height[i_order];
			minimum_position = i_order;
		}
		++current_block_size;
		if ((current_block_size == block_size) || (i_order + 1 == nodes_height.size())) {
			minimums_positions.push_back(pair<int, int>(block_minimum, minimum_position));
			if (i_order + 1 < nodes_height.size()) {
				block_minimum = nodes_height[i_order+1];
				minimum_position = i_order + 1;
			}
			current_block_size = 0;
		}
	}
}

void TreeProcessor::CreateSparseMatrixForMinimumVector() {
	
	//	sparse_matrix - разреженная матрица, составленная для поиска минимума на отрезке в векторе минимумов блоков
	//	!!! строк столько, сколько блоков, столбцов 1 + ceil(лог2(N)) 
	vector<int> first_column;

	for (int i = 0; i < minimums_positions.size(); ++i) {
		first_column.push_back(minimums_positions[i].first);
	}
	BuildSparseMatrix(first_column, &sparse_matrix);
	for (int i_row = 0; i_row < sparse_matrix.size(); ++i_row) {
		for (int i_col = 0; i_col < sparse_matrix[0].size(); ++i_col) {
			sparse_matrix[i_row][i_col] = minimums_positions[sparse_matrix[i_row][i_col]].second;
		}
	}

}

int CountMaskForVector(vector<int>& intvector) {
	// -1->0 +1->1
	int mask = 0;
	int last_value = 0;
	int bin_degree = intvector.size() - 2;
	
	for (int i = 1; i < intvector.size(); ++i, --bin_degree) {
		mask += pow(2.0, (double)bin_degree)*(intvector[i] > last_value);
		last_value = intvector[i];		
	}

	return mask;
}

void CountVectorForMask(int mask, int length, vector<int>* intvector) {
	
	intvector->push_back(0);
	if (length < 2) {
		return;
	}
	int last_value = 0;
	int mask_iterator = 1<<(length - 2);
	while (mask_iterator) {
		if (mask_iterator&mask) {
			intvector->push_back(++last_value);
		} else {
			intvector->push_back(--last_value);
		}
		mask_iterator = mask_iterator >> 1;
	}
}


// индексы должны быть из того массива, для которого строим матрицу
void TreeProcessor::BuildSparseMatrix(vector<int>& first_column, vector<vector<int> >* result_matrix) {
	result_matrix->resize(first_column.size());
	for (int i_row = 0; i_row < result_matrix->size(); ++i_row) {
		result_matrix->at(i_row).push_back(i_row);
	}

	int columns_number = 1 + ceil(log((double)first_column.size())/log(2.0));
	for (int i_col = 1; i_col < columns_number; ++i_col) {
		for (int i_row = 0; i_row < result_matrix->size(); ++i_row) {
			int minimum_of_segment = result_matrix->at(i_row)[i_col - 1];
			if (i_row + pow(2.0, (double)(i_col - 1)) < result_matrix->size()) {
				if (first_column[result_matrix->at(i_row + pow(2.0, (double)(i_col - 1)))[i_col - 1]] < first_column[minimum_of_segment]) {
					minimum_of_segment = result_matrix->at(i_row + pow(2.0, (double)(i_col - 1)))[i_col - 1];
				}
			}
			result_matrix->at(i_row).push_back(minimum_of_segment);
		}
	}
}

void TreeProcessor::PrepareBlockDescriptors() {
	int types_number = pow(2.0, block_size - 1);
	for (int i_type = 0; i_type < types_number; ++i_type) {
		vector<vector<int> > next_matrix;
		vector<int> first_column;
		CountVectorForMask(i_type, block_size, &first_column);
		vector<int> indeces;
		indeces.resize(first_column.size());
		BuildSparseMatrix(first_column, &next_matrix);
		block_matrix.push_back(next_matrix);
	}
}

void TreeProcessor::DescribeBlockTypes() {
	vector<int> current_block;
	int first_element_in_block;
	for (int i = 0; i < nodes_height.size(); ++i) {
		if (current_block.size() == 0) {
			first_element_in_block = nodes_height[i];
		}
		current_block.push_back(nodes_height[i] - first_element_in_block);
		if ((current_block.size() == block_size)) {
			types_for_blocks.push_back(CountMaskForVector(current_block));
			current_block.clear();
		} else if  (i + 1 == nodes_height.size()) {
			int last_element = current_block[current_block.size()-1] + 1;
			while (current_block.size() < block_size) {
				current_block.push_back(last_element);
				++last_element;
			}
			types_for_blocks.push_back(CountMaskForVector(current_block));
		}
	}
}

void TreeProcessor::CountBinDegrees() {
	bin_degrees.resize(dfs_order.size());
	int exp = 0;
	int deg = 1; // 2^0 = 1
	bin_degrees[0] = -1;
	for (int i = 1; i < bin_degrees.size(); ++i) {
		if (deg*2 <= i) {
			deg = deg*2;
			++exp;
		}
			bin_degrees[i] = exp;
	}
}

void TreeProcessor::GetInformationOffline(vector<Node>& tree) {
	tree_size = tree.size();
	dfs_order.push_back(0);
	FindDfsOrder(tree, 0);
	int last_dfs = dfs_order[dfs_order.size()-1];
	if (dfs_order.size() > 1) {
		while ((dfs_order[dfs_order.size() - 2] > dfs_order[dfs_order.size() - 1])) {
			dfs_order.pop_back();
		}
	}
	FindNodesHeight();
	FindNodesFirstAppear();
}

void TreeProcessor::ProcessInformationOffline() {
	CountBinDegrees();
	FindMinimumsInBlocks();
	CreateSparseMatrixForMinimumVector();
	PrepareBlockDescriptors();
	DescribeBlockTypes();
}
void Swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}

int TreeProcessor::GetAnswerFromSparseTable(int left, int right, vector<int>& values, vector<vector<int> >& table) {
	int bin_degree = bin_degrees[right - left + 1];
	if (values[table[left][bin_degree]] < values[table[right - pow(2.0, bin_degree) + 1][bin_degree]]) {
		return table[left][bin_degree];
	} else {
		return table[right - pow(2.0, bin_degree) + 1][bin_degree];
	}
}

// вернуть индекс лса
int TreeProcessor::FindLCA(int v1, int v2) {
	if (first_appear[v1] > first_appear[v2]) {
		Swap(v1, v2);
	}
	if (v1 == v2) {
		return 0;
	}
	int block_left = first_appear[v1]/block_size;
	int block_right = first_appear[v2]/block_size;
	
	vector<int> block;
	for (int i = 0; i < block_size; ++i) {
		if (block_left*block_size + i < dfs_order.size()) {
			block.push_back(nodes_height[block_left*block_size + i]);
		}
	}

	if (block_left == block_right) {
		int index_minimum = GetAnswerFromSparseTable(first_appear[v1]%block_size, first_appear[v2]%block_size, block, block_matrix[types_for_blocks[block_left]]);
		index_minimum += block_left*block_size;
		int minimum = nodes_height[index_minimum];
		return dfs_order[index_minimum];
	}
    int index_minimum_left_block = GetAnswerFromSparseTable(first_appear[v1]%block_size, block_size - 1, block, block_matrix[types_for_blocks[block_left]]);
	index_minimum_left_block += block_left*block_size;
	int minimum_left_block = nodes_height[index_minimum_left_block];
	
	block.clear();
	for (int i = 0; i < block_size; ++i) {
		if (block_right*block_size + i < dfs_order.size()) {
			block.push_back(nodes_height[block_right*block_size + i]);
		}
	}
	int index_minimum_right_block = GetAnswerFromSparseTable(0, first_appear[v2]%block_size, block, block_matrix[types_for_blocks[block_right]]);
	index_minimum_right_block += block_right*block_size;
	int minimum_right_block = nodes_height[index_minimum_right_block];
	int answer_index = index_minimum_left_block;
	int answer_minimum = minimum_left_block;

	if (minimum_right_block < minimum_left_block) {
		answer_index = index_minimum_right_block;
		answer_minimum = minimum_right_block;
	}
	
	if (block_right - block_left < 2) {
		return dfs_order[answer_index];
	}
	int index_minimum_node_between = GetAnswerFromSparseTable(block_left + 1, block_right - 1, nodes_height, sparse_matrix);
	int minimum_node_between = nodes_height[index_minimum_node_between];

	if (minimum_node_between < answer_minimum) {
		answer_index = index_minimum_node_between;
	}
	return dfs_order[answer_index];

}

int TreeProcessor::CountDistanceBetweenNodes(int v1, int v2, vector<Node>& tree) {
	if (v1 == v2) {
		return 0;
	}
	int LCAindex = FindLCA(v1, v2);
	int distance = 0;
	distance = tree[v1].distance_from_root + tree[v2].distance_from_root - 2*tree[LCAindex].distance_from_root;
	return distance;
}
void ModifyNodesNames(int parent_name, int child_name, int* pcounter, vector<int>* new_nodes_names, vector<Edge>* delay_edges, pair<int, int>* new_edge) {
	if (*pcounter == 0) {
		new_nodes_names->at(parent_name - 1) = *pcounter;
		++(*pcounter);
	}
	if (new_nodes_names->at(parent_name - 1) != -1) {
		new_nodes_names->at(child_name - 1) = *pcounter;
		++(*pcounter);
		new_edge->first = new_nodes_names->at(parent_name - 1);
		new_edge->second = new_nodes_names->at(child_name - 1);
	} else if (new_nodes_names->at(child_name - 1) != -1) {
		new_nodes_names->at(parent_name - 1) = *pcounter;
		++(*pcounter);
		new_edge->second = new_nodes_names->at(parent_name - 1);
		new_edge->first = new_nodes_names->at(child_name - 1);
	} else {
		Edge delay_edge;
		delay_edge.parent = parent_name;
		delay_edge.child = child_name;
		delay_edges->push_back(delay_edge);
	}
}

void CountDistanceFromRoot(int start, vector<Node>* tree, int* c) {
	for (int i_child = 0; i_child < tree->at(start).children.size(); ++i_child) {
		int next_child = tree->at(start).children[i_child];
		tree->at(next_child).distance_from_root  = tree->at(start).distance_from_root + tree->at(next_child).distance_from_parent;
		//cout << "in: " << *c << endl;
		++(*c);
		CountDistanceFromRoot(tree->at(start).children[i_child], tree, c);
		--(*c);
		//cout << "out: " << *c << endl;
	}
}

void Input(vector<Node>* tree, vector<pair<int, int> >* requests) {
	
	vector<int> new_nodes_names;				// in old_name-1 is index here
	int tree_size;
	cin >> tree_size;
	tree->resize(tree_size);
	new_nodes_names.resize(tree_size);
	vector<Edge> delay_edges;
	for (int i_name = 0; i_name < tree_size; ++i_name) {
		new_nodes_names[i_name] = -1;
	}
	tree->at(0).parent = -1;
	tree->at(0).distance_from_parent = -1;
	int names_counter = 0;
	for (int i_edge = 0; i_edge < tree_size - 1; ++i_edge) {
		int parent, child, weight;
		cin >> parent >> child >> weight;
		//parent = i_edge + 1;
		//child = i_edge + 2;
		//weight = i_edge + 1;
		pair<int, int> new_edge(-1, -1);
		ModifyNodesNames(parent, child, &names_counter, &new_nodes_names, &delay_edges, &new_edge);
		if (new_edge.first != -1) {
			tree->at(new_edge.first).children.push_back(new_edge.second);
			tree->at(new_edge.second).parent = new_edge.first;
			tree->at(new_edge.second).distance_from_parent = weight;
		} else {
			delay_edges[delay_edges.size() - 1].weight = weight;
		}
	}

	int added_edges = 0;
	while (added_edges < delay_edges.size()) {
		for (int i_delay = 0; i_delay < delay_edges.size(); ++i_delay) {
			pair<int, int> new_edge(-1, -1);
			if ((new_nodes_names[delay_edges[i_delay].child - 1] == -1) != (new_nodes_names[delay_edges[i_delay].parent - 1] == -1)) {
				ModifyNodesNames(delay_edges[i_delay].parent, delay_edges[i_delay].child, &names_counter, &new_nodes_names, &delay_edges, &new_edge);
				tree->at(new_edge.first).children.push_back(new_edge.second);
				tree->at(new_edge.second).parent = new_edge.first;
				tree->at(new_edge.second).distance_from_parent = delay_edges[i_delay].weight;
				++added_edges;
			}
		}
	}
	if (tree->size() == 1) {
		new_nodes_names[0] = 0;
	}
	tree->at(0).distance_from_root = 0;
	int c = 0;
	CountDistanceFromRoot(0, tree, &c);

	int requests_number;
	cin >> requests_number;
	requests->resize(requests_number);

	for (int i_req = 0; i_req < requests_number; ++i_req) {
		int first_node, second_node;
		cin >> first_node >> second_node;
		//first_node = 1;
		//second_node = i_req + 1;
		requests->at(i_req) = pair<int, int>(new_nodes_names[first_node - 1], new_nodes_names[second_node - 1]);
	}


}


int main()
{
	vector<Node> tree;
	vector<pair<int, int> > requests;
	Input(&tree, &requests);
	TreeProcessor tree_processor;
	tree_processor.GetInformationOffline(tree);
	tree_processor.ProcessInformationOffline();
	for (int i_req = 0; i_req < requests.size(); ++i_req) {
		cout << tree_processor.CountDistanceBetweenNodes(requests[i_req].first, requests[i_req].second, tree) << endl;
	}
	
	return 0;
}

