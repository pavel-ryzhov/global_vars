#include <vector>
#include <utility>
#include <iostream>

#define RESERVE    0x200
#define RESERVE_VP 0x2000

// vector<dist>
// 0
// 1: [2]=7
// 2: [1]=7, [3]=3, [4]=6
// 3: [2]=3
// 4: [2]=6, [5]=3
// 5: [6]=1
// 6: [5]=1
typedef std::pair<int,int> dist;

std::istream &operator>>(std::istream &in, std::pair<int,int> &pr)
{
    in >> pr.first;
    in >> pr.second;
    return in;
}

std::istream &operator>>(std::istream &in, std::vector<std::vector<dist> > &dist)
{
    int i, j, value;
    in >> i;
    in >> j;
    in >> value;

    dist[i].push_back(std::make_pair(j, value));
    dist[j].push_back(std::make_pair(i, value));

    if (dist[i].size() % RESERVE == 0) dist[i].reserve(dist[i].size() + RESERVE);
    if (dist[j].size() % RESERVE == 0) dist[j].reserve(dist[j].size() + RESERVE);

    return in;
}

class graph
{
    std::vector<std::vector<dist> >  distances;
    std::vector<std::pair<int,int> >  vertex_pairs;

    int b;
    int dis;
    bool found;

    void distance_r(int a, int prev=-1);

public:
    void get(std::istream &in=std::cin);
    size_t vertex_pairs_count() const
        {
            return vertex_pairs.size();
        }
    int distance(int a, int b);
    int distance(int i)
        {
            return distance(vertex_pairs[i].first,
                            vertex_pairs[i].second);
        }
};

void graph::get(std::istream &in)
{
    int N, M;

    typedef  std::vector<std::vector<dist> >::iterator  iter;
    for (iter it = distances.begin(); it != distances.end(); ++it)
    {
        it->reserve(RESERVE);
    }

    std::cin >> N;
    distances.clear();
    distances.resize(N+1);

    for (int i = 1; i < N; ++i)
        std::cin >> distances;

    std::cin >> M;
    vertex_pairs.resize(M);
    for (int i = 0; i < M; ++i)
    {
        std::cin >> vertex_pairs[i];
        if (i % RESERVE_VP == 0)
            vertex_pairs.reserve(i + RESERVE_VP);
    }
}

void graph::distance_r(int a, int prev)
{
    if (a == b)
    {
        found = true;
        return;
    }

    typedef  std::vector<std::pair<int, int> >::const_iterator  iter;

    iter beg = distances[a].begin();
    iter end = distances[a].end();
    for (iter it = beg; it != end; ++it)
    {
        if (it->first == prev) continue;

        distance_r(it->first, a);

        if (found)
        {
            dis += it->second;
            return;
        }
    }
}

int graph::distance(int a, int b)
{
    dis = 0;

    this->b = b;
    found = false;

    distance_r(a);
    return dis;
}

int main()
{
    graph gr;
    gr.get();

    for (size_t i = 0; i < gr.vertex_pairs_count(); ++i)
    {
        std::cout << gr.distance(i) << std::endl;
    }
}

