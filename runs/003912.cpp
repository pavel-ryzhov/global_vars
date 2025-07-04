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
	int first_vertice;
	int second_vertice;
	int length;

	edge()
	{ }

	edge(int n_first_vertice, int n_second_vertice, int n_length):
		first_vertice(n_first_vertice), second_vertice(n_second_vertice),
		length(n_length)
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
		in >> (*edges)[index].first_vertice;
		in >> (*edges)[index].second_vertice;
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
class segment_tree
{
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

	vector <element_of_segment_tree> m_canonical_segments;

	void build_segment_tree(
		const vector<T>& numbers,
		int first_index, int second_index,
		int current_canonical_segment_index,
		vector <element_of_segment_tree>* canonical_segments)
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
			    element_of_segment_tree(first_index, second_index,
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
			    element_of_segment_tree(first_index, second_index, current_minimum);
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


class tree_graph
{
	struct vertice
	{
		int index;
		int depth;
		long long distance_to_root;
		vector<int> sons;
		
		vertice()
		{ }
		
		vertice(int n_index, int n_depth, long long n_distance_to_root):
			index(n_index), depth(n_depth), distance_to_root(n_distance_to_root)
		{ }
 	};

 	struct element_of_eular_tour
	{
		int vertice_index;
		int depth;
		
		element_of_eular_tour()
		{ }
		
		element_of_eular_tour(int n_vertice_index, int n_depth):
			vertice_index(n_vertice_index), depth(n_depth)
  		{ }
  		
  		bool operator < (const element_of_eular_tour& rhs) const
  		{
			return depth < rhs.depth;
		}
	};
	
////////////////////////////////////////////////////////////////////////////////

    vector<vertice> m_graph;
	vector<element_of_eular_tour> m_eular_tour;
	segment_tree<element_of_eular_tour> m_segment_tree_eular_tour;
	vector<int> m_first_positions_in_eular_tour;

////////////////////////////////////////////////////////////////////////////////

	struct neighbour
	{
		int index;
		int distance;

		neighbour()
        { }

        neighbour(int n_index, int n_distance):
			index(n_index), distance(n_distance)
        { }
	};

  	void get_all_neighbours(const vector<edge>& edges,
		vector< vector<neighbour> >* all_neighbours) const
	{
		all_neighbours->resize(edges.size() + 1);

		for (int index = 0; index < edges.size(); ++index)
		{
			(*all_neighbours)[edges[index].first_vertice - 1].push_back(
				neighbour(edges[index].second_vertice - 1, edges[index].length));

			(*all_neighbours)[edges[index].second_vertice - 1].push_back(
				neighbour(edges[index].first_vertice - 1, edges[index].length));
  		}
    }


	void traverse_tree(
		const vector< vector<neighbour> >& all_neighbours, int current_root,
		int current_depth, long long current_distance_to_root,
		vector<bool>* is_visited, vector<vertice>* graph)
  	{
		if (current_root == 0)
		{
            graph->resize(all_neighbours.size() + 1);
            is_visited->resize(all_neighbours.size() + 1, false);
		}

		(*graph)[current_root] =
			vertice(current_root, current_depth, current_distance_to_root);

		(*is_visited)[current_root] = true;

		for (int son_number = 0;
			son_number < all_neighbours[current_root].size(); ++son_number)
		{
            int current_vertice = all_neighbours[current_root][son_number].index;
            int edge_length = all_neighbours[current_root][son_number].distance;

			if ((*is_visited)[current_vertice] == false)
			{
                (*graph)[current_root].sons.push_back(current_vertice);

				traverse_tree(all_neighbours, current_vertice,
					current_depth + 1, current_distance_to_root + edge_length,
					is_visited, graph);
			}
		}
	}
	
	void get_eular_tour(int current_root, const vector<vertice>& graph,
		vector<element_of_eular_tour>* eular_tour)
	{
		eular_tour->push_back(element_of_eular_tour(graph[current_root].index,
			graph[current_root].depth));

		for (int number_of_son = 0;
			number_of_son < graph[current_root].sons.size();
			++number_of_son)
  		{
  	   		get_eular_tour(graph[current_root].sons[number_of_son], graph,
				eular_tour);

			eular_tour->push_back(
				element_of_eular_tour(m_graph[current_root].index,
				graph[current_root].depth));
 		}
	}
	
	void calculate_first_positions_in_eular_tour(const vector<vertice>& graph,
		const vector<element_of_eular_tour>& eular_tour,
		vector<int>* first_positions_in_eular_tour)
 	{
		const int NO_POSITION = -1;

        first_positions_in_eular_tour->clear();
        first_positions_in_eular_tour->resize(graph.size(), NO_POSITION);

		for (int position = 0; position < eular_tour.size(); ++position)
		{
			if ((*first_positions_in_eular_tour)
					[eular_tour[position].vertice_index] ==	NO_POSITION)
   			{
                (*first_positions_in_eular_tour)
					[eular_tour[position].vertice_index] = position;
			}
		}
	}

    void build_tree_graph(const vector<edge>& edges,
		vector<vertice>* graph,
		vector<element_of_eular_tour>* eular_tour,
		segment_tree<element_of_eular_tour>* segment_tree_eular_tour,
		vector<int>* first_positions_in_eular_tour)
 	{
        vector< vector<neighbour> > all_neighbours;
		get_all_neighbours(edges, &all_neighbours);
		
		vector<bool> is_visited;
		traverse_tree(all_neighbours, 0, 0, 0, &is_visited, graph);
		
		get_eular_tour(0, *graph, eular_tour);
		
		*segment_tree_eular_tour =
			segment_tree<element_of_eular_tour>(*eular_tour);
			
        calculate_first_positions_in_eular_tour(*graph, *eular_tour,
			first_positions_in_eular_tour);
	}

public:

    tree_graph()
    { }
    
    explicit tree_graph(const vector<edge>& edges)
    {
        build_tree_graph(edges, &m_graph, &m_eular_tour,
			&m_segment_tree_eular_tour, &m_first_positions_in_eular_tour);
	}

	int LCA(int first_vertice, int second_vertice) const
    {
		return m_segment_tree_eular_tour.get_segment_minimum(
			min(m_first_positions_in_eular_tour[first_vertice],
				m_first_positions_in_eular_tour[second_vertice]),
			max(m_first_positions_in_eular_tour[first_vertice],
				m_first_positions_in_eular_tour[second_vertice])).vertice_index;
	}

    long long distance_between_vertices(int first_vertice,
		int second_vertice) const
 	{
        int lca_index = LCA(first_vertice, second_vertice);

		return
			(m_graph[first_vertice].distance_to_root -
				m_graph[lca_index].distance_to_root) +
			(m_graph[second_vertice].distance_to_root -
				m_graph[lca_index].distance_to_root);
	}
	
};

void process_sequence_of_quires(const vector<edge> edges,
	const vector< pair<int, int> > vertice_pairs, vector<long long>* distances)
{
    distances->clear();
    
    tree_graph tree(edges);
    
    for (int index = 0; index < vertice_pairs.size(); ++index)
    {
        int first_vertice = vertice_pairs[index].first - 1;
        int second_vertice = vertice_pairs[index].second - 1;

    	long long distance = tree.distance_between_vertices(first_vertice,
			second_vertice);

		distances->push_back(distance);
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
