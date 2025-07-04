#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::min;
using std::max;
using std::vector;
using std::pair;
using std::ostream;
using std::istream;
using std::endl;
using std::ifstream;

struct edge
{
	int parent;
	int son;
	int length;
	
	edge()
	{ }
	
	edge(int n_parent, int n_son, int n_length):
		parent(n_parent), son(n_son), length(n_length)
 	{ }
};
	

void read_input_data(istream& in, vector<edge>* edges,
	vector < pair<int, int> >* vertice_pairs)
{
	int number_of_vertices;
	
	in >> number_of_vertices;
	
	edges->resize(number_of_vertices - 1);
	
	for (int index = 0; index < (*edges).size(); ++index)
	{
		in >> (*edges)[index].parent;
		in >> (*edges)[index].son;
		in >> (*edges)[index].length;
	}
	
	int number_of_vertice_pairs;
	
	in >> number_of_vertice_pairs;
	
	vertice_pairs->resize(number_of_vertice_pairs);
	
	for (int index = 0; index < number_of_vertice_pairs; ++index)
	{
		in >> (*vertice_pairs)[index].first;
		in >> (*vertice_pairs)[index].second;
	}
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct element_of_segment_tree
{
	int first_index;
	int second_index;
	T minimum;
	
	element_of_segment_tree()
	{ }

	element_of_segment_tree(int n_first_index,	int n_second_index,
		const T& n_minimum):
			first_index(n_first_index),
			second_index(n_second_index),
			minimum(n_minimum)
	{ }
};

template <typename T>
class segment_tree
{
	vector < element_of_segment_tree<T> > m_canonical_segments;

	void build_segment_tree(
		const vector<T>& numbers,
		int first_index, int second_index,
		int current_canonical_segment_index,
		vector <element_of_segment_tree<T> >* canonical_segments)
 	{
		if (first_index > second_index)
		{
			return;
  		}

		if (current_canonical_segment_index == 0)
		{
			canonical_segments->resize(4 * numbers.size());
		}

		if (first_index == second_index)
		{
			(*canonical_segments)[current_canonical_segment_index] =
			    element_of_segment_tree<T>(first_index, second_index,
					numbers[first_index]);
			return;
		}

		int middle_index = (first_index + second_index) / 2;

		build_segment_tree(numbers, first_index, middle_index,
			left_son(current_canonical_segment_index),
			canonical_segments);

		build_segment_tree(numbers, middle_index + 1, second_index,
			right_son(current_canonical_segment_index),
			canonical_segments);

		T current_minimum = min(
			(*canonical_segments)[left_son(current_canonical_segment_index)].minimum,
			(*canonical_segments)[right_son(current_canonical_segment_index)].minimum);

        (*canonical_segments)[current_canonical_segment_index] =
			    element_of_segment_tree<T>(first_index, second_index, current_minimum);
	}

public:

	segment_tree()
	{ }

	explicit segment_tree(const vector<T>& numbers)
	{
		build_segment_tree(numbers, 0, static_cast<int>(numbers.size()) - 1,
		    0, &m_canonical_segments);
	}
	
private:

	static int left_son(int current_segment_index)
	{
		return 2 * current_segment_index + 1;
	}

	static int right_son(int current_segment_index)
	{
		return 2 * current_segment_index + 2;
	}

	//invariant: [left, right] in m_canonical_segments[canonical_segment_index]
	T get_segment_minimum(int left, int right,
		int canonical_segment_index) const
	{
		T segment_minimum;

  		if (m_canonical_segments[canonical_segment_index].first_index == left &&
			m_canonical_segments[canonical_segment_index].second_index == right)
  		{
			segment_minimum = m_canonical_segments[canonical_segment_index].minimum;
		}
		
		else if (right <=
			m_canonical_segments[left_son(canonical_segment_index)].second_index)
		{
			segment_minimum = get_segment_minimum(left, right,
				left_son(canonical_segment_index));
		}
		
        else if (left >=
			m_canonical_segments[right_son(canonical_segment_index)].first_index)
		{
			segment_minimum = get_segment_minimum(left, right,
				right_son(canonical_segment_index));
		}

		else
		{
            T left_minimum = get_segment_minimum(left,
				m_canonical_segments[left_son(canonical_segment_index)].second_index,
				left_son(canonical_segment_index));

			T right_minimum = get_segment_minimum(
				m_canonical_segments[right_son(canonical_segment_index)].first_index,
				right, right_son(canonical_segment_index));

			segment_minimum = min(left_minimum, right_minimum);
		}
		
		return segment_minimum;
	}

public:

	T get_segment_minimum(int left, int right) const
	{
		return get_segment_minimum(left, right, 0);
	}

};

////////////////////////////////////////////////////////////////////////////////

class tree
{
	struct son
	{
		int index;
		int distance_to_parent;

		son()
		{ }
		
		son(int n_index, int n_distance_to_parent):
			index(n_index), distance_to_parent(n_distance_to_parent)
		{ }
	};
	
	vector< vector<son> > m_sons_of_vertices;

 	void build_tree(const vector<edge>& edges,
		vector< vector<son> >* sons_of_vertices)
	{
		sons_of_vertices->resize(edges.size() + 1);
		
		for (int index = 0; index < edges.size(); ++index)
		{
			(*sons_of_vertices)[edges[index].parent - 1].push_back(
				son(edges[index].son - 1, edges[index].length));
  		}
 	}
	
public:

	tree()
	{ }

	explicit tree(const vector<edge>& edges)
	{
		build_tree(edges, &m_sons_of_vertices);
	}
	
	void print_tree() const
	{
		for (int vertice_index = 0; vertice_index < m_sons_of_vertices.size();
			++vertice_index)
		{
			cout << vertice_index << ": ";
			for (int son_number = 0;
				son_number < m_sons_of_vertices[vertice_index].size();
				++son_number)
			{
				cout <<
					m_sons_of_vertices[vertice_index][son_number].index
					<< "("
					<< m_sons_of_vertices[vertice_index][son_number].distance_to_parent
					<< ") ";
			}
			cout << endl;
		}
	}

private:

	bool is_leaf(int current_vertice) const
	{
		return m_sons_of_vertices[current_vertice].size() == 0;
	}

	void get_eular_tour(int current_root,
		vector<int>* eular_tour) const
	{
		eular_tour->push_back(current_root);

		for (int number_of_son = 0;
			number_of_son < m_sons_of_vertices[current_root].size();
			++number_of_son)
  		{
  	   		get_eular_tour(
				m_sons_of_vertices[current_root][number_of_son].index,
				eular_tour);

           	eular_tour->push_back(current_root);
  		}
	}

public:

	void get_eular_tour(vector<int>* eular_tour) const
	{
		eular_tour->clear();
		get_eular_tour(0, eular_tour);
	}
	
	void calculate_first_positions_in_eular_tour(
		const vector<int>& eular_tour,
		vector<int>* first_positions_in_eular_tour) const
 	{
		const int NO_POSITION = -1;
		
        first_positions_in_eular_tour->clear();
        first_positions_in_eular_tour->resize(
			m_sons_of_vertices.size(), NO_POSITION);

		for (int index = 0; index < eular_tour.size(); ++index)
		{
			if ((*first_positions_in_eular_tour)[eular_tour[index]] ==
				NO_POSITION)
   			{
                (*first_positions_in_eular_tour)[eular_tour[index]] = index;
			}
		}
	}
	
	int LCA(int first_vertice, int second_vertice,
		const segment_tree<int>& eular_tour_segment_tree,
		const vector<int>& first_positions_in_eular_tour) const
	{
		return eular_tour_segment_tree.get_segment_minimum(
			min(first_positions_in_eular_tour[first_vertice],
			first_positions_in_eular_tour[second_vertice]),
			max(first_positions_in_eular_tour[first_vertice],
			first_positions_in_eular_tour[second_vertice]));
	}
	
	long long distance_between_vertices(
		int first_vertice, int second_vertice,
		const segment_tree<int>& eular_tour_segment_tree,
		const vector<int>& first_positions_in_eular_tour,
		const vector<long long>& distances_to_root) const
 	{
		int lca_index = LCA(first_vertice, second_vertice,
			eular_tour_segment_tree, first_positions_in_eular_tour);

		return
			(distances_to_root[first_vertice] -
				distances_to_root[lca_index]) +
			(distances_to_root[second_vertice] -
				distances_to_root[lca_index]);
	}
			

private:

    void calculate_distances_to_root(
		int current_root, 
		long long current_distance_to_root,
	 	vector<long long>* distances_to_root) const
    {
		if (current_root == 0)
		{
			distances_to_root->resize(m_sons_of_vertices.size());
		}

		(*distances_to_root)[current_root] = current_distance_to_root;
		
		for (int number_of_son = 0;
			number_of_son < m_sons_of_vertices[current_root].size();
			++number_of_son)
  		{
  	   		calculate_distances_to_root(
				m_sons_of_vertices[current_root][number_of_son].index,
				current_distance_to_root +
					m_sons_of_vertices[current_root][number_of_son].distance_to_parent,
				distances_to_root);
        }
	}
public:

	void calculate_distances_to_root(vector<long long>* distances_to_root) const
	{
		calculate_distances_to_root(0, 0, distances_to_root);
	}

};


void process_sequence_of_quires(
	const vector<edge> edges,
	const vector< pair<int, int> > vertice_pairs,
	vector<long long>* distances)
{
	distances->clear();
	
    tree Tree(edges);
    
    vector<long long> distances_to_root;
    
    Tree.calculate_distances_to_root(&distances_to_root);
    
    vector<int> eular_tour;
    Tree.get_eular_tour(&eular_tour);
    
    vector<int> first_positions_in_eular_tour;
    
    Tree.calculate_first_positions_in_eular_tour(eular_tour,
		&first_positions_in_eular_tour);

	segment_tree<int> eular_tour_segment_tree(eular_tour);
    
    for (int index = 0; index < vertice_pairs.size(); ++index)
    {
        int first_vertice = vertice_pairs[index].first - 1;
        int second_vertice = vertice_pairs[index].second - 1;
    
    	long long current_distance =
			Tree.distance_between_vertices(first_vertice, second_vertice,
				eular_tour_segment_tree, first_positions_in_eular_tour,
				distances_to_root);
		distances->push_back(current_distance);
	}
}

void write_answer(ostream& out, const vector<long long>& distances)
{
	for (int index = 0; index < distances.size(); ++index)
	{
		out << distances[index] << endl;
	}
}

int main()
{
 	vector<edge> edges;
	vector< pair<int, int> > vertice_pairs;

	read_input_data(cin, &edges, &vertice_pairs);
	
	vector<long long> distances;
	
	process_sequence_of_quires(edges, vertice_pairs, &distances);

	write_answer(cout, distances);

	return 0;
}
