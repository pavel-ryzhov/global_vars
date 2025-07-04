#include <iostream>
#include <vector>
#include <cstdlib>
//#include <cstdio>
//#include <queue>
//#include <time.h>
//#include <sstream>

using namespace std;

// ребро графа
typedef vector<int> edge_t;

// граф
typedef vector<edge_t> graph_t;

// запросы для нахождения пути
typedef vector<vector<int> > query_t;

// длины путей из исходной точки во все остальные
typedef vector<int> path_length_t;

graph_t graph;
graph_t query;

vector<int> dsu;
vector<int> ancestor;
vector<bool> u;
path_length_t path_length;

// поиск множества включающего в себя v
int dsu_find_set(int v)
{
	return v == dsu[v] ? v : dsu[v] = dsu_find_set(dsu[v]);
}

// объединение множеств a b
void dsu_unite(int a, int b, int new_ancestor)
{
	a = dsu_find_set(a), b = dsu_find_set(b);
	if (rand() & 1)
		swap(a, b);
	dsu[a] = b, ancestor[b] = new_ancestor;
}

// наименьший общий предок + проход в глубину и подсчёт длин путей от корня до каждой вершины
void dfs(int n_vertex)
{
	dsu[n_vertex] = n_vertex, ancestor[n_vertex] = n_vertex;
	u[n_vertex] = true;

	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i][0] == n_vertex)
		{
			if (!u[graph[i][1]])
			{
				path_length[graph[i][1]] = graph[i][2] + path_length[n_vertex];

				dfs(graph[i][1]);
				dsu_unite(n_vertex, graph[i][1], n_vertex);
			}
		}
	}

	for (int i = 0; i < query.size(); i++)
	{
		if (query[i][0] == n_vertex)
		{
			if (u[query[i][1]])
			{
				query[i].push_back(path_length[n_vertex]
						+ path_length[query[i][1]] - 2
						* path_length[ancestor[dsu_find_set(query[i][1])]]);

			}
		}
		
		if (query[i][1] == n_vertex)
		{
			if (u[query[i][0]])
			{
				query[i].push_back(path_length[n_vertex]
						+ path_length[query[i][0]] - 2
						* path_length[ancestor[dsu_find_set(query[i][0])]]);
			}
		}
	}

}

int main()
{
    //clock_t t_0 = clock ();
	// получение количества вершин
	int vertex_count;
	cin >> vertex_count;

	dsu.resize(vertex_count);
	ancestor.resize(vertex_count);
	u.resize(vertex_count);

	edge_t edge(3);
	int buf, from, to;

    //clock_t t_1 = clock ();
	// получение графа
	for (int i = 0; i < vertex_count - 1; i++)
	{
		//edge.clear();
		// от
		cin >> from;
		edge[0] = from -1;

		// до
		cin >> to;
		edge[1] = to - 1;

		// вес
		cin >> buf;
		edge[2] = buf;

		// новое ребро с весом
		graph.push_back(edge);
		
		// 
		edge[0] = to - 1;

		edge[1] = from - 1;

		edge[2] = buf;

		// новое ребро с весом
		graph.push_back(edge);
	}
	
	//clock_t t_2 = clock ();

	// количество вершин для поиска путей
	int count_search;
	cin >> count_search;

    edge.resize(2);
	// вершины для посика
	for (int i = 0; i < count_search; i++)
	{
	    cin >> from >> to;
		// от
		edge[0] = from - 1;

		// до
		edge[1] = to - 1;

		// новая пара для поиска
		query.push_back(edge);
	}
	//clock_t t_3 = clock ();

	// препроцессинг
	// длины путей из исходной точки во все остальные
	// изначально все пути бесконечны = -1
	path_length.clear();
	for (int ii = 0; ii < vertex_count; ii++)
	{
		path_length.push_back(-1);
	}

	// исходная вершина - корень
	path_length[0] = 0;

    //clock_t t_4 = clock ();
	// обход в глубину и ответ на запросы
	dfs(0);
	//clock_t t_5 = clock ();

	for (int i = 0; i < query.size(); i++)
	{
	    cout << query[i][2] << endl;
	}
	//clock_t t_6 = clock ();
	
	//cout << endl;
	//cout << "начало " << t_0 << endl; 
	//cout << "инициализация " << (t_1 - t_0) / 1000 << endl;
	//cout << "получение графа " << (t_2 - t_1) / 1000 << endl;
	//cout << "получение запросов " << (t_3 - t_2) / 1000 << endl;
	//cout << "препроцессинг " << (t_4 - t_3) / 1000 << endl;
	//cout << "обход " << (t_5 - t_4) / 1000 << endl;
	//cout << "вывод результатов " << (t_6 - t_5) / 1000 << endl;
}
