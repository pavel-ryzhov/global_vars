#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;

typedef unsigned short ushort;

struct distant
{
	ushort id;
	int val;
};
class node
{
	node* parent;
	ushort branch;
	ushort deep;
	int distrm;
	ushort ID;
	node* ptrm;
	bool rm;
	vector <node*> childs;
public:
	node();
	node(node* par,ushort id,int dist,ushort branchid,ushort dp,node* ptr);
	friend void scaner(vector <node*>*);
	friend int comp(const void * a, const void * b);
	friend void modify(node*);
	friend void solve(vector <node*>&);
	friend node* find_node(vector <node*>&,ushort);
};


int main()
{
	vector <node*> allnodes;
	scaner(&allnodes);
	solve(allnodes);
	return 0;
}
void scaner(vector <node*> *nodes)
{
	node *n = new node,*par;
	nodes->push_back(n);
	ushort branches = 1;

	ushort N,in[3],br;
	cin >> N;
	for(ushort i = 1; i < N; i++)
	{
		cin >> in[0] >> in[1] >> in[2];
		par = find_node(*nodes,in[0]);
		if(par->childs.empty())
		{
			n = new node(par,in[1],in[2]+par->distrm,par->branch,par->deep,par->ptrm);
			par->childs.push_back(n);
		}
		else
		{
			if(!par->rm)
				modify(par);
			n = new node(par,in[1],in[2],++branches,par->deep+1,par);
		}
		nodes->push_back(n);
	}
}
void modify(node* par)
{
	node* ptr = par->childs[0];
	par->rm = true;
	ptr->distrm-=par->distrm;
	ptr->ptrm = par;
	ptr->deep++;
	while(!ptr->childs.empty())
	{
		ptr=ptr->childs[0];
		ptr->distrm-=par->distrm;
		ptr->ptrm = par;
		ptr->deep++;
	}
}
void solve(vector <node*> &nodes)
{
	ushort M,id[2];
	int base = 0;
	node *f,*s;
	cin >> M;
	for(ushort i = 0; i < M; i++)
	{
		cin >> id[0] >> id[1];
		base = 0;
		f = find_node(nodes,id[0]);
		s = find_node(nodes,id[1]);
		if(f==s)
		{
			cout << 0 << endl;
			continue;
		}
		while(f->ptrm!=s->ptrm)
		{
			if(f->deep < s->deep)
			{
				base += s->distrm;
				s = s->ptrm;
				continue;
			}
			base += f->distrm;
			f = f->ptrm;
		}
		if(f->branch==s->branch)
		{
			cout << base + abs(f->distrm-s->distrm) << endl;
			continue;
		}
		else
			cout << base + f->distrm+s->distrm << endl;
	}
}
int comp(const void * a, const void * b)
{
	return ((node*)a)->ID - ((node*)b)->ID;
}
node* find_node(vector <node*> &nodes,ushort id)
{
	ushort beg = 0,end = nodes.size()-1,mid=end/2;
	while(beg <= end)
	{
		if(nodes[mid]->ID == id)
			return nodes[mid];
		if(nodes[mid]->ID > id)
		{
			end = mid==end?mid-1:mid;
			mid = (beg+end)/2;
			continue;
		}
		beg = mid==beg?mid+1:mid;
		mid = (beg+end)/2;
	}
	return NULL;
}
node::node()
{
	parent = NULL;
	ID = 1;
	deep = 0;
	distrm = 0;
	rm = true;
	ptrm = this;
	branch = 1;
}
node::node(node* par,ushort id, int dist, ushort branchid,ushort dp,node *ptr) 
{
	parent = par;
	ID = id;
	distrm = dist;
	deep = dp;
	ptrm = ptr;
	rm = false;
	branch = branchid;
}