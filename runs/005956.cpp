/*
 * Поиск пути в графе
 */

#include <iostream>
#include <vector>

#define i16  signed short int
#define ui16 unsigned short int
#define i32  signed long int
#define ui32 unsigned long int
#define ui8  unsigned char
#define i8   signed char
#define f32  float
#define f64  double

using namespace std;

// ребро графа
typedef vector<i32> t_edge;
// граф
typedef vector<t_edge> t_graph;

// вершины для поиска
typedef vector<i32> t_vertex_search;
// список вершин для посика
typedef vector<t_vertex_search> t_vertex_search_list;

// длины путей из исходной точки во все остальные
typedef vector<i32> t_path_length;

// нахождение длинны пути до соседних вершин
void search_path (i32 n_vertex, t_graph &graph, t_path_length &path_length)
{
    for (ui32 i = 0; i < graph.size (); i++)
    {
        if (graph.at (i).at (0) == n_vertex && path_length.at (graph.at (i).at (1) - 1) == -1)
        {
            path_length.at (graph.at (i).at (1) - 1) = graph.at (i).at (2) + path_length.at (n_vertex - 1);

            search_path (graph.at (i).at (1), graph, path_length);
        }

        if (graph.at (i).at (1) == n_vertex && path_length.at (graph.at (i).at (0) - 1) == -1)
        {
            path_length.at (graph.at (i).at (0) - 1) = graph.at (i).at (2) + path_length.at (n_vertex - 1);

            search_path (graph.at (i).at (0), graph, path_length);
        }
    }

    return;
}

int main ()
{
    // получение количества вершин
    ui32 vertex_count;
    cin >> vertex_count;

    // получение графа
    t_graph graph;
    for (ui32 i = 0; i < vertex_count - 1; i++)
    {
        t_edge edge;
        i32 buf;

        // от
        cin >> buf;
        edge.push_back (buf);

        // до
        cin >> buf;
        edge.push_back (buf);

        // вес
        cin >> buf;
        edge.push_back (buf);

        // новое ребро с весом
        graph.push_back (edge);
    }

    // количество вершин для поиска путей
    ui32 count_search;
    cin >> count_search;

    // вершины для посика
    t_vertex_search_list vertex_search_list;
    for (ui32 i = 0; i < count_search; i++)
    {
        t_vertex_search vertex_search;
        ui32 buf;

        // от
        cin >> buf;
        vertex_search.push_back (buf);

        // до
        cin >> buf;
        vertex_search.push_back (buf);

        // новая пара для поиска
        vertex_search_list.push_back (vertex_search);
    }

    // поиск путей
    for (ui32 i = 0; i < vertex_search_list.size (); i++)
    {
        // длины путей из исходной точки во все остальные
        // изначально все пути бесконечны = -1
        t_path_length path_length (vertex_count, -1);

        // исходная вершина
        path_length.at (vertex_search_list.at(i).at(0) - 1) = 0;

        // поиск
        search_path (vertex_search_list.at(i).at(0), graph, path_length);

        cout << path_length.at (vertex_search_list.at(i).at(1) - 1) << endl;
    }

    return 0;
}
