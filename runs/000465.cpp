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

    std::vector<int> Order;
    std::vector<int> First;
    std::vector<int> H;
    std::vector<int> D;

    int h_c;
    int first_c;

    void pp(int ver, int prev);

public:
    void get(std::istream &in=std::cin);
    void preprocessing()
        {
            h_c = -1;
            first_c = -1;
            pp(1, -1);
        }
    int lca(int pr);
    size_t vertex_pairs_count() const
        {
            return vertex_pairs.size();
        }
    int distance(int pr);
};

void graph::get(std::istream &in)
{
    int N, M;

    typedef  std::vector<std::list<dist> >::iterator  iter;

    std::cin >> N;
    distances.clear();
    distances.resize(N+1);

    First.resize(N+1);
    H    .resize(N+1);
    D    .resize(N+1);
    Order.reserve(2*N-1);

    for (int i = 1; i < N; ++i)
        std::cin >> distances;

    std::cin >> M;
    vertex_pairs.resize(M);
    for (int i = 0; i < M; ++i)
    {
        std::cin >> vertex_pairs[i];
    }
}

void graph::pp(int ver, int prev)
{
    Order.push_back(ver);
    First[ver] = ++first_c;
    H    [ver] = ++h_c;

    typedef  std::list<std::pair<int, int> >::const_iterator  iter;
    iter beg = distances[ver].begin();
    iter end = distances[ver].end();

    for (iter it = beg; it != end; ++it)
    {
        if (it->first == prev) continue;
        D[it->first] = D[ver] + it->second;
        pp(it->first, ver);
        Order.push_back(ver);
        First[ver] = ++first_c;
    }
    --h_c;
}

int graph::lca(int pr)
{
    int beg = First[vertex_pairs[pr].first];
    int end = First[vertex_pairs[pr].second];
    if (end < beg) std::swap(beg, end);

    int res = Order[beg];
    int min_h = H[res];

    for (int i = beg+1; i <= end; ++i)
    {
        int ord = Order[i];
        if (H[ord] < min_h)
        {
            min_h = H[ord];
            res = ord;
        }
    }

    return res;
}

int graph::distance(int pr)
{
    return D[vertex_pairs[pr].first] +
           D[vertex_pairs[pr].second] -
          (D[lca(pr)] << 1);
}

int main()
{
    graph gr;
    gr.get();
    gr.preprocessing();

    for (size_t i = 0; i < gr.vertex_pairs_count(); ++i)
    {
        std::cout << gr.distance(i) << std::endl;
    }
}

