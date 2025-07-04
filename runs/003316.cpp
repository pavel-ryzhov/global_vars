// ya.problem2.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

//структура для хранения ребер графа и их весов
struct graph_struct
{
	int number;
	int weight;
};

//структура, работающая с парами вершин, 
//между которыми необходимо рассчитаь расстояния
struct pair_struct
{
	int x;
	int y;
	bool flag;
	int ancestor;
	int path;
};

//структура для хранения весов вершин дерева
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
vector<vector<int> > Key;

vector<vertex_type> Vertex;
vector<bool> SetVert;

vector <int> DSU;
vector <int> Ancestor;
vector <bool> Union;

int N, M;

//реализация системы непересекающихся множеств:

//инициализация системы
void Init_Set ()
{
	DSU.resize (N);
	Ancestor.resize (N);
	Union.resize (N);
	Vertex.resize(N);
	for (int i = 0; i < N; ++i)
	{
		DSU[i] = i;
		Ancestor[i] = 0;
		Union[i] = false;
	}

}

//добавление нового элемента в систему
void Make_Set_DSU (int x)
{
	DSU[x] = x;
}

//поиск множества по его элементу 
int Find_Set_DSU (int x)
{
	if (x == DSU[x])  return x;
	return DSU[x] = Find_Set_DSU (DSU[x]);
}

//поиск множеств по элементам и объединение их в одно множество
void Union_DSU (int x, int y, int new_ancestor)
{
	x = Find_Set_DSU (x);
	y = Find_Set_DSU (y);
	if (rand() & 1)
		swap(x, y);
	DSU[x] = y;
	Ancestor[y] = new_ancestor;
}

//нахождение пар вершин
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

//функция нахождения наименьшего общего предка, алгоритм Тарьяна
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

	for (size_t i = 0; i < Key[v].size(); i++)
	{
		int u = LCA(Quest[Key[v][i]], v);
		if (u != -1)
			if ( (Union[u]) && (!Quest[Key[v][i]].flag) ) 
			{
				Quest[Key[v][i]].flag = true;
				//предок вершин
				Quest[Key[v][i]].ancestor = Ancestor[Find_Set_DSU(u)];
				//нахождение расстояний между заданными парами вершин дерева
				Quest[Key[v][i]].path = Vertex[Quest[Key[v][i]].x].weight_vertex - 
						Vertex[Quest[Key[v][i]].ancestor].weight_vertex +
						Vertex[Quest[Key[v][i]].y].weight_vertex - 
						Vertex[Quest[Key[v][i]].ancestor].weight_vertex;
			}
	}
}

//вывод результатов
void Out_Data()
{
	for (size_t i = 0; i < Quest.size(); i++)
		cout<<Quest[i].path<<"\n";
}

//установление информации о ребрах
void Set_Vertex(int a, int b, int weight)
{
	graph_type gr;
	gr.weight = weight;
	gr.number = b;
	Graph[a].push_back (gr);
	gr.number = a;
	Graph[b].push_back (gr);
}

//заданные пары вершин
void Set_Quest(int a, int b, int i)
{
		pair_type pair;
		pair.x = a;
		pair.y = b;
		pair.flag = false;
		pair.ancestor = -1;
		Quest.push_back (pair);
		Key[a].push_back(i);
		Key[b].push_back(i);
}

//чтение данных
void Read_Data()
{	
	int a, b, weight;
	
	cin>>N;
	Graph.resize(N);

	for (int i = 0; i < N-1; i++)
	{
		cin>>a>>b>>weight;
		a--;
		b--;
		Set_Vertex(a, b, weight);
	}

	cin>>M;
	Key.resize(N);

	for (int i = 0; i < M; i++)
	{
		cin>>a>>b;
		a--;
		b--;
		Set_Quest(a, b, i);
	}
}

int main(int argc, char* argv[])
{
	Read_Data();
	Init_Set();
	Deep_First_Search (0, 0);
	Out_Data();

	return 0;
}