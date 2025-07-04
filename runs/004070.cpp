#include <stdio.h>
#include <iostream>

using std::cin;
using std::cout;

/////////////////////////////////////////////////////////////////////

class Node
{
	Node *parent;
public:
	int number;			//номер узла
	int r;				//расстояние до родителя

	Node* getParent() const;
	Node* addChild(int num, int r);
	void setParent(Node* p);

	Node();
	~Node();
};

Node::Node()
{
	parent = 0;
	r = 0;
	number = 0;
}

Node::~Node()
{
}

Node* Node::addChild(int num, int r)
{
	Node *t = new Node;
	t->number = num;
	t->r = r;
	t->parent = this;
	return t;
}

Node* Node::getParent() const
{
	return parent;
}

void Node::setParent(Node* p)
{
	parent = p;
}



/////////////////////////////////////////////////////////////////////

class Three
{
	struct Pointers
	{
		Node *p;
	};

	Pointers *pointers;		//массив указателей на все элементы дерева
	int numNodes;
public:
	void addNode(int num1, int num2, int r);	//num1 = к какому узлу присоединить этот узел, num2 = номер этого узла
	int length(int a, int b);					//возвращает длину кратчайшего пути между a и b - узлами

	Three(int numNodes);
	~Three();
};

Three::Three(int numNodes): pointers()
{
	Node *head = new Node;
	head->number = 1;
	head->r = 0;
	Three::numNodes = numNodes;
	pointers = new Pointers[Three::numNodes+1];
	for(int i=0; i<Three::numNodes; i++)
		pointers[i].p = 0;
	pointers[1].p = head;
}

Three::~Three()
{
	for(int i=0; i<Three::numNodes; i++)
	{
		if(pointers[i].p) delete pointers[i].p;
	}
	delete[] pointers;
}

void Three::addNode(int num1, int num2, int r)
{
	if(pointers[num1].p && !pointers[num2].p)
	{
		pointers[num2].p = (pointers[num1].p->addChild(num2, r));
	}
	else if(!pointers[num1].p && !pointers[num2].p)
	{
		pointers[num1].p = new Node;
		pointers[num2].p = (pointers[num1].p->addChild(num2, r));
	}
	else if(!pointers[num1].p && pointers[num2].p)
	{
		pointers[num1].p = (pointers[num2].p->addChild(num1, r));
	}
	else if(pointers[num1].p && pointers[num2].p)
	{
		Node *t;
		bool f = 0;

		t = pointers[num1].p;
		do
		{
			if(t->number == 1)
			{
				f = 1;
				break;
			}
		}
		while( t = t->getParent() );

		if(f)
		{
			Node *tp;
			tp = pointers[num2].p->getParent();
			pointers[num2].p->setParent(pointers[num1].p);
			tp->setParent(pointers[num2].p);
			tp->r = pointers[num2].p->r;
			pointers[num2].p->r = r;
		}
		else
		{
			Node *tp;
			tp = pointers[num1].p->getParent();
			pointers[num1].p->setParent(pointers[num2].p);
			tp->setParent(pointers[num1].p);
			tp->r = pointers[num1].p->r;
			pointers[num1].p->r = r;

		}
	}
}


int Three::length(int a, int b)
{
	if(a==b) return 0;
	Node *pa, *pb;
	pa = pointers[a].p;
	pb = pointers[b].p;

	char *am = new char[numNodes+1];
	char *bm = new char[numNodes+1];

	for(int i=0; i<=numNodes; i++)
	{
		am[i] = 0;
		bm[i] = 0;
	}

	am[pa->number] = 1;
	bm[pb->number] = 1;

	Node *t = pa->getParent();
	while(1)
	{
		if(!t) break;
		am[t->number] = 1;
		t = t->getParent();
	}

	t = pb->getParent();
	while(1)
	{
		if(!t) break;
		bm[t->number] = 1;
		t = t->getParent();
	}

	int max = 0, ind = 0;
	for(int i=0; i<=numNodes; i++)
		if((am[i]==bm[i])&&(i>=max)&&(am[i]==1))
		{
			max = am[i];
			ind = i;
		}

	int r=0;

	if(ind!=pa->number)
	{
		r=pa->r;
		t = pa->getParent();
		while(1)
		{
			if(!t) break;
			if(t->number==ind) break;
			r += t->r;
			t = t->getParent();
		}
	}

	if(ind!=pb->number)
	{
		r += pb->r;
		t = pb->getParent();
		while(1)
		{
			if(!t) break;
			if(t->number==ind) break;
			r += t->r;
			t = t->getParent();
		}
	}

	delete[] am;
	delete[] bm;

	return r;
}

/////////////////////////////////////////////////////////////////////


int main()
{
	Three *x;

	int a, b, r, N;
	cin>>N;
	x = new Three(N);
	for(int i=0; i<N-1; i++)
	{
		cin>>a>>b>>r;
		x->addNode(a, b, r);
	}
	int N1, r1;
	cin>>N1;
	for(int i=0; i<N1; i++)
	{
		cin>>a>>b;
		r1 = x->length(a, b);
		cout<<r1<<"\n";
	}
	return 0;
}
