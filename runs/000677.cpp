#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::for_each;
using std::transform;
using std::mem_fun;
using std::swap;

//Первый член пары - вершина, куда тянется ребро, вторая - расстояние
typedef vector< vector< pair<int, int> > > graph;

class LCASolver{
	void DoVertex(const vector< vector<int> > &, int, int, int);
	void BuildSegmentTree(int, int, int);
	int LCATreeMin(int, int, int, int, int);
	vector<int> depths_array, index_to_depths_array_map, depths_array_to_index_map, segment_tree;
public:
	void Init(const vector< vector<int> > &ordinary_graph);
	int LCA(const int first, const int second);
};

void LCASolver::DoVertex(
		const vector< vector<int> > &operational_graph,
		int parent_index,
		int current_index,
		int current_depth = 0)
{
	depths_array.push_back(current_depth);
	index_to_depths_array_map[current_index] = (int)depths_array.size() - 1;
	depths_array_to_index_map.push_back(current_index);
	for(vector<int>::size_type i = 0; i < operational_graph[current_index].size(); ++i)
	{
		int child_index = operational_graph[current_index][i];
		if(child_index != parent_index)
		{
			DoVertex(operational_graph, current_index, child_index, current_depth + 1);
			depths_array.push_back(current_depth);
			depths_array_to_index_map.push_back(current_index);
		}
	}
}

void LCASolver::BuildSegmentTree(int current, int left_index, int right_index)
{
	if (left_index == right_index)
		segment_tree[current] = left_index;
	else
	{
		int mid = (left_index + right_index) / 2, left_child = current + current, right_child = left_child + 1;
		BuildSegmentTree(left_child, left_index, mid);
		BuildSegmentTree(right_child, mid + 1, right_index);
		if (depths_array[segment_tree[left_child]] < depths_array[segment_tree[right_child]])
			segment_tree[current] = segment_tree[left_child];
		else
			segment_tree[current] = segment_tree[right_child];
	}
}

void LCASolver::Init(const std::vector<vector<int> > &ordinary_graph)
{
	depths_array.reserve(2 * ordinary_graph.size());
	index_to_depths_array_map.resize(ordinary_graph.size());
	depths_array_to_index_map.reserve(2 * ordinary_graph.size());
	DoVertex(ordinary_graph, 0, 0);

	segment_tree.assign(4 * depths_array.size() + 1, -1);
	BuildSegmentTree(1, 0, (int)depths_array.size() - 1);
}

int LCASolver::LCATreeMin(
		int current,
		int search_left, int search_right,
		int left, int right)
{
	if (search_left == left && search_right == right)
		return segment_tree[current];
	int search_mid = (search_left + search_right) / 2, 
		left_child = current + current,
		right_child = left_child + 1;
	if (right <= search_mid)
		return LCATreeMin(left_child, search_left, search_mid, left, right);
	if (left > search_mid)
		return LCATreeMin(right_child, search_mid + 1, search_right, left, right);
	int ans1 = LCATreeMin(left_child, search_left, search_mid, left, search_mid);
	int ans2 = LCATreeMin(right_child, search_mid + 1, search_right, search_mid + 1, right);
	return depths_array[ans1] < depths_array[ans2] ? ans1 : ans2;
}

int LCASolver::LCA(const int first, const int second)
{
	int left_in_depths_array = index_to_depths_array_map[first],
		right_in_depths_array = index_to_depths_array_map[second];
	if(right_in_depths_array < left_in_depths_array)
	{
		swap(right_in_depths_array, left_in_depths_array);
	}
	return depths_array_to_index_map[
			LCATreeMin(1, 0, (int)depths_array.size() - 1, left_in_depths_array, right_in_depths_array)];
}

inline int GetFirstInPair(const pair<int, int> &p) {return p.first;}

vector<int> MakeOrdinaryVertexFromWeighed(const vector< pair<int, int> > &weighted_vertex)
{
	vector<int> result_array(weighted_vertex.size());
	transform(
		weighted_vertex.begin(), weighted_vertex.end(),
		result_array.begin(),
		GetFirstInPair);
	return result_array;
}

vector< vector<int> > MakeOrdinaryGraphFromWeighed(const graph &weighted_graph)
{
	vector< vector<int> > result_graph(weighted_graph.size());
	transform(
		weighted_graph.begin(), weighted_graph.end(),
		result_graph.begin(),
		MakeOrdinaryVertexFromWeighed);
	return result_graph;
}

void AddVertexToRangesArray(
		vector<int> *ranges_array,
		int parent_index,
		int current_index,
		const graph &operational_graph)
{
	for(vector<int>::size_type i = 0; i < operational_graph[current_index].size(); ++i)
	{
		int child_index = operational_graph[current_index][i].first;
		if(child_index != parent_index)
		{
			ranges_array->at(child_index) = 
				ranges_array->at(current_index) +
				operational_graph[current_index][i].second;
			AddVertexToRangesArray(
				ranges_array,
				current_index,
				child_index,
				operational_graph);
		}
	}
}

vector<int> MakeRangesFromRootArray(const graph &weighted_graph)
{
	vector<int> result_array(weighted_graph.size());
	const int non_existing_index = -1;
	result_array[0] = 0;
	AddVertexToRangesArray(
		&result_array,
		non_existing_index,
		0,
		weighted_graph);

	return result_array;
}

vector<int> GetMinimumRangesInGraph(
				const graph &operational_graph, 
				const vector< pair<int, int> > requests_array)
{
	vector< vector<int> > ordinary_graph = MakeOrdinaryGraphFromWeighed(operational_graph);
	vector<int> ranges_from_root = MakeRangesFromRootArray(operational_graph);

	LCASolver solver;
	
	solver.Init(ordinary_graph);

	vector<int> answers;
	answers.reserve(requests_array.size());
	for(unsigned int i = 0; i < requests_array.size(); ++i)
	{
		answers.push_back(
			ranges_from_root[requests_array[i].first] +
			ranges_from_root[requests_array[i].second] - 
			2 * ranges_from_root[solver.LCA(requests_array[i].first, requests_array[i].second)]);
	}
	
	return answers;
}

void Input(graph *operational_graph, vector< pair<int, int> > *requests_array)
{
	int vertex_number;
	cin >> vertex_number;
	operational_graph->resize(vertex_number);
	for(int i = 0; i < vertex_number - 1; ++i)
	{
		int first_vertex, second_vertex, length;
		cin >> first_vertex >> second_vertex >> length;
		operational_graph->at(first_vertex - 1).push_back(
			make_pair(second_vertex - 1, length));
		operational_graph->at(second_vertex - 1).push_back(
			make_pair(first_vertex - 1, length));
	}

	int requests_number;
	cin >> requests_number;
	requests_array->reserve(requests_number);
	for(int i = 0; i < requests_number; ++i)
	{
		int first_vertex, second_vertex;
		cin >> first_vertex >> second_vertex;
		requests_array->push_back(
			make_pair(first_vertex - 1, second_vertex - 1));
	}
}

inline void MyPrintf(const int output_value)
{
	cout << output_value << endl;
}

void Output(const vector<int> &output_array)
{
	for_each(
		output_array.begin(), output_array.end(), 
		MyPrintf);
}

int main()
{
	graph operational_graph;
	vector< pair<int, int> > requests_array;
	Input(&operational_graph, &requests_array);

	vector<int> minimum_ranges_in_graph = 
		GetMinimumRangesInGraph(operational_graph, requests_array);

	Output(minimum_ranges_in_graph);
	return 0;
}
