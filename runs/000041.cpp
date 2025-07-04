#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

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

std::istream &operator>>(std::istream &in, std::vector<std::list<dist> > &dist)
{
    int i, j, value;
    in >> i;
    in >> j;
    in >> value;

    dist[i].push_back(std::make_pair(j, value));
    dist[j].push_back(std::make_pair(i, value));

    return in;
}

class graph
{
    std::vector<std::list<dist> >  distances;
    std::vector<std::pair<int,int> >  vertex_pairs;

    int b;
    bool found;
    std::list<int> path;

    void find_path(int a, int prev=-1);
    int path_dist() const;

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

    std::cin >> N;
    distances.clear();
    distances.resize(N+1);

    for (int i = 1; i < N; ++i)
        std::cin >> distances;

    std::cin >> M;
    vertex_pairs.resize(M);
    for (int i = 0; i < M; ++i)
        std::cin >> vertex_pairs[i];
}

void graph::find_path(int a, int prev)
{
    if (a == b)
    {
        found = true;
        path.push_front(a);
        return;
    }

    typedef  std::list<std::pair<int, int> >::const_iterator  iter;
    for (iter it = distances[a].begin(); it != distances[a].end(); ++it)
    {
        if (it->first == prev) continue;

        find_path(it->first, a);

        if (found)
        {
            path.push_front(a);
            break;
        }
    }
}

struct equal_first
{
    int value;
    equal_first(int value) : value(value) {};
    bool operator()(const std::pair<int,int> &pr) const
        {
            return pr.first == value;
        }
};

int graph::path_dist() const
{
    int result = 0;

    const std::list<std::pair<int,int> > *list_ptr;
    std::list<int>::const_iterator it = path.begin();

    while (it != --path.end())
    {
        list_ptr = &distances[*it];

        result +=
            std::find_if(
                list_ptr->begin(),
                list_ptr->end(),
                equal_first(*++it)
                )->second;
    }

    return result;
}

int graph::distance(int a, int b)
{
    this->b = b;
    found = false;
    path.clear();

    find_path(a);
    return path_dist();
}

int main()
{
    graph gr;
    gr.get();

    for (int i = 0; i < static_cast<int>(gr.vertex_pairs_count()); ++i)
    {
        std::cout << gr.distance(i) << std::endl;
    }
}

