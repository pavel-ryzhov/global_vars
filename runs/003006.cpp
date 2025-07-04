
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long ulong;

class Tree
{
private:
	class BinaryTree
	{
	private:
		class BinaryNode
		{
		public:
			BinaryNode *pLeft;
			BinaryNode *pRight;

			ulong ulL;
			ulong ulR;

			ulong ulMin;

			BinaryNode(ulong ulLeft, ulong ulRight)
			{
				ulL = ulLeft;
				ulR = ulRight;

				pLeft  = NULL;
				pRight = NULL;
			}
		};

		typedef BinaryNode			*PBinaryNode;

		static PBinaryNode			 pRoot;

		const static vector <ulong> &rNodesDepth;
		const static vector <ulong> &rNodesList;

		static void   p_makeTree       (ulong ulLeft, ulong ulRight, PBinaryNode *pBinaryNode)
		{
			*pBinaryNode = new BinaryNode(ulLeft, ulRight);

			if( ulLeft == ulRight )
				(*pBinaryNode)->ulMin = rNodesList[ulRight];
			else
			{
				ulong ulAa = (ulLeft + ulRight) >> 1;

				p_makeTree(ulLeft, ulAa,    &(*pBinaryNode)->pLeft);
				p_makeTree(ulAa+1, ulRight, &(*pBinaryNode)->pRight);

				if( rNodesDepth[(*pBinaryNode)->pLeft->ulMin-1] < rNodesDepth[(*pBinaryNode)->pRight->ulMin-1] )
					(*pBinaryNode)->ulMin = (*pBinaryNode)->pLeft->ulMin;
				else
					(*pBinaryNode)->ulMin = (*pBinaryNode)->pRight->ulMin;
			}
		}

		static ulong  p_getMinimalDepth(ulong ulLeft, ulong ulRight, const PBinaryNode pBinaryNode)
		{
			if( pBinaryNode->ulL == ulLeft && pBinaryNode->ulR == ulRight )
				return pBinaryNode->ulMin;

			ulong ulAa = (pBinaryNode->ulL + pBinaryNode->ulR) >> 1;

			if( ulRight <= ulAa )
				return p_getMinimalDepth(ulLeft, ulRight, pBinaryNode->pLeft);

			if( ulLeft > ulAa )
				return p_getMinimalDepth(ulLeft, ulRight, pBinaryNode->pRight);

			return (rNodesDepth[p_getMinimalDepth(ulLeft, ulAa,    pBinaryNode->pLeft)-1] < 
					rNodesDepth[p_getMinimalDepth(ulAa+1, ulRight, pBinaryNode->pRight)-1]) ?
					p_getMinimalDepth(ulLeft, ulAa,    pBinaryNode->pLeft) :
					p_getMinimalDepth(ulAa+1, ulRight, pBinaryNode->pRight);
		}
	public:
		static void   makeTree         (void)
		{
			p_makeTree(0, rNodesList.size()-1, &pRoot);
		}

		static ulong  getMinimalDepth  (ulong ulLeft, ulong ulRight)
		{
			return p_getMinimalDepth(ulLeft, ulRight, pRoot);
		}
	};

	static vector <vector <pair <ulong, ulong> > > nodes;
	static vector <bool>						   nodesUsed;
	static vector <ulong>						   nodesDepth;
	static vector <ulong>						   nodesList;
	static vector <ulong>						   nodesIndex;

	static void   p_setNodesCount(ulong ulNodesCount)
	{
		nodes.     resize(ulNodesCount);
		nodesUsed. resize(ulNodesCount, false);
		nodesDepth.resize(ulNodesCount+1);

		nodesList. reserve(ulNodesCount << 1);
	}

	static void   p_addEdge      (ulong ulNodeBegin, ulong ulNodeEnd, ulong ulEdgeLength)
	{
		nodes[ulNodeBegin-1].push_back(pair <ulong, ulong> (ulNodeEnd, ulEdgeLength));
	}

	static void   p_initialize   (void)
	{
		p_dfs(1, 0);

		BinaryTree::makeTree();
		nodesIndex.resize(nodes.size(), (ulong)-1);

		for ( ulong i = 0; i < nodesList.size(); ++i)
		{
			ulong ulNode = nodesList[i];

			if ( nodesIndex[ulNode-1] == (ulong)-1 )
				 nodesIndex[ulNode-1] = i;
		}
	}

	static void   p_dfs			 (ulong ulNode,      ulong ulDepth)
	{
		nodesUsed [ulNode-1] = true;
		nodesDepth[ulNode-1] = ulDepth;
		nodesList.push_back(ulNode);

		for( ulong i = 0 ; i < nodes[ulNode-1].size() ; ++i)
		{
			ulong nodeNext = nodes[ulNode-1][i].first;

			if( !nodesUsed[nodeNext-1] )
			{
				p_dfs(nodeNext, ulDepth + nodes[ulNode-1][i].second);
				nodesList.push_back(ulNode);
			}
		}
	}

	static ulong p_lca			 (ulong ulNodeBegin, ulong ulNodeEnd)
	{
		ulong ulLeft  = nodesIndex[ulNodeBegin-1];
		ulong ulRight = nodesIndex[ulNodeEnd-1];

		if ( ulLeft > ulRight )
			swap (ulLeft, ulRight);

		return BinaryTree::getMinimalDepth(ulLeft, ulRight);
	}
public:
	static void	  readFromStream (void)
	{
		ulong ulNodesCount;
		ulong ulEdgeLength;
		ulong ulNodeBegin;
		ulong ulNodeEnd;

		cin >> ulNodesCount;

		p_setNodesCount(ulNodesCount);

		while( --ulNodesCount )
		{
			cin >> ulNodeBegin >> ulNodeEnd >> ulEdgeLength;

			p_addEdge(ulNodeBegin, ulNodeEnd,   ulEdgeLength);
			p_addEdge(ulNodeEnd,   ulNodeBegin, ulEdgeLength);
		}

		p_initialize();
	}

	static ulong  getMinimalPath (ulong ulNodeBegin, ulong ulNodeEnd)
	{
		int a = p_lca(ulNodeBegin, ulNodeEnd);
		
		return nodesDepth[ulNodeBegin-1] + nodesDepth[ulNodeEnd-1] - (nodesDepth[p_lca(ulNodeBegin, ulNodeEnd)-1] << 1);
	}
};

vector <vector <pair <ulong, ulong> > > Tree::nodes;
vector <bool>						    Tree::nodesUsed;
vector <ulong>							Tree::nodesDepth;
vector <ulong>							Tree::nodesList;
vector <ulong>							Tree::nodesIndex;

Tree::BinaryTree::PBinaryNode           Tree::BinaryTree::pRoot;
const vector <ulong>				   &Tree::BinaryTree::rNodesDepth = Tree::nodesDepth;
const vector <ulong>				   &Tree::BinaryTree::rNodesList  = Tree::nodesList;

int main(void)
{
	ulong ulPairsCount;
	ulong ulNodeBegin;
	ulong ulNodeEnd;
	
	Tree::readFromStream();

	cin >> ulPairsCount;

	while( ulPairsCount-- )
	{
		cin >> ulNodeBegin >> ulNodeEnd;
		cout << Tree::getMinimalPath(ulNodeBegin, ulNodeEnd);

		if( ulPairsCount )
			cout << '\n';
	}

	return 0;
}