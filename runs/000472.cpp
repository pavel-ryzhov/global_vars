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

int lg(int i)
{
    int res = 0;
    while (i != 1)
    {
        i >>= 1;
        ++res;
    }
    return res;
}

int pw(int i)
{
    int res = 1;
    while (i-- != 0)
    {
        res <<= 1;
    }
    return res;
}

int max_pow2(int i)
{
    int res = 1;
    while ( (res << 1) <= i ) res <<= 1;
    return res;
}

std::istream &operator>>(std::istream &in, std::pair<int,int> &pr)
{
    in >> pr.first;
    in >> pr.second;
    --pr.first;
    --pr.second;
    return in;
}

std::istream &operator>>(std::istream &in, std::vector<std::list<dist> > &dist)
{
    int i, j, value;
    in >> i;
    in >> j;
    in >> value;
    --i; --j;

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

    std::vector<std::vector<int> > sparse_table;

    int h_c;
    int first_c;

    void pp(int ver, int prev);
public:
    void fill_sparse_table();
    int min_h(int i, int j) const
        {
            return (H[i] < H[j]) ? i : j;
        }

public:
    void get(std::istream &in=std::cin);
    void preprocessing();
    int lca(int pr) const;
    size_t vertex_pairs_count() const
        {
            return vertex_pairs.size();
        }
    int distance(int pr) const;
};

void graph::get(std::istream &in)
{
    int N, M;

    typedef  std::vector<std::list<dist> >::iterator  iter;

    std::cin >> N;
    distances.clear();
    distances.resize(N+1);

    First.resize(N);
    H    .resize(N);
    D    .resize(N);
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

void graph::preprocessing()
{
    h_c = -1;
    first_c = -1;
    pp(0, -1);
}

void graph::fill_sparse_table()
{
    int hg = Order.size()-1;
    if (hg == 0) hg = 1;

    const int st_width = lg(hg)+1;
    sparse_table.resize(hg, std::vector<int>(st_width));

    --hg;
    for (int i = 0; i < hg; ++i)
        sparse_table[i][0] = min_h(Order[i], Order[i+1]);

    for (int j = 1; j < st_width; ++j)
    {
        for (int i = 0; i < hg; ++i)
        {
            if (i+pw(j) > hg) continue;
            int x = i+pw(j-1);
            sparse_table[i][j] =
                min_h(
                    sparse_table[i][j-1],
                    sparse_table[i+pw(j-1)][j-1]
                );
        }
    }
}

int graph::lca(int pr) const
{
    int a = First[vertex_pairs[pr].first];
    int b = First[vertex_pairs[pr].second];
    if (b < a) std::swap(a, b);

    int sz = (a==b) ? 1 : lg(b-a);
    return min_h(
        sparse_table[a][sz],
        sparse_table[b-pw(sz)][sz]
        );
}

int graph::distance(int pr) const
{
    int first  = vertex_pairs[pr].first;
    int second = vertex_pairs[pr].second;
    if (first == second) return 0;
    return D[first] + D[second] - (D[lca(pr)] << 1);
}

int main()
{
    graph gr;
    gr.get();
    gr.preprocessing();
    gr.fill_sparse_table();

    for (size_t i = 0; i < gr.vertex_pairs_count(); ++i)
    {
        std::cout << gr.distance(i) << std::endl;
    }
}

