#include <vector>
#include <iostream>
#include <queue>

class Node;

struct Edge
{
public:
	Node* To;
	int Length;
};

class Node
{
public:
	explicit Node(int n): Number(n) {}
	void AddEdge(Node* node, int l)
			{Edge e;
			 e.To = node;
			 e.Length = l;
			 Edges.push_back(e);}

	std::vector<Edge> Edges;
	Edge ParentEdge;
	int Depth;
	int Number;
};

static int NodeCount;
static Node* Root;
static std::vector<Node*> Nodes;

void Preprocessing() //нахождение корня, определение глубин вершин
{
	Root = Nodes[0];
	for (std::vector<Node*>::iterator iter = (Nodes.begin()+1); iter!=Nodes.end(); ++iter)
	{
		if ( (*iter)->  Edges.size() > Root->Edges.size())
			Root = *iter;
	}
 
	Root->Depth = 0;
	std::queue<Node*> q;
	q.push(Root);
	bool *Map = new bool[NodeCount];
	std::fill(Map, Map+NodeCount, false);
	Map[Root->Number] = true;
	Node* node;
	Edge e;

	while (q.size())
	{
		node = q.front();
		q.pop();
		for (std::vector<Edge>::iterator iter = node->Edges.begin(); iter!=node->Edges.end(); ++iter)
		{
			if (false == Map[iter->To->Number])
			{
				e.Length = iter->Length;
				e.To = node;
				iter->To->ParentEdge = e;
				iter->To->Depth = node->Depth + 1;
				q.push(iter->To);
				Map[iter->To->Number] = true;
			}
		}
	}
}

int PathLength(Node* From, Node* To) //подъём в дереве
{
	int result = 0;
	Node* f = From, *t = To;
	while (f->Depth > t->Depth)
	{
		result += f->ParentEdge.Length;
		f = f->ParentEdge.To;
	}
	while (t->Depth > f->Depth)
	{
		result += t->ParentEdge.Length;
		t = t->ParentEdge.To;
	}
	while (t != f)
	{
		result += t->ParentEdge.Length;
		result += f->ParentEdge.Length;
		t = t->ParentEdge.To;
		f = f->ParentEdge.To;
	}
	return result;
}

int main()
{
	using namespace std;
	cin>>NodeCount;
	for (int i=0;i<NodeCount;i++)
		Nodes.push_back(new Node(i));
	int From, To, Length;
	for (int i=0;i<NodeCount-1;i++)
	{
		cin>>From>>To>>Length;
		Nodes[From-1]->AddEdge(Nodes[To-1], Length);
		Nodes[To-1]->AddEdge(Nodes[From-1], Length);
	}
	int n;
	cin>>n;
	vector<pair<int, int> > In;
	for (int i=0;i<n;i++)
	{
		cin>>From>>To;
		In.push_back(pair<int,int>(From-1, To-1));
	}

	Preprocessing();
	for (vector<pair<int,int> >::iterator iter = In.begin();iter!=In.end();++iter)
	{
		if (iter->first == iter->second)
			cout<<0<<endl;
		else
			cout<<PathLength(Nodes[iter->first], Nodes[iter->second])<<endl;
	}
	return 0;
}