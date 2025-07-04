#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<vector<int> > graph;
int N;
class node 
{
public:	
	node* linkUp; // указатель на предка.
	int h; //глубина
	vector<int> ves; //вес связи к предку
	vector<node*> linkDown;
	int vesUp;
	node ()								{ves = vector<int>(0);linkDown=vector<node*>(0);}
	~node(){}
}; 

vector<node*> heads;
void create_tree(graph &g)
{
	for (unsigned i=0;i<g.size();i++)
	{
		node* p=heads[g[i][0]-1];
		if (!p)
		{
			p= new node();
			heads[g[i][0]-1]=p;
		}
		node* p2= heads[g[i][1]-1];
		if (!p2)
		{
			p2= new node();
			heads[g[i][1]-1]=p2;
		}
		p->linkDown.push_back(p2);
		p->ves.push_back(g[i][2]);
		p2->linkDown.push_back(p);
		p2->ves.push_back(g[i][2]);
	}
	
}
void setHeight(node* p, int h, node* up)
{
	p->h=h;
	p->linkUp=up;
	
	for (unsigned i=0; i<p->linkDown.size(); ++i)
	{
		if ((p->linkDown)[i]!=up)
		{
		setHeight(p->linkDown[i], h+1, p);
		} else 
		{
			p->vesUp=p->ves[i];
		}
	} 
} 
int height(int v1, int v2)
{
	int sum=0;
	node* p1 = heads[v1-1];
	node* p2 = heads[v2-1];
	while (p1->h>p2->h)
	{
		sum+=p1->vesUp;
		p1=p1->linkUp;
	} 
	while (p1->h<p2->h)
	{
		sum+=p2->vesUp;
		p2=p2->linkUp;
	}
	while( p1!=p2)
	{
		sum+=p1->vesUp;
		p1=p1->linkUp;
		sum+=p2->vesUp;
		p2=p2->linkUp;
	} 
	return sum;
}
int main()
{
	graph g;
	cin>>N;
	g=graph(N-1);
	for (int i=0;i<N-1;i++)
	{
		g[i]=vector<int>(3);
		cin>>g[i][0];
		cin>>g[i][1];
		cin>>g[i][2];	
	}
	heads.assign(N, (node*)0);
	if (g.size()>0) {
		create_tree(g);
		setHeight(heads[0],0,(node*)0);
	}
	int M;
	cin>>M;
	for (int i=0; i<M; i++)
	{
		int v1,v2;
		cin>>v1;
		cin>>v2;
		if (v1==v2) cout<<0<<endl;
		else 
		if (N>1)cout<<height(v1,v2)<<endl;
	}
	
	return 0;
}
