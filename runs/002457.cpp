// 1. RMQ - range minimum query
// 2. number in brackets in comments before function where mentioned stands for time asymptotic
// 3. time asymptotic : buildTime ~ N*lgN , getDistance ~ 1
// 4. memory asymptotic ~ N*lgN
// 5. build time asymptotic could be reduced to ~N

#include <iostream>
#include <vector>
#include <list> 

using std::cin ; 
using std::cout ;
using std::vector ;
using std::pair ;
using std::list ;

class NlgN_RMQ_Table ;
class GraphWithEulerParh ;
struct Node ;

class NlgN_RMQ_Table{
public:
	//initialize ( N*lgN )
	void buildForVector( const vector< int > &sourceVector ) ;
	//Minimal Range Query in [ from , to ) ( 1 )
	int RMQ( int from , int to ) ;
private:
	//table [ N ][ lgN ] with evaluated answers
	vector< vector< int > > RMQs ;
	//we operate with indexes corresponding to this container
	vector< int > sourceVectorCopy ;

	// least int <= log( number )
	int intLog2( int number ) ;
	// 2^degree
	int degreeOf2( int degree ) ;
	// compares indexes according to elemnts they point to 
	int pickBestIndex( int index1 , int index2 ) ;
};

//node in tree_with_euler_path
struct Node{
	list< pair< int , int > > links ;
	int anyPosInEulerPath ;
};

//has definition of Euler path
class GraphWithEulerParh{
public:
	void getNodesFromCin() ;
	//build heighttsInEulerPath , distancesInEulerPath , table
	void buildEulerParh() ;
	//get distance between nodes given their indexes
	int getDistance( int node1Index , int node2Index ) ;
private:
	//recursive function for generating Euler path
	void addNodeToEulerPath( int prevNodeIndex , int nodeIndex , int distance , int height ) ;
	vector< Node > nodes ;
	//are used to find LCA and distance respectively
	vector< int > heightsInEulerPath , distancesInEulerPath ;
	//lookup table, builds time O( N*lgN ) , call time O( 1 )
	NlgN_RMQ_Table RMQTable ;
};

//-------------------------------------------------------------------------------

void NlgN_RMQ_Table::buildForVector( const vector< int > &sourceVector ){
	sourceVectorCopy = sourceVector ;
	RMQs.clear() ;
	int nLines = intLog2( ( int )sourceVector.size() ) + 1 ;
	RMQs.assign( nLines , vector< int >( sourceVector.size() , 0 ) ) ;

	//dinamic building
	for( int x = 0 ; x < ( int )sourceVectorCopy.size() ; ++x ){
		RMQs[ 0 ][ x ] = x ;
	};
	for( int line = 1 ; line < nLines ; ++line ){
		int blockLength = degreeOf2( line ) ;
		for( int x = 0 ; x <= ( int )sourceVectorCopy.size() - blockLength ; ++x ){
			RMQs[ line ][ x ] = pickBestIndex( RMQs[ line - 1 ][ x ] , RMQs[ line - 1 ][ x + blockLength / 2 ] ) ;
		};
	};
};
//
int NlgN_RMQ_Table::RMQ( int from , int to ){
	int length = to - from ;
	int tableLine = intLog2( length ) ;

	int leftHalfRMQ = RMQs[ tableLine ][ from ] ;
	int rightHalfRMQ = RMQs[ tableLine ][ to - degreeOf2( tableLine ) ] ;

	return pickBestIndex( leftHalfRMQ , rightHalfRMQ ) ;
};
//
int NlgN_RMQ_Table::intLog2( int number ){
	int result = -1 ;
	while( number > 0 ){
		result += 1 ;
		number >>= 1 ;
	};
	return result ;
};

//
int NlgN_RMQ_Table::degreeOf2( int degree ){
	int answer = 1 ;
	while( degree-- > 0 ){
		answer <<= 1 ;
	};
	return answer ;
};
//
int NlgN_RMQ_Table::pickBestIndex( int index1 , int index2 ){
	return ( sourceVectorCopy[ index1 ] < sourceVectorCopy[ index2 ] ) ? index1 : index2 ;
};
//

//-------------------------------------------------------------------------------

void GraphWithEulerParh::getNodesFromCin(){
	int nNodes ;
	cin >> nNodes ;
	nodes.assign( nNodes + 1 , Node() ) ;
	while ( --nNodes > 0 ){
		int from , to , length ;
		cin >> from >> to >> length ;// might add check if from, to are in [ 1 , size )
		nodes[ from ].links.push_back( pair< int , int >( length , to ) ) ;
		nodes[ to ].links.push_back( pair< int , int >( length , from ) ) ;
	};
};
//
void GraphWithEulerParh::buildEulerParh(){
	heightsInEulerPath.clear() ;
	distancesInEulerPath.clear() ;
	if ( nodes.size() < 2 ){
		return ;
	};
	//start the recursive process, from arbitrary node
	addNodeToEulerPath( -1 , 1 , 0 , 0 ) ;
	//index heights table to allow MQR
	RMQTable.buildForVector( heightsInEulerPath ) ;
};
//
int GraphWithEulerParh::getDistance( int node1Index , int node2Index ){
	//get any entries of these nodes
	int node1IndexInEulerPath = nodes[ node1Index ].anyPosInEulerPath ;
	int node2IndexInEulerPath = nodes[ node2Index ].anyPosInEulerPath ;
	//get any entrie of their LCA ensuring the first arg being less the the second
	int nodeLCAIndexInEulerPath ;
	if ( node1IndexInEulerPath <= node2IndexInEulerPath ){
		nodeLCAIndexInEulerPath = RMQTable.RMQ( node1IndexInEulerPath , node2IndexInEulerPath + 1 ) ;
	}else{
		nodeLCAIndexInEulerPath = RMQTable.RMQ( node2IndexInEulerPath , node1IndexInEulerPath + 1 ) ;
	};

	//get sum of distances from LCA to the nodes
	int node1Distance = distancesInEulerPath[ node1IndexInEulerPath ] ;
	int node2Distance = distancesInEulerPath[ node2IndexInEulerPath ] ;
	int nodeLCADistance = distancesInEulerPath[ nodeLCAIndexInEulerPath ] ;

	return ( - nodeLCADistance + node1Distance - nodeLCADistance + node2Distance ) ;
};
//
void GraphWithEulerParh::addNodeToEulerPath( int prevNodeIndex , int nodeIndex , int distance , int height ){
	//registrate the node
	nodes[ nodeIndex ].anyPosInEulerPath = ( int )heightsInEulerPath.size() ;
	heightsInEulerPath.push_back( height ) ;
	distancesInEulerPath.push_back( distance ) ;
	//applying this function to its neighbors excluding previous node
	for( list< pair< int , int > >::iterator linkIt = nodes[ nodeIndex ].links.begin() ; linkIt != nodes[ nodeIndex ].links.end() ; ++linkIt ){
		if ( linkIt->second == prevNodeIndex ){
			continue ;
		};
		addNodeToEulerPath( nodeIndex , linkIt->second , distance + linkIt->first , height + 1 ) ;
		heightsInEulerPath.push_back( height ) ;
		distancesInEulerPath.push_back( distance ) ;
	};
};
//

//-------------------------------------------------------------------------------

int main(){
	GraphWithEulerParh graph ;
	graph.getNodesFromCin() ;
	graph.buildEulerParh() ;

	int nQuestions ;
	cin >> nQuestions ;
	list< int > answers ;
	for ( ; nQuestions > 0 ; --nQuestions ){
		int node1Index , node2Index ;
		cin >> node1Index >> node2Index ; // we might check if indexes are in [ 1 ; size )
		answers.push_front( graph.getDistance( node1Index , node2Index ) ) ;
	};

	while( answers.empty() == false ){
		cout << answers.back() << "\n" ;
		answers.pop_back() ;
	};

	return 0;
};


