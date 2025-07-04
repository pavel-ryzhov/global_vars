#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<vector<int> > graph;
int N;
class node 
{
	int ves; //вес связи к предку
	node* linkUp; // указатель на предка.
	int he; //глубина
	vector<node*> linksDown;
	
public:
	node ()								{linkUp=0;linksDown=vector<node*>(0);}
	node(int v, node* up=0)				{ ves=v; linkUp=up; linksDown=vector<node*>(0);}
	void setLinkUp(node* n)				{ linkUp=n;}
	node* getLinkUp()					{return linkUp;}
	void setLinkDown(vector<node*> n)	{linksDown=n;}
	vector<node*>* getLinkDown()		{return &linksDown;}
	int getH() const					{return he;}
	void setH(int h)					{he=h;}
	int getVes() const					{return ves;}
	void setVes(int i)					{ ves=i;}
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
			p= new node(0,0);
			heads[g[i][0]-1]=p;
		}
		node* p2= heads[g[i][1]-1];
		if (!p2)
		{
			p2= new node(g[i][2], p);
			heads[g[i][1]-1]=p2;
		} else
		{
			p2->setVes(g[i][2]);
			p2->setLinkUp(p);
		}
		(p->getLinkDown())->push_back(p2);
	}
	
}
node* getroot(int i)
{
	node* p=heads[i];
	while (p->getLinkUp())
	{
		p=p->getLinkUp();
	}
	return p;
}
void setHeight(node* root, int h)
{
	root->setH(h);
	vector<node*> *l=root->getLinkDown();
	for (unsigned i=0; i<l->size(); ++i)
	{
		setHeight((*l)[i], h+1);
	} 
} 
int height(int v1, int v2)
{
	int sum=0;
	node* p1 = heads[v1-1];
	node* p2 = heads[v2-1];
	while (p1->getH()>p2->getH())
	{
		sum+=p1->getVes();
		p1=p1->getLinkUp();
	} 
	while (p1->getH()<p2->getH())
	{
		sum+=p2->getVes();
		p2=p2->getLinkUp();
	}
	while( p1!=p2)
	{
		sum+=p1->getVes();
		p1=p1->getLinkUp();
		sum+=p2->getVes();
		p2=p2->getLinkUp();
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
	setHeight(getroot(g[0][0]),0);
	}
	int M;
	cin>>M;
	for (int i=0; i<M; i++)
	{
		int v1,v2;
		cin>>v1;
		cin>>v2;
		if (v1==v1) cout<<0;
		else 
		if (N>1)cout<<height(v1,v2)<<endl;
	}
	
	return 0;
}
