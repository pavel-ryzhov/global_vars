#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>



class element
{
 public:
	element* father;
	int *prevs;
	int dep;
	int dep_len;
	int id;
	element(element* f,int d,int add_len)
	{
		id=d;
		father=f;
		dep=f->dep+1;
		prevs=new int[dep+1];
		for(int i=0;i<dep;i++)
		{
			prevs[i]=f->prevs[i];
		}
		prevs[dep]=id;
		dep_len=f->dep_len+add_len;
	}
	element(int d)
	{
		id=d;
		father=NULL;
		dep=0;
		prevs=new int[1];
		prevs[0]=id;
		dep_len=0;
	}
	void print(void)
	{
		printf("id=%d dep=%d dep_len=%d\n",id,dep,dep_len);
	}
};

int FindLen(element** tree, int a, int b)
{
	int *prevsa,*prevsb;
	int mindep,i=0;
	prevsa=tree[a-1]->prevs;
	prevsb=tree[b-1]->prevs;
	mindep= tree[a-1]->dep < tree[b-1]->dep ? tree[a-1]->dep : tree[b-1]->dep;
	for(i=0;i<mindep+1;i++)
	{
		if(prevsa[i]!=prevsb[i]) 
		{
			return tree[a-1]->dep_len + tree[b-1]->dep_len - 2*tree[prevsa[i-1]-1]->dep_len;
		}
//		printf("%d %d\n",mindep,prevsa[i]);
	}
//		printf("%d %d\n",i,prevsa[i-1]);
	return (tree[a-1]->dep < tree[b-1]->dep ? tree[b-1]->dep_len - tree[a-1]->dep_len : tree[a-1]->dep_len - tree[b-1]->dep_len);
}

using namespace std;

int main()
{
	int i,a,b,c;
	int tree_len,querry_len;
	cin>>tree_len;
	element **tree;
	tree=new element*[tree_len];
	cin>>a>>b>>c;
	tree[a-1]=new element(a);
	tree[b-1]=new element(tree[a-1],b,c);
	for(i=0;i<tree_len-2;i++)
	{
		cin>>a>>b>>c;
		tree[b-1]=new element(tree[a-1],b,c);
	}

	cin>>querry_len;
	for(i=0;i<querry_len;i++)
	{
		cin>>a>>b;
		c=FindLen(tree,a,b);
		cout<<c<<'\n';
	}
	


}