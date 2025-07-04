#include <vector>
#include <iostream>

using namespace std;



class Edge
{
public:
	long AdjacentVertex;
	long EdgeLength;
};

class Vertex
{
public:
	vector<Edge> Edges;
	long Length;
};

typedef vector<Vertex> Graph;
typedef vector<Edge>::const_iterator GraphIter;


class GraphAnalyser
{
	Graph CurrentGraph;
	long Root;
	vector<long> Height, OrderList, First, Tree;
	vector<char> VertexUsed;

public:
	int Initialize ();
	void LCAMakeOrderList (long, long, long);
	void BuildTree (long, long, long);
	void Prepare ();
	long TreeMin (long, long, long, long, long);
	long LCA (long, long);
	long GetLenth (long Vert)
	{
		return CurrentGraph[Vert].Length;
	};
};




int GraphAnalyser::Initialize ()
{
	long n;
	long vert1, vert2;
	Edge CurrentEdge;
	Vertex default_Vertex;

	default_Vertex.Length = 0;
	cin >> n;
	CurrentGraph.assign (n, default_Vertex);
	if (n == 0)
		return 1;
	Root = 0;
	for (int i = 0; i<n-1; i++)
	{
		cin >> vert1 >> vert2 >> CurrentEdge.EdgeLength;
		if (i == 0)
			Root = vert1-1;
		CurrentEdge.AdjacentVertex = vert2-1;
		CurrentGraph[vert1-1].Edges.push_back(CurrentEdge);
		CurrentEdge.AdjacentVertex = vert1-1;
		CurrentGraph[vert2-1].Edges.push_back(CurrentEdge);

	}	
	return 0;
}

void GraphAnalyser::LCAMakeOrderList (long v, long h = 1, long l = 0)
{
	VertexUsed[v] = true;
	Height[v] = h;
	OrderList.push_back (v);
	CurrentGraph[v].Length = l;
	for (GraphIter i = CurrentGraph[v].Edges.begin(); i != CurrentGraph[v].Edges.end(); ++i)
		if (!VertexUsed[i->AdjacentVertex])
		{
			LCAMakeOrderList (i->AdjacentVertex, h+1, l+i->EdgeLength);
			OrderList.push_back (v);
		}
}

void GraphAnalyser::BuildTree(long i, long Left, long Right)
{
	if (Left == Right)
		Tree[i] = OrderList[Left];
	else
	{
		long m = (Left + Right) / 2;
		BuildTree (i+i, Left, m);
		BuildTree (i+i+1, m+1, Right);
		if (Height[Tree[i+i]] < Height[Tree[i+i+1]])
			Tree[i] = Tree[i+i];
		else
			Tree[i] = Tree[i+i+1];
	}
}

void GraphAnalyser::Prepare ()
{
	long n = (long) CurrentGraph.size();
	Height.resize (n);
	OrderList.reserve (n*2 + 1);
	VertexUsed.assign (n, 0);

	LCAMakeOrderList (Root);

	long m = (long) OrderList.size();
	Tree.assign (OrderList.size() * 4 + 1, -1);
	BuildTree (1, 0, m-1);

	First.assign (n, -1);
	for (long i = 0; i < m; ++i)
	{
		long v = OrderList[i];
		if (First[v] == -1)
			First[v] = i;
	}
}

long GraphAnalyser::TreeMin (long i, long sLeft, long sRight, long Left, long Right)
{
	if (sLeft == Left && sRight == Right)
		return Tree[i];
	long sm = (sLeft + sRight) / 2;
	if (Right <= sm)
		return TreeMin (i+i, sLeft, sm, Left, Right);
	if (Left > sm)
		return TreeMin (i+i+1, sm+1, sRight, Left, Right);
	long ans1 = TreeMin (i+i, sLeft, sm, Left, sm);
	long ans2 = TreeMin (i+i+1, sm+1, sRight, sm+1, Right);
	return Height[ans1] < Height[ans2] ? ans1 : ans2;
}

long GraphAnalyser::LCA (long a, long b)
{
	long left = First[a],
		right = First[b];
	if (left > right)  swap (left, right);
	return TreeMin (1, 0, (long)OrderList.size()-1, left, right);
}

int main()
{
	GraphAnalyser MyAnalyser;
	long n;
	if (1 == MyAnalyser.Initialize())
		return 1;
	MyAnalyser.Prepare();

	cin >> n;
	for (long i = 0; i < n; i++)
	{
		long v1, v2, l;
		cin >> v1 >> v2;
		v1--;
		v2--;
		long v = MyAnalyser.LCA (v1, v2);
		l = MyAnalyser.GetLenth(v1) + MyAnalyser.GetLenth(v2) - 2 * MyAnalyser.GetLenth(v);
		cout << l <<endl;
		
	}
	cin>>n;
	return 0;
}
