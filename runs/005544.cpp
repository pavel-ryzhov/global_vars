/* test with random generator */

#include <iostream>

#include <vector>

#include <deque>

#include <climits>

#include <cstdlib>

#include <cstdio>

#include <algorithm>

int const MagicSeedConstant = 1147;


using std::min;


enum node_processing_type
{
  not_visited,    //each Node in the beginning
  visited,
  fully_processed
};


struct edge_info
{
  int node_begin, node_end;
  int length;
};


class edge
{
public:
  edge( int index, int length ):
    node_index_( index ),
    length_( length )
  {
  }

private:
  int node_index_;

  int length_;

public:
  int get_node_addr( ) const
  {
    return node_index_;
  }

  int get_length( ) const
  {
    return length_;
  }
};


class Node
{
public:
  Node( ):
    dimension_( -1 )
  {
  }

  void make_transition( int node_number, int length )
  {
    edges_.push_back( edge( node_number, length ) );
  }

  const std::vector< edge >& get_transitions( ) const
  {
    return edges_;
  }

private:
  std::vector< edge > edges_;

  int dimension_;

public:
  void set_dimension( int value )
  {
    dimension_ = value;
  }

  int get_dimension( ) const
  {
    return dimension_;
  }

};


class BaseGraphGenerator
{
public:
  virtual const std::vector< edge_info >& build_edges( ) = 0;

  virtual int generate_start_number( ) const = 0;
  virtual int generate_finish_number( ) const = 0;

  virtual ~BaseGraphGenerator( ) { };
};

class GraphGenerator : public BaseGraphGenerator
{
public:
  GraphGenerator( )
  {
  }

  GraphGenerator( int nodes, int edges ):
    number_of_nodes_( nodes ),
    number_of_edges_( edges )
  {
  }

  int get_number_of_nodes( ) const;
  int get_number_of_edges( ) const;

protected:
  std::vector< edge_info > edges_;
  int number_of_nodes_;
  int number_of_edges_;
};


class Graph
{
  void add_edge_to_node( int previous_node, int next_node, int edge_length );

public:
  void build( GraphGenerator * generator  );

  const Node& operator[]( int node_number ) const
  {
    return nodes_[node_number];
  }

  Node& operator[]( int node_number )
  {
    return nodes_[node_number];
  }

  void clear()
  {
    std::vector< Node >::iterator it( nodes_.begin() );
    for( ; it < nodes_.end(); ++it)
    {
      it->set_dimension( -1 );
    }
  }

private:
  std::vector< Node > nodes_;

public:
  const std::vector< Node >& get_nodes( ) const
  {
    return nodes_;
  }

  int get_number_of_nodes( ) const
  {
    return nodes_.size();
  }
};



void Graph::add_edge_to_node( int previous_node, int next_node, int edge_length )
{
  nodes_[previous_node].make_transition( next_node, edge_length );
  nodes_[next_node].make_transition( previous_node, edge_length );
}

void Graph::build( GraphGenerator * generator )   // think about making "&generator": delete vars in gen
{
  int number_of_nodes = generator->get_number_of_nodes();
  int number_of_edges = generator->get_number_of_edges();
  const std::vector< edge_info >& edges = generator->build_edges( );

  nodes_.resize( number_of_nodes );

  for ( int index( 0 ); index < number_of_edges; ++index )
  {
    add_edge_to_node( edges[index].node_begin - 1, edges[index].node_end - 1, edges[index].length );
  }
}


class StdInReader : public GraphGenerator
{
public:
  StdInReader( )
  {
    //std::cout << "nodes edges" << std::endl;
    std::cin >> number_of_nodes_;
    number_of_edges_ = number_of_nodes_ - 1;
  }

  const std::vector< edge_info >& build_edges( );

  int generate_start_number( ) const;
  int generate_finish_number( ) const;

  ~StdInReader( )
  {
  }
};

template< int n, int m >
class RandomGenerator : public GraphGenerator
{
public:
  RandomGenerator( ):
    GraphGenerator( n, m )
  {
    srand( MagicSeedConstant );
  }

  const std::vector< edge_info >& build_edges( );

  int generate_start_number( ) const;
  int generate_finish_number( ) const;

  ~RandomGenerator( )
  {
  }
};



int GraphGenerator::get_number_of_nodes( ) const
{
  return number_of_nodes_;
}

int GraphGenerator::get_number_of_edges( ) const
{
  return number_of_edges_;
}

int StdInReader::generate_start_number( ) const
{
  int start_number;
  //std::cout << "start finish" << std::endl;
  std::cin >> start_number;
  return start_number - 1;
}

int StdInReader::generate_finish_number( ) const
{
  int finish_number;
  std::cin >> finish_number;
  return finish_number - 1;
}

const std::vector< edge_info >& StdInReader::build_edges( )
{
  //std::cout << "node_begin node_end node_len" << std::endl;
  edges_.resize( number_of_edges_ );
  for ( int index( 0 ); index < number_of_edges_; ++index )
  {
    std::cin >> edges_[index].node_begin >> edges_[index].node_end
      >> edges_[index].length;
  }

  return edges_;
}

template< int n, int m >
int RandomGenerator< n, m >::generate_start_number( ) const
{
  std::cout << "start: ";
  int start_number = rand() % number_of_nodes_ + 1;
  std::cout << start_number << std::endl;

  return start_number - 1;
}

template< int n, int m >
int RandomGenerator< n, m >::generate_finish_number( ) const
{
  std::cout << "finish: ";
  int finish_number = rand() % number_of_nodes_ + 1;
  std::cout << finish_number << std::endl;

  std::cout << std::endl;
  return finish_number - 1;
}

template< int n, int m >
const std::vector< edge_info >& RandomGenerator< n, m >::build_edges( )
{
  edges_.resize( number_of_edges_ );
  for ( int i = 0; i < number_of_edges_; ++i )
  {
    edges_[i].node_begin = rand() % number_of_nodes_ + 1;
    std::cout << edges_[i].node_begin << " <-> ";
    edges_[i].node_end = ( rand() % ( number_of_nodes_ - edges_[i].node_begin + 1 ) ) + edges_[i].node_begin;
    std::cout << edges_[i].node_end << " : ";
    edges_[i].length = rand() % 2;
    std::cout << edges_[i].length << std::endl;
  }

  return edges_;
}



// ... bypass graph, marking visited nodes
void Relax( const int node_index, const edge& node_edge, const int next_node_index,
  std::deque< int >* indexes_of_visited_nodes, Graph* graph )
{
  if ( ( *graph )[next_node_index].get_dimension() == -1 ) 
  {
    ( *graph )[next_node_index].set_dimension(
      ( *graph )[node_index].get_dimension() + node_edge.get_length() );
  }
  else
  {
    ( *graph )[next_node_index].set_dimension(
      min(
        ( *graph )[next_node_index].get_dimension(),
        ( *graph )[node_index].get_dimension() + node_edge.get_length() ) );
  }

  if ( node_edge.get_length() == 0 )
  {
    indexes_of_visited_nodes->push_front( node_edge.get_node_addr() );
  }
  else
  {
    indexes_of_visited_nodes->push_back( node_edge.get_node_addr() );
  }
}


// Finds a shortest way in the graph,
// returns -1 if there is no way
int CalculateShortestWay( int source_number, int finish_number, Graph & graph )   // graph[number] or (*graph).[number]
{
  graph[source_number].set_dimension( 0 );

  std::vector< node_processing_type > status_of_the_node;

  status_of_the_node.resize( graph.get_number_of_nodes() );

  std::deque< int > indexes_of_visited_nodes;

  indexes_of_visited_nodes.push_front( source_number );

  while ( !indexes_of_visited_nodes.empty() )
  {
    int node_with_minimal_dimension = indexes_of_visited_nodes.front();
    indexes_of_visited_nodes.pop_front();

    status_of_the_node[node_with_minimal_dimension] = fully_processed;

    const std::vector< edge >& edges = graph[node_with_minimal_dimension].get_transitions();

    for ( std::vector< edge >::const_iterator edge_it = edges.begin();
      edge_it != edges.end(); ++edge_it )
    {
      int next_node = edge_it->get_node_addr();
      if ( status_of_the_node[next_node] != fully_processed )
      {
        Relax( node_with_minimal_dimension, *edge_it, edge_it->get_node_addr(),
          &indexes_of_visited_nodes, &graph );
      }
    }
  }

  return graph[finish_number].get_dimension( );
}


void BuildGraph( GraphGenerator * generator, Graph * graph )
{
  graph->build( generator );
}


void GetStartFinish( const GraphGenerator & graph_generator, int & start, int & finish )
{
  start = graph_generator.generate_start_number();
  finish = graph_generator.generate_finish_number();
}

void ProcessQueries( const GraphGenerator & graph_generator, Graph & graph, std::vector< int > * answers  )    // may be Graph * graph
{
  int unsolved_pairs;
  std::cin >> unsolved_pairs;

  //std::cout << '\n';
  int start, finish;
  for(int step = 0; step < unsolved_pairs; ++step)
  {
    GetStartFinish( graph_generator, start, finish );
  
    answers->push_back( CalculateShortestWay( start, finish, graph ) );

    graph.clear();
  }
}

int main( )
{
  Graph graph;
  //RandomGenerator< 3, 3 > graph_generator; 
  StdInReader graph_generator;

  BuildGraph( &graph_generator, &graph );

  std::vector< int > answers;
  ProcessQueries(graph_generator, graph, &answers);

  std::vector< int >::const_iterator it = answers.begin();
  for( ; it < answers.end(); ++it)
  {
    std::cout << *it << std::endl;
  }

  getchar();
  getchar();

  return 0;
}


//start: 1
//finish: 3
//
//4 <-> 4 : 0
//1 <-> 3 : 1
//1 <-> 3 : 1
//3 <-> 4 : 1
//4 <-> 4 : 1
//
//1



/* debugging

magic seed is 1147
RandomGenerator< 16, 19 >
...
start: 9
finish: 11

generated edges:
4 <-> 16 : 0
13 <-> 15 : 1
13 <-> 15 : 1
15 <-> 16 : 1
4 <-> 7 : 1
2 <-> 12 : 0
1 <-> 16 : 0
2 <-> 13 : 1
10 <-> 12 : 1
13 <-> 14 : 1
8 <-> 9 : 0
10 <-> 16 : 1
12 <-> 12 : 0
5 <-> 15 : 1
1 <-> 1 : 0
2 <-> 2 : 1
10 <-> 12 : 0
16 <-> 16 : 0
3 <-> 9 : 1

answer:
-1
*/