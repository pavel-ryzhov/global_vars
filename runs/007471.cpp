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

bool* Map;
static int NodeCount;

int PathLength(Node* From, Node* To) //реализовано при помощи поиска в ширину
{
	std::queue<struct Edge> q;
	Edge e = {From, 0}, t;
	q.push(e);
	std::fill(Map, Map+NodeCount, false);
	Map[From->GetNumber()] = true;
	while (q.size())
	{
		e = q.front();
		q.pop();
		for (std::vector<Edge>::iterator iter = e.To->Edges.begin(); iter!=e.To->Edges.end(); ++iter)
		{
			if (!Map[iter->To->GetNumber()])
			{
				if (iter->To == To)
					return iter->Length + e.Length;
				t = *iter;
				t.Length += e.Length;
				q.push(t);
				Map[iter->To->GetNumber()] = true;
			}
		}
	}
	return 0;
}

int main()
{
	using namespace std;
	cin>>NodeCount;
	vector<Node*> Nodes;
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

	Map = new bool[NodeCount];
	for (vector<pair<int,int> >::iterator iter = In.begin();iter!=In.end();++iter)
	{
		if (iter->first == iter->second)
			cout<<0<<endl;
		else
			cout<<PathLength(Nodes[iter->first], Nodes[iter->second])<<endl;
	}
	delete[] Map;
	cin.get();
	cin.get();
	return 0;
}