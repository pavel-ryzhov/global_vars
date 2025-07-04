#include <stdio.h>
#include <math.h>
#include <list>
#include <algorithm>

using namespace std;

// ----------------------------------- TreeNode

class TreeNode;
struct NodeLink;

struct NodeLink
{
	NodeLink(TreeNode* _node = NULL, int _weight = 0):
		node(_node),
		weight(_weight)
	{
	}
	
	TreeNode* node;
	int weight;	
};

class TreeNode
{
private:
	typedef list<NodeLink> ChildrenList;
	
	friend int FindLCAWeight(TreeNode* a, TreeNode* b);
	friend void MakeLink(TreeNode* a, TreeNode* b, int weight);

	int depth;
	NodeLink parents[16];
	ChildrenList children;   // stores links before the tree is hanged
	
public:
	TreeNode()
	{					
		depth = -1;
		for (int i = 0; i<16; ++i)
			parents[i] = NULL;
	}
	
	void Hang(int _depth = 0, TreeNode* parent = NULL)
	{
		depth = _depth;
		
		if (parent)
		{
			// find a parent, write it into parent[0], and remove it from children list
			for (ChildrenList::iterator i = children.begin(); i != children.end(); ++i)
				if ((*i).node == parent)
				{
					parents[0] = NodeLink(parent, (*i).weight);
					children.erase(i);
					break;
				}
			
		}
		else
			; // root node
		 		
		for (int i = 1; i<16; ++i)
		{
			int generation = 1 << i;
			if (parents[0].node)
			{
				NodeLink parentLink = parents[0].node->GetParent(generation-1);
				parents[i] = NodeLink(parentLink.node, parentLink.weight+parents[0].weight);
			}
			else
				parents[i] = NodeLink(NULL, 0);
		}
		
		for (ChildrenList::iterator i = children.begin(); i != children.end(); ++i)
			(*i).node->Hang(depth+1, this);
	}
	
	NodeLink GetParent(int generation)
	{
		if (generation == 0)
			return NodeLink(this, 0);
		else
		{
			int closest = floor(logf(generation)/logf(2));
			if (parents[closest].node)
			{
				NodeLink parentLink = parents[closest].node->GetParent(generation - (1 << closest));
				return NodeLink(parentLink.node, parentLink.weight + parents[closest].weight);
			}
			else
				return NodeLink(NULL, 0);
		}
	}
	
	bool CanBeRoot()
	{
		return children.size() == 1;
	}
	
};

// ------------------------------------------------------- LCA

void MakeLink(TreeNode* a, TreeNode* b, int weight)
{
	a->children.push_back(NodeLink(b, weight));
	b->children.push_back(NodeLink(a, weight));
}

int FindLCAWeight(TreeNode* a, TreeNode* b)
{  
	if (a->depth > b->depth) swap(a, b);
	
	NodeLink newHigherParent = b->GetParent(b->depth - a->depth);
	int heightDiff = newHigherParent.weight;
	b = newHigherParent.node;
	
	if (a == b) return heightDiff;
	
	int closest = 0;
	while (a->parents[closest+1].node != b->parents[closest+1].node)
		++closest;	
	
	return FindLCAWeight(a->parents[closest].node, b->parents[closest].node) + 
		a->parents[closest].weight + b->parents[closest].weight +
		heightDiff;
}

TreeNode* nodes;

//#include <conio.h>

int main()
{
	//freopen("input.txt", "r", stdin);

	// read nodes
	int N;
	scanf("%i\n", &N);
	nodes = new TreeNode[N];
	for (int i = 0; i<N-1; ++i)
	{
		int start, end, weight;
		scanf("%i %i %i\n", &start, &end, &weight);
		--start; --end;
		MakeLink(nodes+start, nodes+end, weight);
	}
	
	// find a node with one link and hang a tree on that node
	for (int i = 0; i<N; ++i)
		if (nodes[i].CanBeRoot())
		{
			nodes[i].Hang();
			break;
		}

	// execute queries
	int M; 
	
	scanf("%i\n", &M);
	for (int i = 0; i<M; ++i)
	{
		int start, end;
		scanf("%i %i\n", &start, &end);
		--start; --end;
		printf("%i\n", FindLCAWeight(nodes+start, nodes+end));
	}
	
	//getch();
	
	return 0;
}