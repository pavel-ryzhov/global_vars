
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned short ushort;

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

			ushort usL;
			ushort usR;

			ushort usMin;

			BinaryNode(ushort usLeft, ushort usRight)
			{
				usL = usLeft;
				usR = usRight;

				pLeft  = NULL;
				pRight = NULL;
			}
		};

		typedef BinaryNode			 *PBinaryNode;

		static PBinaryNode			  pRoot;

		const static vector <ushort> &rNodesDepth;
		const static vector <ushort> &rNodesList;

		static void   p_makeTree       (ushort usLeft, ushort usRight, PBinaryNode *pBinaryNode)
		{
			*pBinaryNode = new BinaryNode(usLeft, usRight);

			if( usLeft == usRight )
				(*pBinaryNode)->usMin = rNodesList[usRight];
			else
			{
				ushort usAa = (usLeft + usRight) >> 1;

				p_makeTree(usLeft, usAa,    &(*pBinaryNode)->pLeft);
				p_makeTree(usAa+1, usRight, &(*pBinaryNode)->pRight);

				if( rNodesDepth[(*pBinaryNode)->pLeft->usMin-1] < rNodesDepth[(*pBinaryNode)->pRight->usMin-1] )
					(*pBinaryNode)->usMin = (*pBinaryNode)->pLeft->usMin;
				else
					(*pBinaryNode)->usMin = (*pBinaryNode)->pRight->usMin;
			}
		}

		static ushort p_getMinimalDepth(ushort usLeft, ushort usRight, const PBinaryNode pBinaryNode)
		{
			if( pBinaryNode->usL == usLeft && pBinaryNode->usR == usRight )
				return pBinaryNode->usMin;

			ushort usAa = (pBinaryNode->usL + pBinaryNode->usR) >> 1;

			if( usRight <= usAa )
				return p_getMinimalDepth(usLeft, usRight, pBinaryNode->pLeft);

			if( usLeft > usAa )
				return p_getMinimalDepth(usLeft, usRight, pBinaryNode->pRight);

			return (rNodesDepth[p_getMinimalDepth(usLeft, usAa,    pBinaryNode->pLeft)-1] < 
					rNodesDepth[p_getMinimalDepth(usAa+1, usRight, pBinaryNode->pRight)-1]) ?
					p_getMinimalDepth(usLeft, usAa,    pBinaryNode->pLeft) :
					p_getMinimalDepth(usAa+1, usRight, pBinaryNode->pRight);
		}
	public:
		static void   makeTree         (void)
		{
			p_makeTree(0, rNodesList.size()-1, &pRoot);
		}

		static ushort getMinimalDepth  (ushort usLeft, ushort usRight)
		{
			return p_getMinimalDepth(usLeft, usRight, pRoot);
		}
	};

	static vector <vector <pair <ushort, ushort> > > nodes;
	static vector <bool>						   nodesUsed;
	static vector <ushort>						   nodesDepth;
	static vector <ushort>						   nodesList;
	static vector <ushort>						   nodesIndex;

	static void   p_setNodesCount(ushort usNodesCount)
	{
		nodes.     resize(usNodesCount);
		nodesUsed. resize(usNodesCount, false);
		nodesDepth.resize(usNodesCount+1);

		nodesList. reserve(usNodesCount << 1);
	}

	static void   p_addEdge      (ushort usNodeBegin, ushort usNodeEnd, ushort usEdgeLength)
	{
		nodes[usNodeBegin-1].push_back(pair <ushort, ushort> (usNodeEnd, usEdgeLength));
	}

	static void   p_initialize   (void)
	{
		p_dfs(1, 0);

		BinaryTree::makeTree();
		nodesIndex.resize(nodes.size(), (ushort)-1);

		for ( ushort i = 0; i < nodesList.size(); ++i)
		{
			ushort usNode = nodesList[i];

			if ( nodesIndex[usNode-1] == (ushort)-1 )
				 nodesIndex[usNode-1] = i;
		}
	}

	static void   p_dfs			 (ushort usNode,      ushort usDepth)
	{
		nodesUsed [usNode-1] = true;
		nodesDepth[usNode-1] = usDepth;
		nodesList.push_back(usNode);

		for( ushort i = 0 ; i < nodes[usNode-1].size() ; ++i)
		{
			ushort nodeNext = nodes[usNode-1][i].first;

			if( !nodesUsed[nodeNext-1] )
			{
				p_dfs(nodeNext, usDepth + nodes[usNode-1][i].second);
				nodesList.push_back(usNode);
			}
		}
	}

	static ushort p_lca			 (ushort usNodeBegin, ushort usNodeEnd)
	{
		ushort usLeft  = nodesIndex[usNodeBegin-1];
		ushort usRight = nodesIndex[usNodeEnd-1];

		if ( usLeft > usRight )
			swap (usLeft, usRight);

		return BinaryTree::getMinimalDepth(usLeft, usRight);
	}
public:
	static void	  readFromStream (void)
	{
		ushort usNodesCount;
		ushort usEdgeLength;
		ushort usNodeBegin;
		ushort usNodeEnd;

		cin >> usNodesCount;

		p_setNodesCount(usNodesCount);

		while( --usNodesCount )
		{
			cin >> usNodeBegin >> usNodeEnd >> usEdgeLength;

			p_addEdge(usNodeBegin, usNodeEnd,   usEdgeLength);
			p_addEdge(usNodeEnd,   usNodeBegin, usEdgeLength);
		}

		p_initialize();
	}

	static ushort getMinimalPath (ushort usNodeBegin, ushort usNodeEnd)
	{
		int a = p_lca(usNodeBegin, usNodeEnd);
		
		return nodesDepth[usNodeBegin-1] + nodesDepth[usNodeEnd-1] - (nodesDepth[p_lca(usNodeBegin, usNodeEnd)-1] << 1);
	}
};

vector <vector <pair <ushort, ushort> > > Tree::nodes;
vector <bool>						      Tree::nodesUsed;
vector <ushort>							  Tree::nodesDepth;
vector <ushort>							  Tree::nodesList;
vector <ushort>							  Tree::nodesIndex;

Tree::BinaryTree::PBinaryNode             Tree::BinaryTree::pRoot;
const vector <ushort>				     &Tree::BinaryTree::rNodesDepth = Tree::nodesDepth;
const vector <ushort>				     &Tree::BinaryTree::rNodesList  = Tree::nodesList;

int main(void)
{
	ushort usPairsCount;
	ushort usNodeBegin;
	ushort usNodeEnd;
	
	Tree::readFromStream();

	cin >> usPairsCount;

	while( usPairsCount-- )
	{
		cin >> usNodeBegin >> usNodeEnd;
		cout << Tree::getMinimalPath(usNodeBegin, usNodeEnd);

		if( usPairsCount )
			cout << '\n';
	}

	return 0;
}