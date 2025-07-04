#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <queue>

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
int dsu_find_set (int v)
{
    return v == dsu.at (v) ? v : dsu.at (v) = dsu_find_set (dsu.at (v));
}

// объединение множеств a b
void dsu_unite (int a, int b, int new_ancestor)
{
    a = dsu_find_set (a), b = dsu_find_set (b);
    if (rand () & 1)
        swap (a, b);
    dsu[a] = b, ancestor[b] = new_ancestor;
}

// наименьший общий предок
void dfs (int n_vertex)
{
    //cout << n_vertex + 1 << endl;
    dsu[n_vertex] = n_vertex, ancestor[n_vertex] = n_vertex;
    u[n_vertex] = true;

    for (int i = 0; i < graph.size (); i++)
    {
        if (graph.at (i).at (0) == n_vertex)
        {
            //cout << "graph --> " << graph.at (i).at (0) + 1 << " " << graph.at (i).at (1) + 1 << endl;
            if (!u[graph.at (i).at (1)])
            {
                dfs (graph.at (i).at (1));
                dsu_unite (n_vertex, graph.at (i).at (1), n_vertex);
            }
        }

        if (graph.at (i).at (1) == n_vertex)
        {
            if (!u[graph.at (i).at (0)])
            {
                dfs (graph.at (i).at (0));
                dsu_unite (n_vertex, graph.at (i).at (0), n_vertex);
            }
        }
    }

    for (int i = 0; i < query.size (); i++)
    {
        if (query.at (i).at (0) == n_vertex)
        {
            if (u[query.at (i).at (1)])
            {
                query.at (i).push_back (path_length.at(n_vertex) + path_length.at(query.at (i).at (1)) - 2 * path_length.at(ancestor[dsu_find_set (query.at (i).at (1))]));

            }
        }

        if (query.at (i).at (1) == n_vertex)
        {
            if (u[query.at (i).at (0)])
            {
                query.at (i).push_back (path_length.at(n_vertex) + path_length.at(query.at (i).at (0)) - 2 * path_length.at(ancestor[dsu_find_set (query.at (i).at (0))]));
            }
        }
    }

}

// нахождение длинны пути до соседних вершин
void search_path (int n_vertex)
{
    for (int i = 0; i < graph.size (); i++)
    {
        if (graph.at (i).at (0) == n_vertex && path_length.at (graph.at (i).at (1)) == -1)
        {
            path_length.at (graph.at (i).at (1)) = graph.at (i).at (2) + path_length.at (n_vertex);
            search_path (graph.at (i).at (1));
        }

        if (graph.at (i).at (1) == n_vertex && path_length.at (graph.at (i).at (0)) == -1)
        {
            path_length.at (graph.at (i).at (0)) = graph.at (i).at (2) + path_length.at (n_vertex);
            search_path (graph.at (i).at (0));
        }
    }

    return;
}

int main ()
{
    // получение количества вершин
    int vertex_count;
    cin >> vertex_count;

    dsu.resize (vertex_count);
    ancestor.resize (vertex_count);
    u.resize (vertex_count);

    // получение графа
    for (int i = 0; i < vertex_count - 1; i++)
    {
        edge_t edge;
        int buf;

        // от
        cin >> buf;
        edge.push_back (buf - 1);

        // до
        cin >> buf;
        edge.push_back (buf - 1);

        // вес
        cin >> buf;
        edge.push_back (buf);

        // новое ребро с весом
        graph.push_back (edge);
    }

    // количество вершин для поиска путей
    int count_search;
    cin >> count_search;

    // вершины для посика
    for (int i = 0; i < count_search; i++)
    {
        edge_t edge;
        int buf;

        // от
        cin >> buf;
        edge.push_back (buf - 1);

        // до
        cin >> buf;
        edge.push_back (buf - 1);

        // новая пара для поиска
        query.push_back (edge);
    }

    // препроцессинг
    // длины путей из исходной точки во все остальные
    // изначально все пути бесконечны = -1
    path_length.clear ();
    for (int ii = 0; ii < vertex_count; ii++)
    {
        path_length.push_back (-1);
    }

    // исходная вершина
    path_length.at (0) = 0;
    // поиск
    search_path (0);

    // обход в глубину и ответ на запросы
    dfs (0);

    for (int i = 0; i < query.size (); i++)
    {
        cout << query.at (i).at (2) << endl;
    }
}
