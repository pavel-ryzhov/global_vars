#include <stdio.h>
#include <math.h>
#include <list>

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
	typedef list<TreeNode*> ChildrenList;
	
	friend int FindLCAWeight(TreeNode* a, TreeNode* b);

	int depth;
	NodeLink parent[16];
	ChildrenList children;
	
public:
	TreeNode()
	{					
		depth = -1;
		for (int i = 0; i<16; ++i)
			parent[i] = NULL;
	}
	
	void AppendChild(TreeNode* node, int weight)
	{
		children.push_back(node);
		children.back()->parent[0] = NodeLink(this, weight);
	}
	
	void Hang(int _depth = 0)
	{
		depth = _depth;
		
		for (int i = 1; i<16; ++i)
		{
			int generation = 1 << i;
			if (parent[0].node)
			{
				NodeLink parentLink = parent[0].node->GetParent(generation-1);
				parent[i] = NodeLink(parentLink.node, parentLink.weight+parent[0].weight);
			}
			else
				parent[i] = NodeLink(NULL, 0);
		}
		
		for (ChildrenList::iterator i = children.begin(); i != children.end(); ++i)
			(*i)->Hang(depth+1);
	}
	
	NodeLink GetParent(int generation)
	{
		if (generation == 0)
			return NodeLink(this, 0);
		else
		{
			int closest = floor(logf(generation)/logf(2));
			if (parent[closest].node)
			{
				NodeLink parentLink = parent[closest].node->GetParent(generation - (1 << closest));
				return NodeLink(parentLink.node, parentLink.weight + parent[closest].weight);
			}
			else
				return NodeLink(NULL, 0);
		}
	}
	
};

int FindLCAWeight(TreeNode* a, TreeNode* b)
{  
	if (a->depth > b->depth) swap(a, b);
	
	NodeLink newHigherParent = b->GetParent(b->depth - a->depth);
	int heightDiff = newHigherParent.weight;
	b = newHigherParent.node;
	
	if (a == b) return heightDiff;
	
	int closest = 0;
	while (a->parent[closest+1].node != b->parent[closest+1].node)
		++closest;	
	
	return FindLCAWeight(a->parent[closest].node, b->parent[closest].node) + 
		a->parent[closest].weight + b->parent[closest].weight + heightDiff;
}

TreeNode* nodes;

int main()
{
	nodes = new TreeNode[40000];

	// read nodes
	int N;
	scanf("%i\n", &N);
	for (int i = 0; i<N-1; ++i)
	{
		int start, end, weight;
		scanf("%i %i %i\n", &start, &end, &weight);
		--start; --end;
		nodes[start].AppendChild(&nodes[end], weight);
	}
	
	// find a node with no parents and hand a tree on that node
	for (int i = 0; i<N; ++i)
		if (nodes[i].GetParent(1).node == NULL)
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
		printf("%i\n", FindLCAWeight(&nodes[start], &nodes[end]));
	}
	
	return 0;
}