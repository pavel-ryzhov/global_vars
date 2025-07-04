
#include <stdio.h>
#include <vector>

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
			fprintf(stderr,"Node %u has not parent\n",id);
			depth=0;
		} else
			depth = tree[parentId].GetDepth()+1;
	}
	return depth;
}

int main(int argc,char **argv)
{
	int treeSz;
	scanf("%u",&treeSz);
	tree.resize(treeSz);
	int id=0;
	for (std::vector<TreeNode>::iterator i=tree.begin();i!=tree.end();i++,id++)
		i->id = id;
	tree[0].depth=0;
	for (int a=0;a<treeSz-1;a++) {
		int n1,n2,len;
		scanf("%u %u %u",&n1,&n2,&len);
		n1--;
		n2--;
		if (!tree[n2].SetParent(n1,len))
			if (!tree[n1].SetParent(n2,len))
				fprintf(stderr,"Nodes %u and %u already has a parent\n",n1,n2);
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
