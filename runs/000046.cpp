// Author: Govorov Igor, 2010
// Task B (Tree).
// Метод двоичного подъёма (препроцессинг - O(N log N), ответ за O(log N)).

#include <cstdlib> // for EXIT_SUCCESS
#include <iostream>
#include <vector>


int n = 0; // число вершин
int maxHeight = 1;
std::vector<std::vector<std::pair<int, int> > > g;
std::vector<bool> used;
std::vector<int> tin, tout;
int timer = 0;
std::vector<std::vector<int> > up;


void dfs(int vertex, int parent = 0)
{
    used[vertex] = true;
    tin[vertex] = ++timer;
    up[vertex][0] = parent;
    for (size_t i = 1; i <= up[vertex].size() -1 ; ++i)
    {
        up.at(vertex).at(i) = up[up[vertex][i-1]][0];
    }
    for (size_t i=0; i<g[vertex].size(); ++i)
    {
        int to = g[vertex][i].first;
        if(!used[to])
        {
            dfs(to, vertex);
        }
    }
    tout[vertex] = ++timer;
}

bool upper(int a, int b)
{
    return (tin[a] <= tin[b]) && (tout[a] >= tout[b]);
}

int lca(int a, int b)
{
    if(upper(a, b))
    {
        return a;
    }
    if(upper(b, a))
    {
        return b;
    }
    for(int i = maxHeight; i >= 0; --i)
    {
        if (!upper(up[a][i], b))
        {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int computePath(int a, int b, int c)
{
    int p = a;
    int sum = 0;
    while(p!=c)
    {
        for(size_t idx = 0; idx < g.at(p).size(); ++idx)
        {
            if(g.at(p).at(idx).first == up[p][0])
            {
                sum += g.at(p).at(idx).second;
                break;
            }
        }
        p = up[p][0];
    }
    p = b;
    while(p!=c)
    {
        for(size_t idx = 0; idx < g.at(p).size(); ++idx)
        {
            if(g.at(p).at(idx).first == up[p][0])
            {
                sum += g.at(p).at(idx).second;
                break;
            }
        }
        p = up[p][0];
    }
    return sum;
}

int main()
{
    using std::make_pair;

    //std::ifstream in("big.txt");
    std::istream &in = std::cin;
    in >> n;
    // На всякий случай
    if(n == 0) return EXIT_SUCCESS;

    used.resize(n);
    tin.resize(n);
    tout.resize(n);
    up.resize (n);
    g.resize(n);

    for(int i = 0; i < n-1; ++i)
    {
        int first, second, lenght;
        in >> first >> second >> lenght;
        g[first-1].push_back(make_pair(second-1, lenght));
        g[second-1].push_back(make_pair(first-1, lenght));
    }

    // Вычисляем количество ячеек под предков (максимальная высота дерева).
    // Кроме корня, очевидно что он всегда предок.
    while((1<<maxHeight) <= n)
    {
        ++maxHeight;
    }
    for(int i = 0; i < n; ++i)
    {
        up[i].resize (maxHeight + 1);
    }
    // Обход в глубину с запоминанием времени и родительских элементов
    dfs(0);

    int m = 0;
    in >> m;
    for(int i = 0; i < m; ++i)
    {
        int first = 0, second = 0;
        in >> first >> second;
        --first;
        --second;
        std::cout << computePath(first, second, lca(first, second)) << std::endl;
    }
    return EXIT_SUCCESS;
}
