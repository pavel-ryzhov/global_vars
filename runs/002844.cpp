#include <iostream>
#include <vector>


// Класс реализующий структуру 
// системы непересекающихся множеств
class DisjointSets
{
public:
    DisjointSets(int max_number) : sets_(max_number)
    {}

    // метод реализующий поиск корня множества включающего
    // елемент number
    int FindSet(int number)
    {
        int prev = number;
        int cur = number;
        int next = sets_[number];

        while (cur != next)
        {
            sets_[cur] = prev;
            prev = cur;
            cur = next;
            next = sets_[cur];
        }

        while (cur != prev)
        {
            cur = prev;
            prev = sets_[cur];
            sets_[cur] = sets_[next];
        }

        return sets_[cur];
    }

    // метод объединения двух множеств
    //  main_number - елемент первого множества для объединения
    //  aux_number - елемент второго множества для объединения
    // в качестве корня объединения береться корень первого множества
    void Union(int main_number, int aux_number)
    {
        int main_set = FindSet(main_number);
        int aux_set = FindSet(aux_number);
        sets_[aux_number] = main_set;
    }

    // метод для инициализации нового множества с одним елементом
    void AddSet(int number)
    {
        sets_[number] = number;
    }

private:
    std::vector<int> sets_;
};


// Класс реализующий методы для создания дерева
// и поиска расстояний между его узлами
class Graph
{
public:
    Graph(size_t nodes_count) : nodes_(nodes_count), nodes_dsu_(nodes_count)
    {}

    void PushEdge(int first_node, int second_node, int length)
    {
        nodes_[first_node - 1].edges.push_back(std::make_pair(second_node - 1, length));
        nodes_[second_node - 1].edges.push_back(std::make_pair(first_node - 1, length));
    }

    // метод вычисляющий расстояния для заданных пар вершин
    //  queries_nodes - массив, содержащий пары вершин расстояния между которыми необходимо найти
    //  out_dists - массив посчитанных расстояний
    void CalculateDistances(const std::vector<std::pair<int, int> >& queries_nodes, std::vector<int>& out_dists)
    {
        int query_number = 0;
        for (std::vector<std::pair<int, int> >::const_iterator it = queries_nodes.begin();
            it != queries_nodes.end(); ++it, ++query_number)
        {
            nodes_[it->first - 1].queries.push_back(std::make_pair(it->second - 1, query_number));
            nodes_[it->second - 1].queries.push_back(std::make_pair(it->first - 1, query_number));
        }

        out_dists.resize(queries_nodes.size());
        RecursiveTrace(0, 0, 0, out_dists);
    }

private:
    // структура представляющая узел дерева
    //  edges - ребра исходящие из этой вершины, представляются в 
    //          виде массива пар: ("номер второго узла ребра", "длинна ребра")
    //  queries - запросы на поиск расстояний от данного узла, представляются
    //            в виде пар: ("номер конечного узла", "номер запроса в общем списке")
    //  root_length - длина пути от данной вершины к корню
    //  visited - идентификатор, того был ли посещен узел в процессе обхода
    struct NodeState
    {
        NodeState() : root_length(0), visited(false)
        {}

        std::vector<std::pair<int, int> > edges;
        std::vector<std::pair<int, int> > queries;
        int root_length;
        bool visited;
    };

private:
    // узлы дерева
    std::vector<NodeState> nodes_;
    // система непересекающихся множеств
    // для реализации быстрого поиска наименьшего общего предка
    // для пары вершин
    DisjointSets nodes_dsu_;

private:
    // рекурсивный метод выполняющий обход дерева и выполняющий поиск расстояний 
    // между заданными вершинами.
    //  node - текущий узел для обхода
    //  parent - предок текущего узла
    //  length - длина пути от данного узла к корню
    //  out_dists - выходной массив заполняемый полученными расстояними
    void RecursiveTrace(int node, int parent, int length, std::vector<int>& out_dists)
    {
        NodeState& node_state = nodes_[node];
        node_state.root_length = length;
        nodes_dsu_.AddSet(node);

        // обходим дочерние узлы
        for (std::vector<std::pair<int, int> >::iterator it = node_state.edges.begin(); 
            it != node_state.edges.end(); ++it)
        {
            if (it->first != parent)
            {
                RecursiveTrace(it->first, node, length + it->second, out_dists);
                nodes_dsu_.Union(node, it->first);
            }
        }

        // находим расстояния до уже посещенных узлов
        for (std::vector<std::pair<int, int> >::iterator it = node_state.queries.begin(); 
            it != node_state.queries.end(); ++it)
        {
            if (nodes_[it->first].visited)
            {
                int lca_node = nodes_dsu_.FindSet(it->first);
                out_dists[it->second] = GetDistance(it->first, node, lca_node);
            }
        }
        
        node_state.visited = true;
    }

    int GetDistance(int first_node, int second_node, int lca_node)
    {
        return (nodes_[first_node].root_length - nodes_[lca_node].root_length) + 
                (nodes_[second_node].root_length - nodes_[lca_node].root_length);
    }
};


int main()
{
    int nodes_count;
    std::cin >> nodes_count;
    
    Graph graph(nodes_count);
    int first_node;
    int second_node;
    int length;
    while (--nodes_count > 0)
    {
        std::cin >> first_node >> second_node >> length;
        graph.PushEdge(first_node, second_node, length);
    }

    int queries_count;
    std::cin >> queries_count;

    std::vector<std::pair<int, int> > queries;
    queries.reserve(queries_count);
    while (queries_count--)
    {
        std::cin >> first_node >> second_node;
        queries.push_back(std::make_pair(first_node, second_node));
    }

    std::vector<int> distances;
    graph.CalculateDistances(queries, distances);

    for (int i = 0; i < distances.size(); ++i) 
    {
        std::cout << distances[i] << std::endl;
    }
}

