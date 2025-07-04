#include <vector>
#include <iostream>

static int* AdjacencyMatrix;
static int NodeCount;
static const int MaxWeight = 40000;

void FindPaths() //Алгоритм Флойда — Уоршелла для нахождения кратчайших путей для каждой пары вершин
{
	int* m0, *m1;
	m0 = AdjacencyMatrix;
	m1 = new int[NodeCount*NodeCount];
	for (int n=0;n<NodeCount;n++)
	{
		for (int i=0;i<NodeCount;i++)
			for (int j=0;j<NodeCount;j++)
				m1[i*NodeCount+j] = std::min(m0[i*NodeCount+j], m0[i*NodeCount+n] + m0[n*NodeCount+j]);
		std::swap(m0, m1);
	}
	AdjacencyMatrix = m0;
	delete[] m1;
}

int main()
{
	using namespace std;
	cin>>NodeCount;
	AdjacencyMatrix = new int[NodeCount*NodeCount];
	std::fill(AdjacencyMatrix, AdjacencyMatrix+NodeCount*NodeCount, MaxWeight);
	int From, To, Length;
	for (int i=0;i<NodeCount-1;i++)
	{
		cin>>From>>To>>Length;
		AdjacencyMatrix[(From-1)*NodeCount + To-1] = Length;
		AdjacencyMatrix[(To-1)*NodeCount + From-1] = Length;
		AdjacencyMatrix[i*NodeCount+i] = 0;
	}
	AdjacencyMatrix[NodeCount*NodeCount-1] = 0;
	FindPaths();

	int n = 0;
	cin>>n;
	vector<int> Out;
	for (int i=0;i<n;i++)
	{
		cin>>From>>To;
		Out.push_back(AdjacencyMatrix[(From-1)*NodeCount+To-1]);
	}
	for (int i=0;i<n;i++)
	{
		cout<<Out[i]<<endl;
	}
	return 0;
}