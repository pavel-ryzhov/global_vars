// Problem B of Yandex lab entrance test
//
// (c) Andrei Anufriev, 2011.
//----------------------------------------------------------------------------
// Solution implemented:
// 
// Preparation: O(N) time
// Query answer: O(1)
// Memory: O(N log(n))
// using Farach-Colton, Bender algorithm
//----------------------------------------------------------------------------
// Hungarian notation agreements:
// n -- 1-based order numder
// id -- 0-based index in a vector
// l -- uint distance
// h -- height in a tree from root to this node
//----------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
//----------------------------------------------------------------------------
namespace p2
{
//----------------------------------------------------------------------------
// if there is no assert by compiller
#ifndef _ASSERT
// just none
#define _ASSERT(a) ;
#endif
//----------------------------------------------------------------------------
// global types

typedef unsigned int uint;				// for convenience

// N < 40 000 : 2 bytes (ushort) is enough
typedef unsigned short OrderNumber;		// 1-based; 0: stands for none; order number of a tree node/graph vertex
										// prefix: n

typedef unsigned int ID;				// 0-based, prefix: id

typedef unsigned int Distance;			// prefix: l

typedef unsigned int Height;			// prefix: h
//............................................................................
// represent a node of tree
struct TreeNode;

// linear collection of tree nodes
typedef std::vector<TreeNode *> VecPTreeNodes;

typedef std::pair<OrderNumber, Distance> NumLength;		// <order number, length>
typedef std::vector<NumLength> VecNumLen;

// represent a node of tree
struct TreeNode
{
public:
	// TODO: to save memory: move from here: temporary data
	VecNumLen Connections;				// node #, length
	// TODO: extract Connections to temporary struct

//	TreeNode * Parent;
	OrderNumber nParentNum;				// 1-based; pointer is in g_TreeNodes
	
	VecPTreeNodes childs;				// vector of pointers

	Distance lUpToRoot;					// calculated distance between this node and the root node

	Height hLevel;						// height of layer where this node is situated, 0: for root node, 1: for its childs, so on

	// release reserved memory of std::vector
	void inline Compactify()
	{
		;	// TODO: Not implemented
	}
};
//............................................................................
// a record in the input
// represents an edge of a graph
 struct anEdge
{
	OrderNumber nStart;					// graph endge starting vertex # ; 1-based, from the input
	OrderNumber nEnd;					// ending one
	Distance length;
	anEdge() {}
	anEdge(uint s, uint e, uint l)
		: 
		nStart(s),
		nEnd(e),
		length(l)
	{}
};

typedef std::vector<anEdge> VecEdges;

typedef std::vector<std::pair<OrderNumber, OrderNumber> > VecOfQueries;

typedef std::vector<int> VecInt;

typedef std::vector<uint> VecOfHash;

typedef std::vector<uint> VecOfUInt;
//----------------------------------------------------------------------------
// global variables

// TODO: use Singleton design pattern if construction order does matter

// all the input numbers
// 0 <= N <= 40 000

static uint g_NumberOfVertices = 0;			// graph of N vertices
static VecEdges g_arEdges;					// its edges

static uint g_NumberOfTargets = 0;			// M -- number of distances to calculate
static VecOfQueries g_Targets;				// <start, end>

static bool g_IsPreparationDone = false;	// preparation guard

static OrderNumber g_nRoot = 0;				// 0: is undefined here
static VecPTreeNodes g_TreeNodes;			// storage for all the tree nodes, needed for linear access by ID; 0-based

static std::vector<OrderNumber> g_Order;	// Order vector biult during DFS: deep first search, 
											// contains OrderNumber 1-based # of tree nodes traversed
											// and is used as a source array for LCA

static uint g_OrderSizeLog2 = 0;			// and logarith base 2 of its size; rounded up to integer
static uint g_OrderSizeSqrt = 0;			// and square root of its size; rounded up to integer

static std::vector<ID> g_First;				// vector of g_NumberOfVertices size; for each vertixe store ID in g_Order


static uint g_BlockSize = 0; 				// size of block inside g_Order
											// block size = 0.5 log A.size()

static uint g_NumberOfBlocks = 0;			// number of such blocks

// sparse table of in block minimums of g_Order
// TODO: rewrite to vector of vectors to save memory
// for now: just plain vector with access macro for two dimentions
// signed int: use -1 as unused indicator
// actually contains IDs : 0-based index in g_Order
static VecInt g_MinInBlocks;	

// its access macro
// usage: 
// g_MinInBlocks[B(X, Y)]
#define B(x, y) ((x) + ((y) * g_NumberOfBlocks) )

// хэши из 0 
// 1 : если высота больше, чем у предыдущей вершины

// storage for hash of every block for Farach-Colton, Bender algorithm
// 1bit if this node has hight larger then previous
// usage: 
// hash = g_HashOfBlock[idOfBlock] 
static VecOfHash g_HashOfBlock;

// storage for data for RMQ inside a block
// TODO: rewrite to vector<vector<vector> > > to save memory
// for now: just plain vector with access macro for three dimentions
// signed int: use -1 as unused indicator
// actually contains IDs : 0-based relative index inside block
static VecInt g_RmqDataForBlocks;
// its access macro
// usage: 
// g_RmqDataForBlocks[D(hash, Left, Right)]
#define D(hash, Left, Right) ((hash) * g_BlockSize * g_BlockSize + ((Left) * g_BlockSize) + (Right))

// for 40'000 limit: 80'000 max possible size of g_Order
// so 17 bit needed
// precalculated logarithms (floored values) : to avoid O(logN): and reach O(1)
VecOfUInt g_Log2Cache;
//----------------------------------------------------------------------------
static inline OrderNumber NFromId(ID anId)
{
	return anId + 1;
}
//----------------------------------------------------------------------------
static inline ID IdFromN(OrderNumber n)
{
	return n - 1;
}
//----------------------------------------------------------------------------
static inline TreeNode * NodeFromN(OrderNumber n)
{
	return g_TreeNodes[IdFromN(n)];
}
//----------------------------------------------------------------------------
static inline Height HeightFromN(OrderNumber n)
{
	return g_TreeNodes[IdFromN(n)]->hLevel;
}
//----------------------------------------------------------------------------
static inline Distance DistanceFromN(OrderNumber n)
{
	return g_TreeNodes[IdFromN(n)]->lUpToRoot;
}
//----------------------------------------------------------------------------
// read all the input data to global variables
static void ReadInput()
{
	std::cin >> g_NumberOfVertices;							// first line contains N

	uint start;
	uint end;
	uint length;
	uint NumberOfEdges = g_NumberOfVertices - 1;
	g_arEdges.reserve(NumberOfEdges);
	for (uint i = 0; i < NumberOfEdges; ++i)				// next N-1 lines (all the edges): #start #end length
	{
		std::cin >> start >> end >> length;
		g_arEdges.push_back(anEdge(start, end, length));	// TODO: rewrite to pointer to speedup, unless gcc 4.3.2 has moving constructors &&
	}

	std::cin >> g_NumberOfTargets;
	g_Targets.reserve(g_NumberOfTargets);
	for (uint i = 0; i < g_NumberOfTargets; ++i)			// next M lines: #start #end
	{
		std::cin >> start >> end;
		g_Targets.push_back(std::make_pair(start, end));
	}
}
//----------------------------------------------------------------------------
// determine root of the tree inputed
// set g_TreeRoot and g_nRoot to correct values
// TODO: to balance
// 
// for now just a node in the middle
static void DetermineRoot()
{
	g_nRoot = g_TreeNodes.size() / 2;
	if (g_nRoot < 1)	// handle case of 1 node tree
		g_nRoot = 1;
}
//----------------------------------------------------------------------------
// this function does two tasks
// 1) build interconnected tree from linear representation in g_TreeNodes
// 2) fill the Orders structure for LCA
// 
// O(N)
static void BiuldTreeNodeCilds(TreeNode * ThisNode, 
			OrderNumber nThisNum, 
			Height hThisLevel,
			OrderNumber nParentNum, 		// 1-based, 0 stands for none
			Distance DistanceOfThisToRoot)
{
	_ASSERT(ThisNode);

	// process this node
	ThisNode->lUpToRoot = DistanceOfThisToRoot;								// remember distance
	ThisNode->hLevel = hThisLevel;											// and level
	
	g_Order.push_back(nThisNum);											// add this node to Order

	// push to first; this statement will be executed only once for any node
	g_First[IdFromN(nThisNum)] = g_Order.size() - 1;						
	
	// create all the childs of this node
	for	(	VecNumLen::iterator connection = ThisNode->Connections.begin();	// for all the connections of this node
			ThisNode->Connections.end() != connection;
			++connection
		)
	{
		OrderNumber nChildNumber = (*connection).first;
		if (nChildNumber != nParentNum)										// if this is a child
		{
			uint lBetweenThisAndCurrentChild = (*connection).second;
			BiuldTreeNodeCilds(
				NodeFromN(nChildNumber), nChildNumber, 
				hThisLevel + 1,												// next level is +1 level
				nThisNum, 													// this node is parent for its childs
				DistanceOfThisToRoot + lBetweenThisAndCurrentChild
				);

			// and push this node to Order again during exit from a child
			g_Order.push_back(nThisNum);
		}
		// else this is parent node, already processed
	}
}
//----------------------------------------------------------------------------
// return base 2 logarithm of t rounded up to integer
// O(logN)
uint log2(uint t) 
{
	uint logValue = 0;
	while ( ((uint)1 << logValue) < t)  
		++logValue;
	return logValue;
}
//----------------------------------------------------------------------------
// return ID in g_Order with minimal height (close to the root of tree)
// n1, n2 : 0-based id of nodes in g_Order
static inline ID MinHeight(ID id1, ID id2)
{
	return 
		(HeightFromN(g_Order[id1]) < HeightFromN(g_Order[id2]) ) ?
		id1 : id2;
}
//----------------------------------------------------------------------------
// do all the preparations to ultimate query torrent
// O(N)
static void Prepare()
{
	if (!g_IsPreparationDone)
	{
		// create all the tree nodes
		// initialize g_First: fill the vector to enable random access
		g_TreeNodes.reserve(g_NumberOfVertices);
		g_First.reserve(g_NumberOfVertices);			
		for (uint k = 0; k < g_NumberOfVertices; ++k)	
		{
			g_TreeNodes.push_back(new TreeNode() );
		}
		g_First.assign(g_NumberOfVertices, 0);			// 0 stands for none

		// determine the root node
		DetermineRoot();								// g_TreeRoot is correct after this line

		// add relations to all the nodes		
		for (VecEdges::iterator edge = g_arEdges.begin(); 
			edge != g_arEdges.end();
			++edge
			)
		{
			// add relation between this two nodes

			// store length to cumulative calculate length
			anEdge & e = *edge;
			NodeFromN(e.nStart)->Connections.push_back( std::make_pair(e.nEnd, e.length) );
			NodeFromN(e.nEnd)->Connections.push_back( std::make_pair(e.nStart, e.length) );
		}

		// build tree starting from the root node
		TreeNode * pTreeRoot = NodeFromN(g_nRoot);
		pTreeRoot->nParentNum = 0;						// none
		
		pTreeRoot->lUpToRoot = 0;						// this is the root, distance = 0
		BiuldTreeNodeCilds(								// recursive procedure
			pTreeRoot, g_nRoot, 						// starting from the root node
			0, 											// root is in the 0 layer
			0, 											// 0: none; there is no parent for root node
			0											// distance between the root and root is 0
			);	
		
		g_OrderSizeLog2 = log2(g_Order.size());			// +1 : rounded up to integer
		g_OrderSizeSqrt = ((uint)std::sqrt((double)g_Order.size())) + 1; // rounded up

		g_BlockSize = (g_OrderSizeLog2 + 1) / 2;		// 0.5 log2 N

		if (g_BlockSize > 0)							// guard code against one-node tree and division by zero
		{
			g_NumberOfBlocks = 
				g_Order.size() / g_BlockSize + 
				(g_Order.size() % g_BlockSize ? 1 : 0);
		}

		// build saprse table: every cell is a min of a block
		// and calculate hashes and store to g_HashOfBlock

		// build the first line of sparse table: every cell is the minimum of corresponding block
		// and for every block: calculate hash of block
		uint SizeOfST = g_NumberOfBlocks * (g_OrderSizeLog2 + 1);	// X * Y
		g_MinInBlocks.reserve(SizeOfST);
		g_MinInBlocks.assign(SizeOfST, -1);
		
		g_HashOfBlock.reserve(g_NumberOfBlocks);
		g_HashOfBlock.assign(g_NumberOfBlocks, 0);

		uint idOfBlock = 0;
		uint idInsideBlock = 0;
		for (uint id = 0, 
			sz = g_Order.size(); id < sz; 				// for each entry in g_Order
			++id, ++idInsideBlock)
		{
			if (idInsideBlock >= g_BlockSize)			// if block is over
			{
				idInsideBlock = 0;						// start next block
				++idOfBlock;
			}

			// min inside block:
			if (g_MinInBlocks[B(idOfBlock, 0)] == -1)	// if there is no min for this block
			{
				g_MinInBlocks[B(idOfBlock, 0)] = id;	// set initial value of min() for this block
			}
			else
			{
				// if current entry of g_Order is less than min of this block
				if (MinHeight(id, g_MinInBlocks[B(idOfBlock, 0)]) == id)
				{
					g_MinInBlocks[B(idOfBlock, 0)] = id; // we have new min
				}					
			}

			// hash of block:
			if 	( idInsideBlock > 0 					// skip first entry of a block
				&& (MinHeight(id - 1, id) == (id -1) )	// and if curent node is far from the root than previous
				)
			{											// then in hash of this block set bit to 1
				g_HashOfBlock[idOfBlock] += 1 << (idInsideBlock - 1);
			}
		}

		// build the rest of sparse table based on the first line
		for (ID idY = 1; 								// from the second 
			idY <= g_OrderSizeLog2; 					// till the last line
			++idY
			)
		{
			for (ID idX = 0; idX < g_NumberOfBlocks; ++idX) 
			{
				ID idXEnd = 							// end of interval to accumulate
					idX + ( 1 << (idY - 1) );

				if (idXEnd >= g_NumberOfBlocks)			// if right edge of interval is exceeds size of line
				{										// there is no right cell to compare: use left cell
					g_MinInBlocks[B(idX, idY)] = g_MinInBlocks[B(idX, idY - 1)];
				}
				else
				{
					g_MinInBlocks[B(idX, idY)] = 		// it's enough to compare only two values of edges
						MinHeight(
							g_MinInBlocks[B(idX, idY - 1)], 
							g_MinInBlocks[B(idXEnd, idY - 1)]
						);
				}
			}
		}

		// compute data for RMQ inside block
		uint SizeOfInsideBlockTable = g_OrderSizeSqrt * g_BlockSize * g_BlockSize;
		g_RmqDataForBlocks.reserve(SizeOfInsideBlockTable);
		g_RmqDataForBlocks.assign(SizeOfInsideBlockTable, -1);
		
		// loop is through every of g_NumberOfBlocks block
		// but algorith granted unique number of hashes <= g_OrderSizeSqrt
		for ( ID idBlock = 0; idBlock < g_NumberOfBlocks; ++idBlock) // for each block
		{
			uint H = g_HashOfBlock[idBlock];			// for convenience
			if (-1 == g_RmqDataForBlocks[D(H, 0, 0)] )	// if block was not processed already
			{			
				for (ID L = 0; L < g_BlockSize; ++L)	// double loop over upper triangle
				{
					g_RmqDataForBlocks[D(H, L, L)] = L;	// for range 1: the only entry is min
					for (ID R = L + 1; R < g_BlockSize; ++R) // upper triangle
					{
						// set current as left cell of range
						g_RmqDataForBlocks[D(H, L, R)] = g_RmqDataForBlocks[D(H, L, R - 1)];
						
						// can exceed for the last block
						if ((idBlock * g_BlockSize + R) < g_Order.size()) // if does not exceed
						{
							g_RmqDataForBlocks[D(H, L, R)] =	// then fill upper triangle
																// relative id inside bock
								MinHeight(						// convert relative id (inside block) into absolute id in g_Order
									idBlock * g_BlockSize + g_RmqDataForBlocks[D(H, L, R)], 
									idBlock * g_BlockSize + R
									)
								- idBlock * g_BlockSize;		//convert back to relative
						}
					}
				}
			}
		}


		// store logarithm value up to g_Order.size
		g_Log2Cache.reserve(g_Order.size());
		uint CurrPower = 0;
		for (uint k=0, 
			sz = g_Order.size(); 
			k < sz; 									// for the whole length of list
			++k) 
		{
			if	( ((uint)1 << (CurrPower + 1) )				// +1 : floored value
					<= k
				)	
			{
				++CurrPower;							
			}
			g_Log2Cache.push_back(CurrPower);			// floored llogarithm: power of 2
		}
		
		g_IsPreparationDone = true;
	}
}
//----------------------------------------------------------------------------
// return ID in g_Order of LCA in block idBlock with range L to R
// ID idLeftInBlock, ID idRightInBlock : are relative inside this block
static inline ID LcaInBlock(ID idBlock, ID idLeftInBlock, ID idRightInBlock) 
{
	_ASSERT(0 <= (g_RmqDataForBlocks[D(g_HashOfBlock[idBlock] , idLeftInBlock, idRightInBlock)] + idBlock * g_BlockSize) );
	_ASSERT(g_Order.size() > (g_RmqDataForBlocks[D(g_HashOfBlock[idBlock] , idLeftInBlock, idRightInBlock)] + idBlock * g_BlockSize) );

	return g_RmqDataForBlocks[
		D(g_HashOfBlock[idBlock] , idLeftInBlock, idRightInBlock)
		] + idBlock * g_BlockSize;
}
//----------------------------------------------------------------------------
// for two tree nodes with order numbers n1 and n2
// return OrderNumber of node which is Lowest Common Ancestor for nodes given
// O(1)
static OrderNumber Lca(OrderNumber n1, OrderNumber n2)
{
	ID idL = g_First[IdFromN(n1)];	// get ID of first occurence in g_Orders
	ID idR = g_First[IdFromN(n2)];

	if (idL > idR)			// ensure left is on the left
	{	// swap
		ID tmp = idL;
		idL = idR;
		idR = tmp;
	}

	ID idLeftBlock;
	ID idRightBlock;
	if (g_BlockSize > 0)					// guard code against one-node tree and division by zero
	{
		idLeftBlock = idL / g_BlockSize;	// get IDs of blocks where given tree nodes resides
		idRightBlock = idR / g_BlockSize;
	}
	else
	{
		idLeftBlock = 0;
		idRightBlock = 0;
	}
	
	ID idLca = 0;						// id of LCA in g_Order
	if (idLeftBlock == idRightBlock)	// if both nodes are in the same block
	{
		idLca = 
			LcaInBlock( idLeftBlock, 	// id of this 
			idL % g_BlockSize, 			// relative id inside this block
			idR % g_BlockSize			// 
			);
	}
	else	// nodes in different blocks
	{
		// at least two blocks
		// get LCA inside these blocks
		ID idLcaInMostLeftBlock = LcaInBlock(idLeftBlock, idL % g_BlockSize, g_BlockSize - 1);
		ID idLcaInMostRightBlock = LcaInBlock(idRightBlock, 0, idR % g_BlockSize);
		idLca = MinHeight(idLcaInMostLeftBlock, idLcaInMostRightBlock);
		
		if (idLeftBlock < (idRightBlock - 1) ) 	// if nodes are not in adjacent blocks 
		{	// there are blocks between these two
			int pw2 = g_Log2Cache[idRightBlock - idLeftBlock - 1];		// logarithm for number of block in between

			// lookup minimum for all the block between at once
			// in the sparse table of minimums
			ID idLcaInRangeFromLeft = 			// from next to the most left block
				g_MinInBlocks[B(idLeftBlock + 1, pw2)];
										
			ID idLcaInRangeByRight = 			// by the right
				g_MinInBlocks[B(idRightBlock - (1<<pw2), pw2)];

			// minimum in the whole range from n1 to t2
			idLca = MinHeight(idLca, 
					MinHeight(idLcaInRangeFromLeft, idLcaInRangeByRight)
					);
		}
	}
	return g_Order[idLca];
}
//----------------------------------------------------------------------------
static void PrintDistance(Distance d)
{
	std::cout << d << std::endl;
}
//----------------------------------------------------------------------------
// just output 0 because there is no edge information
static void ProcessOneNodeTree()
{
	for (VecOfQueries::iterator it = g_Targets.begin(); g_Targets.end() != it; ++it)
	{
		PrintDistance(0);
	}
}
//----------------------------------------------------------------------------
static void ProcessTwoNodeTree()
{
	for (VecOfQueries::iterator it = g_Targets.begin(); g_Targets.end() != it; ++it)
	{
		uint lDistance = 0;
		if ((*it).first != (*it).second)
			lDistance = g_arEdges.front().length;	
		PrintDistance(lDistance);
	}
}
//----------------------------------------------------------------------------
// process all the special cases in a special way and do not use the main algorithm
// return true if this is a special case
static bool SpecialCase()
{
	if (g_NumberOfVertices <= 1)
	{
		ProcessOneNodeTree();
		return true;
	}
	if (g_NumberOfVertices <= 2)
	{
		ProcessTwoNodeTree();
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
// do the job
// calculate distance between given pairs of vertices
//
// O(N)
static void CalculateDistances()
{
	// process special cases first
	if (SpecialCase() )
		return;
	
	// create auxiliary data 
	Prepare();								// O(N)	
											
	
	// for each target: calculate distance
	for (VecOfQueries::iterator itQ = g_Targets.begin();
		itQ != g_Targets.end();
		++itQ
		)
	{
		OrderNumber n1 = (*itQ).first;
		OrderNumber n2 = (*itQ).second;
		Distance lBetween12 = 0;
		if (n1 != n2)
		{
			OrderNumber nCross = Lca(n1, n2);	// O(1)

			lBetween12 = 
				DistanceFromN(n1) - DistanceFromN(nCross)
				+
				DistanceFromN(n2) - DistanceFromN(nCross)
				;
		}
		PrintDistance(lBetween12);
	}
	
}
//----------------------------------------------------------------------------
// cleanup:
// release all the captured memory
//
// for the entrance test: not implemented due to economy of execution time, let's memory leaks
static void Cleanup()
{
	;	// TODO: not implemented
}
//----------------------------------------------------------------------------
}	// end of namespace p2
//----------------------------------------------------------------------------
int main(int argc, char * argv[])
{

	p2::ReadInput();			// read all the inputs
	p2::CalculateDistances();	// it outputs distances itself

	p2:: Cleanup();
	
	return 0;
}
//----------------------------------------------------------------------------

