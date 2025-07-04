/* test with random generator */

#include <iostream>

#include <vector>

#include <deque>

#include <climits>

#include <cstdlib>

#include <cstdio>

#include <exception>

#include <cassert>

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

  void print_edges()
  {
    std::cout << "edges: ";
    for(  std::vector< edge >::iterator it = edges_.begin(); it < edges_.end(); ++it )
    {
      std::cout << it->get_node_addr() << ' ';
    }
    std::cout << std::endl;
  }

private:
  std::vector< edge > edges_;

  int dimension_;

  int number_;

  int ancestor_;

public:
  void set_ancestor( int value )
  {
    ancestor_ = value;
  }

  void set_dimension( int value )
  {
    dimension_ = value;
  }

  void set_number ( int value )
  {
    number_ = value;
  }

  int get_ancestor( ) const
  {
    return ancestor_;
  }

  int get_dimension( ) const
  {
    return dimension_;
  }

  int get_number ( ) const
  {
    return number_;
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

  void print_edges( )
  {
    std::cout << "edges:" << std::endl;
    for( std::vector< edge_info >::iterator it = edges_.begin();
      it < edges_.end(); ++it )
    {
      std::cout << it->node_begin << ' ' << it->node_end << std::endl;
    }
  }

protected:
  std::vector< edge_info > edges_;
  int number_of_nodes_;
  int number_of_edges_;
};


class Graph
{
public:
  void add_edge_to_node( int previous_node, int next_node, int edge_length );

  void build( GraphGenerator * generator  );

  const Node& operator[]( int node_number ) const
  {
    return nodes_.at(node_number);
  }

  Node& operator[]( int node_number )
  {
    return nodes_.at(node_number);
  }

  void print_graph()
  {
    std::vector< Node >::iterator it( nodes_.begin() );
    for( ; it < nodes_.end(); ++it)
    {
      std::cout << "wow, node!" << std::endl;
      it->print_edges();
    }
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



class Tree
{
public:
  Tree( )
  {
  }

  Tree( const Graph & graph ):
    nodes_( graph.get_nodes() )
  {
    root_ = 0;
    status_of_the_node_.resize( nodes_.size() );
    BuildTree( -1, root_, 0 );
  }

  void print_tree()
  {
    std::cout << "Tree: " << std::endl;
    std::vector< Node >::iterator it( nodes_.begin() );
    for( ; it < nodes_.end(); ++it)
    {
      std::cout << "node " << it->get_number() << " dim " << it->get_dimension() << "; ";
      std::cout << std::endl;
      it->print_edges();
    }
  }
    
  int LCA( int start, int finish )
  {
    int start_depth = nodes_.at(start).get_dimension();
    int finish_depth = nodes_.at(finish).get_dimension();

    int minimal_dim = 0;
    int delta = 0;

    //std::cout << "s " << start << " e " << finish << std::endl;
  
    while( start_depth != finish_depth )
    {
      if (start_depth > finish_depth)
      {
        int old_depth = start_depth;
        start = nodes_.at(start).get_ancestor();
        start_depth = nodes_.at(start).get_dimension();
        delta = old_depth - start_depth;
      }
      else
      {
        int old_depth = finish_depth;
        finish = nodes_.at(finish).get_ancestor();
        finish_depth = nodes_.at(finish).get_dimension();
        delta = old_depth - finish_depth;
      }

      minimal_dim += delta;
    }

    while( start != finish )
    {
      //std::cout << "s " << start << " e " << finish << std::endl;
      //std::cout << "sd " << nodes_.at(start).get_dimension() << " ed " << nodes_.at(finish).get_dimension() << std::endl;

      int old_depth = start_depth;

      if ( start == root_ || finish == root_ )
      {
        if ( start == root_ )
        {
          while ( start != finish )
          {
            finish = nodes_.at(finish).get_ancestor();
          }
        }
        if ( finish == root_ )
        {
          while ( start != finish )
          {
            start = nodes_.at(start).get_ancestor();
          }
        }
      }
      else
      {
        int finish_ancestor = nodes_.at(finish).get_ancestor();
        int start_ancestor = nodes_.at(start).get_ancestor();

        //std::cout << "s " << start << " e " << finish << std::endl;
        //std::cout << "s " << nodes_.at(start).get_dimension() << " e " << nodes_.at(finish).get_dimension() << std::endl;

        //null-length edge case
        while ( start != finish && 
          nodes_.at(finish).get_dimension() - nodes_.at(finish_ancestor).get_dimension() == 0 )
        {
          finish = nodes_.at(finish).get_ancestor();
        }
        while ( start != finish && 
          nodes_.at(start).get_dimension() - nodes_.at(start_ancestor).get_dimension() == 0 )
        {
          start = nodes_.at(start).get_ancestor();
        }

        if( start != finish )
        {
          start = nodes_.at(start).get_ancestor();
          finish = nodes_.at(finish).get_ancestor();
        }

        start_depth = nodes_.at(start).get_dimension();
        minimal_dim += 2 * (old_depth - start_depth);
      }        
    }

    return minimal_dim;
  }
    
  void BuildTree( int ancestor_number, int node_number, int length )
  {
    nodes_.at( node_number ).set_number( node_number ); // can be in the constructor

    nodes_.at( node_number ).set_ancestor( ancestor_number );

    if ( ancestor_number == - 1 )
    {
      nodes_.at(node_number).set_dimension( 0 );
    }
    else
    {
      int ancestor_depth = nodes_.at(ancestor_number).get_dimension();
      nodes_.at(node_number).set_dimension( ancestor_depth + length );
    }

    status_of_the_node_.at(node_number) = visited;

    const std::vector< edge > & edges = nodes_.at(node_number).get_transitions();
    std::vector< edge >::const_iterator edge_it = edges.begin();
    
    for ( ; edge_it < edges.end(); ++ edge_it )
    {
      int next_node = edge_it->get_node_addr();
      int length = edge_it->get_length();

      if ( status_of_the_node_[next_node] == not_visited )
      {
        BuildTree( node_number, next_node, length );
      }
    }

    status_of_the_node_[node_number] = fully_processed;
  }

private:
  int root_;

  std::vector< node_processing_type > status_of_the_node_;

  std::vector< Node > nodes_;
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



// "Relax" across edge to choose minimal way to next_node_index
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
int FindShortestPath( int source_number, int finish_number, Graph & graph )   // graph[number] or (*graph).[number], what's better?
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

void ProcessQueries( const GraphGenerator & graph_generator, Graph & graph, Tree & tree, std::vector< int > * answers  )    // may be Graph * graph
{
  int unsolved_pairs;
  std::cin >> unsolved_pairs;

  int start(0);
  int finish(0);
  for(int step = 0; step < unsolved_pairs; ++step)
  {
    GetStartFinish( graph_generator, start, finish );
  
    //answers->push_back( FindShortestPath( start, finish, graph ) );

    int result;
    result = tree.LCA( start, finish );

    //std::cout << result;

    answers->push_back( result );

    graph.clear();
  }
}


int main( )
{
  Graph graph;
  //RandomGenerator< 3, 3 > graph_generator; 
  StdInReader graph_generator;

  BuildGraph( &graph_generator, &graph );

  //graph.print_graph();

  Tree tree( graph );

  //tree.print_tree();

  std::vector< int > answers;

  ProcessQueries(graph_generator, graph, tree, &answers);

  std::vector< int >::const_iterator it = answers.begin();
  for( ; it < answers.end(); ++it)
  {
    std::cout << *it << std::endl;
  }

  getchar();
  getchar();

  return 0;
}


//11
//1 8 1
//2 8 9
//3 10 2
//4 8 1
//5 10 0
//6 10 3
//7 8 7
//8 10 3
//9 10 6
//11 8 8
//1
//6 5


//
//4 
//3 2 1
//2 3 5
//4 3 9


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