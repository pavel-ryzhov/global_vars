// ��������� ��� ������� ������ "���������� � ������" �� ��������� ������� �������
// ������� ��� ��������� �������� ��������� ������ "������� ���������������� ��������", ������� ���� ���������� �������� (Tarjan)

#include <iostream>
#include <vector>
#include <cstdlib>

using std::cout;
using std::cin;
using std::vector;

typedef vector< vector<long int> > Graph;

class MyGraph
{
public:
	void writeAns()	// �������� ������ �� �����
	{
		for (long int i = 0; i < ansList.size(); i++)
			cout << ansList[i] << "\n" ;
	}

	void dfs()	// ��������� ����� ������ � �����
	{
		dfs(0, 0, 0);
	}
	
	void read(long int nodesPairsNumber)	// ��������� ����
	{
		for (long int i = 0; i < nodesPairsNumber; i++)
		{
			long int node1, node2;
			long int distance;
			cin >> node1 >> node2 >> distance;
			node1--;
			node2--;
			graph[node1].push_back(node2);
			graph[node2].push_back(node1);
			distances[node1].push_back(distance);
			distances[node2].push_back(distance);
		}
	}

	void readQuest(long int numberOfQuestions)	// ��������� �������
	{
		ansList.resize(numberOfQuestions);
		for (long int i = 0; i < numberOfQuestions; i++)
		{
			long int node1, node2;
			cin >> node1 >> node2;
			node1--;
			node2--;
			if (node1 == node2)
				ansList[i] = 0;
			else
			{
				quest[node1].push_back(node2);
				quest[node2].push_back(node1);
				questNo[node1].push_back(i);
				questNo[node2].push_back(i);
			}
		}
	}

	MyGraph(long int size)
	{
		graph.resize(size);
		distanceToRoot.resize(size);
		distances.resize(size);
		quest.resize(size);
		questNo.resize(size);
		dsu.resize(size);
		ancestor.resize(size);
		for (long int i = 0; i < size; i++)
			wasVisited.push_back(false);
	}

private:
	Graph graph;	// ��� ����
	Graph distances;	// distances[i][j] - ���������� ����� �������� i+1 � graph[i][g]+1
	vector <long int> distanceToRoot;	// distanceToRoot[i] - ���������� �� ������� i+1 �� �����
	Graph quest;	// ������� � ���� �����
	Graph questNo;	// questNo[i][j] ������ ����� �� ������ i+1, quest[i][j]+1
	vector <long int> ansList;	// ansList[i] - ����� �� ������ questList[2i][2i+1]
	vector <bool> wasVisited;	// wasVisited[i] = true, ���� ������� i+1 ���� �������� ��� ������
	vector <long int> dsu;	// ������� ���������������� ��������
	vector <long int> ancestor;	// ancestor[i] ������ ����� ����������� ������ ������ ������, ������������������ ��������� �������� �������� ������ i+1
	
	long int getFromDsu(long int v) 
	{
		if (v == dsu[v])
			return v;
		else
			return dsu[v] = getFromDsu (dsu[v]);
	}
	
	void uniteUnDsu(long int v1, long int v2, long int newAncestor)
	{
		v1 = getFromDsu(v1);
		v2 = getFromDsu(v2);
		if (rand() & 1)
		{
			long int tmp = v1;
			v1 = v2;
			v2 = tmp;
		}
		dsu[v1] = v2;
		ancestor[v2] = newAncestor;
	}

	// ����� � �������
	void dfs(long int v,	// ������� �������
			 long int lastV,	// �������, �� ������� ������ � �������	
			 long int lastI)	// v = graph[lastV][lastI]
	{
		dsu[v] = v;
		ancestor[v] = v;
		wasVisited[v] = true;
		if (v == 0)
			distanceToRoot[v] = 0;
		else
			distanceToRoot[v] = distanceToRoot[lastV] + distances[lastV][lastI];
		for (long int i = 0; i < graph[v].size(); i++)
			if (wasVisited[graph[v][i]] == false)
			{
				dfs(graph[v][i], v, i);
				uniteUnDsu(v, graph[v][i], v);
			}
		for (size_t i=0; i<quest[v].size(); ++i)
			if (wasVisited[quest[v][i]])
			{
				ansList[questNo[v][i]] = 
					distanceToRoot[v] + distanceToRoot[quest[v][i]]
					- 2*distanceToRoot[ancestor[getFromDsu(quest[v][i])]];
			}
	}
};


int main()
{
	// ������ �����
	long int n;	// ���������� ������
	cin >> n;
	MyGraph myGraph(n);	// ����
	myGraph.read(n-1);

	// ������ ��������
	long int m;	// ���������� ��������
	cin >> m;
	myGraph.readQuest(m);
	
	myGraph.dfs();	// ����� �����
	myGraph.writeAns();	// ����������� ����������
	return 0;
}