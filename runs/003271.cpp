#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

//��������� ��� �������� ����� ����� � �� �����
struct graph_struct
{
	int number;
	int weight;
};

//���������, ���������� � ������ ������, 
//����� �������� ���������� ��������� ����������
struct pair_struct
{
	int x;
	int y;
	bool flag;
	int ancestor;
	int path;
};

//��������� ��� �������� ����� ������ ������
struct vertex_struct
{
	int weight_vertex;
	int previos_vertex;
};

typedef struct graph_struct graph_type;
typedef struct pair_struct pair_type;
typedef struct vertex_struct vertex_type;

vector<vector<graph_type> > Graph;
vector<pair_type> Quest;

vector<vertex_type> Vertex;
vector<bool> SetVert;

vector <int> DSU;
vector <int> Ancestor;
vector <bool> Union;

int N, M;

//���������� ������� ���������������� ��������:

//������������� �������
void Init_Set ()
{
	DSU.resize (N);
	Ancestor.resize (N);
	Union.resize (N);
	for (int i = 0; i < N; ++i)
	{
		DSU[i] = i;
		Ancestor[i] = 0;
		Union[i] = false;
	}
}

//���������� ������ �������� � �������
void Make_Set_DSU (int x)
{
	DSU[x] = x;
}

//����� ��������� �� ��� �������� 
int Find_Set_DSU (int x)
{
	if (x == DSU[x])  return x;
	return DSU[x] = Find_Set_DSU (DSU[x]);
}

//����� �������� �� ��������� � ����������� �� � ���� ���������
void Union_DSU (int x, int y, int new_ancestor)
{
	x = Find_Set_DSU (x);
	y = Find_Set_DSU (y);
	if (rand() & 1)
		swap(x, y);
	DSU[x] = y;
	Ancestor[y] = new_ancestor;
}

//������������� ������ �����
void Init_Vertex()
{
	Vertex.resize (N);
	for (int i = 0; i < N; i++)
	{
		Vertex[i].previos_vertex = 0;
		Vertex[i].weight_vertex = 0;
	}
}

//���������� ��� ������
int LCA (pair_type Q, int v)
{
	if (Q.x == v)
		return Q.y;
	else
		if (Q.y == v)
			return Q.x;
		else
			return -1;
}

//������� ���������� ����������� ������ ������, �������� �������
void Deep_First_Search (int v, int weight) 
{
	Make_Set_DSU(v);
	Ancestor[v] = v;
	Union[v] = true;

	for (size_t i = 0; i < Graph[v].size(); ++i)
		if ( !Union[Graph[v][i].number] ) 
		{
			Vertex[Graph[v][i].number].previos_vertex = weight;
			Vertex[Graph[v][i].number].weight_vertex = Graph[v][i].weight + 
											Vertex[Graph[v][i].number].previos_vertex;
			Deep_First_Search (Graph[v][i].number, Vertex[Graph[v][i].number].weight_vertex);
			Union_DSU (v, Graph[v][i].number, v);

		}

	for (size_t i = 0; i < Quest.size(); ++i)
	{
		int u = LCA(Quest[i], v);
		if (u != -1)
			if ( (Union[u]) && (!Quest[i].flag) ) 
			{
				Quest[i].flag = true;
				Quest[i].ancestor = Ancestor[Find_Set_DSU(u)];
			}
	}
}

//���������� ���������� ����� ��������� ������ ������ ������
void Shortest_Path()
{
	for (size_t i = 0; i < Quest.size(); i++)	
		Quest[i].path = Vertex[Quest[i].x].weight_vertex - 
						Vertex[Quest[i].ancestor].weight_vertex +
						Vertex[Quest[i].y].weight_vertex - 
						Vertex[Quest[i].ancestor].weight_vertex;
}

//����� �����������
void Out_Data()
{
	for (size_t i = 0; i < Quest.size(); i++)
		cout<<Quest[i].path<<"\n";
}

//������������ ���������� � ������
void Set_Vertex(int a, int b, int weight)
{
	graph_type gr;
	gr.weight = weight;
	for (int i = 0; i < N; i++)
	{
		if (i == a)
		{
			gr.number = b;
			Graph[a].push_back (gr);
		}
		if (i == b)
		{
			gr.number = a;
			Graph[b].push_back (gr);
		}
	}
}

//�������� ���� ������
void Set_Quest(int a, int b)
{
		pair_type pair;
		pair.x = a;
		pair.y = b;
		pair.flag = false;
		pair.ancestor = -1;
		Quest.push_back (pair);
}

//������������� �����
void Init_Graph()
{
	for (int i = 0; i < N; i++)
	{
		vector<graph_type> new_vertex;
		Graph.push_back(new_vertex);
	}
}

//������ ������
void Read_Data()
{	
	int a, b, weight;
	cin>>N;
	Init_Graph();
	for (int i = 0; i < N-1; i++)
	{
		cin>>a>>b>>weight;
		a--;
		b--;
		Set_Vertex(a, b, weight);
	}

	cin>>M;
	for (int i = 0; i < M; i++)
	{
		cin>>a>>b;
		a--;
		b--;
		Set_Quest(a, b);
	}
}

int main(int argc, char* argv[])
{
	Read_Data();
	Init_Set();
	Init_Vertex();
	Deep_First_Search (0, 0);
	Shortest_Path();
	Out_Data();
	
	return 0;
}