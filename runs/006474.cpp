#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <cstring>
using namespace std;

typedef unsigned short ushort;

struct stackelem
{
	ushort id;
	ushort eid;
	ushort last;
	bool init;
	stackelem *next;
	stackelem *back;
};
struct edge
{
	ushort id[2];
	ushort dist;
};
class node
{
	ushort branch;
	ushort deep;
	int distrm;
	node* ptrm;
	bool rm;
	vector <ushort> links;
public:
	node();
	friend void scaner(node**,edge**,ushort&);
	friend void solve(node**);
};


int main()
{
	node * allnodes[40001];
	edge * alledges[40001];
	ushort edgenum = 0;
	memset(allnodes,0,40001*sizeof(node*));
	memset(alledges,0,40001*sizeof(edge*));
	scaner(allnodes,alledges,edgenum);
	solve(allnodes);
	return 0;
}
void scaner(node** nodes,edge**edges, ushort &edgenum)
{
	ushort N,in[3];
	cin >> N;
	for(ushort i = 1; i < N; i++)
	{
		cin >> in[0] >> in[1] >> in[2];
		if(nodes[in[0]]==NULL)
			nodes[in[0]] = new node;
		if(nodes[in[1]]==NULL)
			nodes[in[1]] = new node;
		edges[edgenum] = new edge;
		edges[edgenum]->dist = in[2];
		edges[edgenum]->id[0] = in[0];
		edges[edgenum]->id[1] = in[1];
		nodes[in[0]]->links.push_back(edgenum);
		nodes[in[1]]->links.push_back(edgenum);
		edgenum++;
	}
	nodes[1]->branch = 1;
	nodes[1]->deep = 0;
	nodes[1]->distrm = 0;
	nodes[1]->ptrm = nodes[1];
	nodes[1]->rm = true;

	ushort br = 2;
	stackelem *base = NULL,*ptr;
	base = new stackelem;
	base->back = NULL;
	base->id = 40002;
	base->next = NULL;
	base->eid = 40002;
	base->last = 0;

	base->next = new stackelem;
	ptr = base->next;
	ptr->next = NULL;
	ptr->last = 0;
	ptr->init = true;
	ptr->eid = 40002;
	ptr->id = 1;
	ptr->back = base;

	while(ptr!=base)
	{
		if(!ptr->init)
		{
			if(nodes[ptr->back->id]->rm)
			{
				nodes[ptr->id]->branch = br++;
				nodes[ptr->id]->distrm = edges[ptr->eid]->dist;
				nodes[ptr->id]->ptrm = nodes[ptr->back->id];
			}
			else
			{
				nodes[ptr->id]->branch = nodes[ptr->back->id]->branch;
				nodes[ptr->id]->distrm = edges[ptr->eid]->dist+nodes[ptr->back->id]->distrm;
				nodes[ptr->id]->ptrm = nodes[ptr->back->id]->ptrm;
			}
			nodes[ptr->id]->deep = nodes[ptr->back->id]->deep;
			if(nodes[ptr->id]->links.size() > 2)
				nodes[ptr->id]->rm = true;
			else
				nodes[ptr->id]->rm = false;
			if(nodes[ptr->back->id]->rm)
				nodes[ptr->id]->deep++;
			ptr->init = true;
		}
		if(ptr->last < nodes[ptr->id]->links.size())
		{
			if(nodes[ptr->id]->links[ptr->last] == ptr->eid)
			{
				ptr->last++;
				continue;
			}
			ptr->next = new stackelem;
			ptr->next->next = NULL;
			ptr->next->last = 0;
			ptr->next->init = false;
			ptr->next->eid = nodes[ptr->id]->links[ptr->last];
			ptr->next->id = edges[nodes[ptr->id]->links[ptr->last]]->id[0]==ptr->id?edges[nodes[ptr->id]->links[ptr->last]]->id[1]:edges[nodes[ptr->id]->links[ptr->last]]->id[0];
			ptr->next->back = ptr;
			ptr->last++;
			ptr = ptr->next;
			continue;
		}
		ptr=ptr->back;
		delete ptr->next;
	}
}
void solve(node ** nodes)
{
	ushort M,id[2];
	int base = 0;
	node *f,*s;
	cin >> M;
	for(ushort i = 0; i < M; i++)
	{
		cin >> id[0] >> id[1];
		base = 0;
		f = nodes[id[0]];
		s = nodes[id[1]];
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
node::node()
{
	deep = 0;
	distrm = 0;
	rm = false;
	ptrm = NULL;
}