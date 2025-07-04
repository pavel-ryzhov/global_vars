
#include <stdio.h>
#include <vector>
#include <set>

class TreeNode
{
public:
	TreeNode()
	:id(-1),parentId(-1),parentLen(0),depth(-1)
	{
	}
	~TreeNode()
	{
	}

	int id;
	int parentId;
	int parentLen;
	int depth;
	bool SetParent(int parent,int len);
	int GetDepth();
};

std::vector<TreeNode> tree;

bool TreeNode::SetParent(int parent,int len)
{
	if (parentId!=-1 || id==0) {
		return false;
	}
	parentId = parent;
	parentLen = len;
	int d;
	if ((d=tree[parentId].depth)!=-1) depth = d+1;
	return true;
}

int TreeNode::GetDepth()
{
	if (depth==-1) {
		if (parentId==-1) {
			fprintf(stderr,"Node %u has not parent\n",id+1);
			depth=0;
		} else
			depth = tree[parentId].GetDepth()+1;
	}
	return depth;
}

struct TreeEdge
{
	int n1,n2,len;
	bool processed;
};

int main(int argc,char **argv)
{
	int treeSz;
	scanf("%u",&treeSz);
	tree.resize(treeSz);
	int id=0;
	for (std::vector<TreeNode>::iterator i=tree.begin();i!=tree.end();i++,id++)
		i->id = id;
	tree[0].depth=0;
	std::vector<TreeEdge> edges;
	for (int a=0;a<treeSz-1;a++) {
		TreeEdge e;
		scanf("%u %u %u",&e.n1,&e.n2,&e.len);
		e.processed = false;
		e.n1--;
		e.n2--;
		edges.insert(edges.end(),e);
	}
	std::set<int> connectedNodes;
	connectedNodes.insert(0);
	int processedEdges=0;
	int prevProcessedEdges=0;
	while (processedEdges<edges.size()) {
		prevProcessedEdges = processedEdges;
		for (std::vector<TreeEdge>::iterator i=edges.begin();i!=edges.end();i++) {
			if (i->processed) continue;
			int n1,n2;
			if (connectedNodes.find(i->n1)!=connectedNodes.end()) {
				n1=i->n1;
				n2=i->n2;
			} else if (connectedNodes.find(i->n2)!=connectedNodes.end()) {
				n1=i->n2;
				n2=i->n1;
			} else continue;
			if (!tree[n2].SetParent(n1,i->len))
				fprintf(stderr,"Node %u already has a parent\n",n2+1);
			connectedNodes.insert(n2);
			i->processed = true;
			processedEdges++;
		}
		if (prevProcessedEdges==processedEdges) {
			for (std::vector<TreeEdge>::iterator i=edges.begin();i!=edges.end();i++) {
				if (i->processed) continue;
				fprintf(stderr,"Selected node %u as new root\n",i->n1+1);
				connectedNodes.insert(i->n1);
			}
		}
	}
	int queryCnt;
	scanf("%u",&queryCnt);
	for (int a=0;a<queryCnt;a++) {
		int n1,n2;
		scanf("%u %u",&n1,&n2);
		n1--;
		n2--;
		int d1=tree[n1].GetDepth();
		int d2=tree[n2].GetDepth();
		if (d1<d2) {
			std::swap(n1,n2);
			std::swap(d1,d2);
		}
		int len1=0;
		int len2=0;
		while (d1>d2) {
			len1+=tree[n1].parentLen;
			n1=tree[n1].parentId;
			d1=tree[n1].GetDepth();
		}
		while (n1!=n2) {
			len1+=tree[n1].parentLen;
			n1=tree[n1].parentId;
			len2+=tree[n2].parentLen;
			n2=tree[n2].parentId;
		}
		printf("%u\n",len1+len2);
	}
	return 0;
}
