#include <stdio.h>
#include <iostream>

using std::cin;
using std::cout;

/////////////////////////////////////////////////////////////////////

template <class T> class List
{
	struct list
	{
		T data;
		list *next;
	};

	list *start, *now;
public:
	bool isEnd;

	void onStart();
	T getNextElem();
	void addElem(T data);
	void Destroy();

	List();
	~List();
};




template <class T> void List<T>::onStart()
{
	now = start;
	isEnd = false;
}

template <class T> T List<T>::getNextElem()
{
	if(now->next)
	{
		now = now->next;
		return now->data;
	}
	else
	{
		isEnd = true;
	}
}

template <class T> List<T>::List()
{
	start = new list;
	start->next=0;
	now = start;
	isEnd = true;
}

template <class T> void List<T>::addElem(T data)
{
	list *t = new list;
	t->data = data;
	t->next = 0;
	now->next = t;
	now = now->next;
}

template <class T> List<T>::~List()
{
	Destroy();
}

template <class T> void List<T>::Destroy()
{
	list *t = start, *t1;
	while(t)
	{
		t1 = t->next;
		delete t;
		t = t1;
	}
}

/////////////////////////////////////////////////////////////////////

class Node
{
	Node *parent;
	List<Node*> childs;
public:
	int number;			//номер узла
	int r;				//расстояние до родителя

	Node* getParent() const;
	void onStartChild();			//установить указатель на первый дочерний узел
	Node* getNextChild();			//получить следующий дочерний узел, если конец, то возвращает 0
	Node* addChild(int num, int r);

	Node();
	~Node();
};

Node::Node(): childs()
{
	parent = 0;
	r = 0;
	number = 0;
}

Node::~Node()
{
	childs.onStart();
	while(1)
	{
		Node *t = childs.getNextElem();
		if(!childs.isEnd) delete t; else break;
	}
}

Node* Node::addChild(int num, int r)
{
	Node *t = new Node;
	t->number = num;
	t->r = r;
	t->parent = this;
	childs.addElem(t);
	return t;
}

Node* Node::getParent() const
{
	return parent;
}

Node* Node::getNextChild()
{
	Node* t = childs.getNextElem();
	if(childs.isEnd) return 0;
	else return t;
}

void Node::onStartChild()
{
	childs.onStart();
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
}

void Three::addNode(int num1, int num2, int r)
{
	if(pointers[num1].p) pointers[num2].p = (pointers[num1].p->addChild(num2, r));
	else
	{
		pointers[num1].p = new Node;
		pointers[num2].p = (pointers[num1].p->addChild(num2, r));
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
