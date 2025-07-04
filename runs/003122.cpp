#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>



class element
{
 public:
	element** nears;
	int* nears_len;
	int nears_num;
	int id;
	element(int d,int len)
	{
		nears=new element*[len];
		nears_len=new int[len];
		nears_num=0;
		id=d;
	}
	void addNear(element*n,int l)
	{
		nears[nears_num]=n;
		nears_len[nears_num]=l;
		nears_num++;
	}
};

int finder(int a, int b,int len_from_a,element*current,element* last)
{
	int ans;
	if (current->id==b) return len_from_a;
	for(int i=0;i<current->nears_num;i++)
	{
		if(current->nears[i]==last) continue;
		ans=finder(a,b,len_from_a+current->nears_len[i],current->nears[i],current);
		if (ans>0) return ans;
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
	cin>>querry_len;
	for(i=0;i<querry_len;i++)
	{
		cin>>a>>b;
		c=finder(a,b,0,tree[a-1],tree[a-1]);
		cout<<c<<'\n';
	}
	


}