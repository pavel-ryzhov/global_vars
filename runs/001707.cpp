#include <iostream>
#include <vector>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

const int YES   =  1;
const int NO    =  0;
const int EMPTY = -1;

void InputEdges(
    vector<vector<std::pair<int, int> > > * graph ) 
{
    int number_of_vertices;
    scanf( "%d", &number_of_vertices );
    graph->resize( number_of_vertices );

    for ( int edge_index = 0; edge_index < 
        number_of_vertices - 1; ++edge_index )
    {
        int from, to, distance;
        scanf( "%d%d%d", &from, &to, &distance );

        graph->at( from - 1 ).push_back( std::make_pair( to - 1, distance ));
        graph->at( to - 1 ).push_back( std::make_pair( from - 1, distance ));
    }
}

void InputRequests(
    vector<std::pair<int, int> > * requests ) 
{
    int number_of_requests;
    scanf( "%d", &number_of_requests );

    for ( int request_index = 0; request_index <
        number_of_requests; ++request_index ) 
    {
        int from, to;
        scanf( "%d%d", &from, &to );

        requests->push_back( std::make_pair( from, to ));
    }
}

void Input(
    vector<vector<std::pair<int, int> > > * graph,
    vector<std::pair<int, int> > * requests )
{
    InputEdges( graph );
    InputRequests( requests );
}

void CalculateLevelsAndDistances(
    int vertex_index,
    const vector<vector<std::pair<int, int> > > & graph,
    vector<int> & were_visited,
    vector<int> * levels,
    vector<int> * parents_in_a_tree,
    vector<int> * distances_to_the_root )
{
    for ( int adj_index = 0; adj_index < 
        (int)graph.at( vertex_index ).size(); ++adj_index ) 
    {
        const int & adj_vertex_index = graph.at( vertex_index ).at(
            adj_index ).first;
        const int & distance_to_adjacent = graph.at( vertex_index ).at(
            adj_index ).second;

        if ( were_visited.at( adj_vertex_index ) == NO ) {
            were_visited.at( adj_vertex_index ) = YES;

            levels->at( adj_vertex_index ) = levels->at( vertex_index ) + 1;
            parents_in_a_tree->at( adj_vertex_index ) = vertex_index;
            distances_to_the_root->at( adj_vertex_index ) = 
                distances_to_the_root->at( vertex_index ) + distance_to_adjacent;

            CalculateLevelsAndDistances( adj_vertex_index, graph, were_visited,
                levels, parents_in_a_tree, distances_to_the_root );
        }
    }
}

void PreprocessLevelsAndDistances( 
    const vector<vector<std::pair<int, int> > > & graph,
    vector<int> * levels,
    vector<int> * parents_in_a_tree,
    vector<int> * distances_to_the_root ) 
{
    levels->resize( graph.size());
    parents_in_a_tree->resize( graph.size());
    distances_to_the_root->resize( graph.size());

    levels->at( 0 ) = 0;
    parents_in_a_tree->at( 0 ) = EMPTY;
    distances_to_the_root->at( 0 ) = 0;

    vector<int> were_visited( graph.size(), NO );
    were_visited.at( 0 ) = YES;

    CalculateLevelsAndDistances( 
        0, graph, were_visited, levels, parents_in_a_tree, 
        distances_to_the_root );
}

void CalculateParentsInAStage(
    int vertex_index,
    int number_of_vertices_in_one_stage,
    const vector<vector<std::pair<int, int> > > & graph,
    const vector<int> & levels,
    const vector<int> & parents_in_a_tree,
    vector<int> & were_visited,
    vector<int> * parents_in_a_stage )
{
    if ( levels.at( vertex_index ) < number_of_vertices_in_one_stage ) {
        parents_in_a_stage->at( vertex_index ) = 0;
    } else {
        if ( !(levels.at( vertex_index ) % 
            number_of_vertices_in_one_stage )) 
        {
            parents_in_a_stage->at( vertex_index ) = 
                parents_in_a_tree.at( vertex_index );
        } else {
            parents_in_a_stage->at( vertex_index ) = 
                parents_in_a_stage->at( parents_in_a_tree.at( vertex_index ));
        }
    }

    for ( int adj_index = 0; adj_index < 
        (int)graph.at( vertex_index ).size(); ++adj_index ) 
    {
        const int & adj_vertex_index = graph.at( vertex_index ).at(
            adj_index ).first;

        if ( were_visited.at( adj_vertex_index ) == NO ) {
            were_visited.at( adj_vertex_index ) = YES;

            CalculateParentsInAStage( 
                adj_vertex_index, 
                number_of_vertices_in_one_stage,
                graph, 
                levels, 
                parents_in_a_tree, 
                were_visited,
                parents_in_a_stage );
        }
    }
}

//stages with size sqrt(N)
void PreprocessParentsInAStage(
    const vector<vector<std::pair<int, int> > > & graph,
    const vector<int> & levels,
    const vector<int> & parents_in_a_tree,
    vector<int> * parents_in_a_stage )
{
    parents_in_a_stage->resize( graph.size());

    int height_of_a_tree = *std::max_element( 
        levels.begin(), levels.end());

    int number_of_vertices_in_one_stage =
        (int)sqrt( static_cast<double>(height_of_a_tree));

    if ( !number_of_vertices_in_one_stage ) {
        number_of_vertices_in_one_stage = 1;
    }
    
    vector<int> were_visited( graph.size(), NO );
    were_visited.at( 0 ) = YES;

    CalculateParentsInAStage(
        0,
        number_of_vertices_in_one_stage,
        graph,
        levels,
        parents_in_a_tree,
        were_visited,
        parents_in_a_stage );
}

//LeastCommonAncestor Query ~ O(sqrt(N))
int LeastCommonAncestor(
    int vertex_A,
    int vertex_B,
    const vector<int> & levels,
    const vector<int> & parents_in_a_tree,
    const vector<int> & parents_in_a_stage )
{
    while ( parents_in_a_stage.at( vertex_A ) !=
        parents_in_a_stage.at( vertex_B )) 
    {
        if ( levels.at( vertex_A )  > 
            levels.at( vertex_B ))
        {
            vertex_A = parents_in_a_stage.at( vertex_A );
        } else {
            vertex_B = parents_in_a_stage.at( vertex_B );
        }
    }

    while ( vertex_A != vertex_B ) {
        if ( levels.at( vertex_A )  > 
            levels.at( vertex_B ))
        {
            vertex_A = parents_in_a_tree.at( vertex_A );
        } else {
            vertex_B = parents_in_a_tree.at( vertex_B );
        }
    }

    return vertex_A;
}

void Output( int min_distance_between_vertices ) {
    printf( "%d\n", min_distance_between_vertices );
}

int MinDistanceBetweenAandB(
    int vertex_A,
    int vertex_B,
    int vertex_LCA,
    const vector<int> & distances_to_the_root )
{
    return 
        abs( distances_to_the_root.at( vertex_A ) - 
            distances_to_the_root.at( vertex_LCA )) +  
        abs( distances_to_the_root.at( vertex_B ) - 
            distances_to_the_root.at( vertex_LCA ));
}

void ProcessRequests( 
    const vector<int> & levels,
    const vector<int> & parents_in_a_tree,
    const vector<int> & parents_in_a_stage,
    const vector<int> & distances_to_the_root,
    vector<std::pair<int, int> > & requests ) 
{
    for ( int request = 0; request < (int)requests.size(); ++request ) {

        int vertex_A = requests[ request ].first  - 1;
        int vertex_B = requests[ request ].second - 1;

        if ( vertex_A == vertex_B ) {
            //trivial case
            Output( 0 );
        } else {
            //getting LCA
            int vertex_LCA = LeastCommonAncestor( vertex_A,
                vertex_B, levels, parents_in_a_tree, parents_in_a_stage );
            
            //printing the distance( from A to LCA ) + 
            //distance( from B to LCA )
            Output( MinDistanceBetweenAandB( vertex_A, vertex_B,
                vertex_LCA, distances_to_the_root ));
        }
    }
}

int main() {
    //graph using adjacency vector
    //pair.first  - index of vertice
    //pair.second - distance to this vertice
    vector<vector<std::pair<int, int> > > graph;
    vector<std::pair<int, int> > requests;
	Input( &graph, &requests );
    
    vector<int> levels;
    vector<int> parents_in_a_tree;
    vector<int> distances_to_the_root;
    PreprocessLevelsAndDistances( 
        graph,
        &levels, 
        &parents_in_a_tree, 
        &distances_to_the_root );

    vector<int> parents_in_a_stage;
    PreprocessParentsInAStage(
        graph,
        levels,
        parents_in_a_tree,
        &parents_in_a_stage );

    ProcessRequests( 
        levels, 
        parents_in_a_tree, 
        parents_in_a_stage,
        distances_to_the_root, 
        requests );

	return 0;
}