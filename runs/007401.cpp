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
	int GetNumber() {return Number;}
	void AddEdge(Node* node, int l)
			{Edge e;
			 e.To = node;
			 e.Length = l;
			 Edges.push_back(e);}

	std::vector<Edge> Edges;
private:
	int Number;
};

int DepthFirstSearch(Node* Begin, Node* End, Node* Pred, bool& IsFound, int CurLength)
{
	if (Begin == End)
	{
		IsFound = true;
		return CurLength;
	}
	int l = 0;
	for (std::vector<Edge>::iterator i = Begin->Edges.begin();i!=Begin->Edges.end();++i)
	{
		if (i->To != Pred)
			l = DepthFirstSearch(i->To, End, Begin, IsFound, CurLength + i->Length);
		if (IsFound)
			return l;
	}
	return 0;
}

int PathLength(Node* From, Node* To) //реализовано при помощи поиска в глубину
{
	bool b = false;
	return DepthFirstSearch(From, To, From, b, 0);
}

int main()
{
	using namespace std;
	int n;
	cin>>n;
	vector<Node*> Nodes;
	for (int i=0;i<n;i++)
		Nodes.push_back(new Node(i));
	int From, To, Length;
	for (int i=0;i<n-1;i++)
	{
		cin>>From>>To>>Length;
		Nodes[From-1]->AddEdge(Nodes[To-1], Length);
		Nodes[To-1]->AddEdge(Nodes[From-1], Length);
	}
	cin>>n;
	vector<int> Out;
	for (int i=0;i<n;i++)
	{
		cin>>From>>To;
		Out.push_back(PathLength(Nodes[From-1], Nodes[To-1]));
	}
	for (int i=0;i<n;i++)
	{
		cout<<Out[i]<<endl;
	}
	return 0;
}