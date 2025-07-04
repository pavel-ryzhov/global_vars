#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

class element_list;
class element;

class element_list
{
 public:
	element_list *next;
	element *current;
	element_list(element* cur)
	{
		next=NULL;
		current=cur;
	}
	void addElem(element *add)
	{
		if(next) next->addElem(add);
		else next=new element_list(add);
	}

};


class element
{
 public:
	element_list *nears;
	int* nears_len;
	int nears_num;
	int id;
	element(int d,int len)
	{
		nears=NULL;
		nears_len=new int[len];
		nears_num=0;
		id=d;
	}
	void addNear(element*n,int l)
	{
		if (nears_num==0) nears=new element_list(n);
		else nears->addElem(n);
		nears_len[nears_num]=l;
		nears_num++;
	}
	void print()
	{
		element_list*n;
		n=nears;
		printf("id=%d,nears_num=%d,nears:",id,nears_num);
		for(int i=0;i<nears_num;i++){printf(" id=%d ",n->current->id);n=n->next;}
		printf("\n");
	}
};





int finder(int a, int b,int len_from_a,element*current,element* last)
{
//printf("finder in %d,last %d",current->id,last->id);
	int ans;
	element_list* n;
	if (current->id==b) return len_from_a;
	if(current->nears) n=current->nears;
	for(int i=0;i<current->nears_num;i++)
	{
		if(n->current==last) {n=n->next;continue;}
//		printf("i=%d\n",i);
		ans=finder(a,b,len_from_a+current->nears_len[i],n->current,current);
		if (ans>0) return ans;
		n=n->next;
	}
	return 0;

}

using namespace std;

int main()
{
	int i,a,b,c;
	int tree_len,querry_len;
	cin>>tree_len;
	element **tree;
	tree=new element*[tree_len];
	for(i=0;i<tree_len;i++){tree[i]=new element(i+1,tree_len);}
	for(i=0;i<tree_len-1;i++)
	{
		cin>>a>>b>>c;
		tree[a-1]->addNear(tree[b-1],c);
		tree[b-1]->addNear(tree[a-1],c);
	}
//	for(i=0;i<tree_len;i++){tree[i]->print();}
	cin>>querry_len;
	for(i=0;i<querry_len;i++)
	{
		cin>>a>>b;
		c=finder(a,b,0,tree[a-1],tree[a-1]);
		cout<<c<<'\n';
	}
	


}